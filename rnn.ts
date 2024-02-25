#!/usr/bin/env -S bun run

import * as cmake from "./rnn/cmake";
import * as util from "./rnn/util";
import * as cxx from "./rnn/cxx";
import * as rnn from "./rnn/rnn";

const logger = new util.LineLogger();

const cmake_targets: cmake.BuildTarget[] = [
  {
    name: "llvm_c_2",
    kind: cmake.BinaryKind.staticLib,
    dir: "./",
    files: [
      "src/**\/*.cpp",
      "include/**\/*.h"
    ],
    includeDirs: ["include/llvm_c_2", "src"],
    links: [],
    linkDirs: [],
    cxx_version: "17",
    build_options: ["-fno-exceptions"],
    defines: [],
    libraries: [
      {
        name: "llvm",
        includes: [(await util.cmdOutputStdout(["./llvm-config", "--includedir"])).trim()],
        linkDirs: [(await util.cmdOutputStdout(["./llvm-config", "--libdir"])).trim()],
        links: [(await util.cmdOutputStdout(["./llvm-config", "--libs"])).trim()],
        defines: [
          ["_GNU_SOURCE", ""],
          ["__STDC_CONSTANT_MACROS", ""],
          ["__STDC_FORMAT_MACROS", ""],
          ["__STDC_LIMIT_MACROS", ""],
        ],
      },
    ],
  },
];

const project: rnn.Project = {
  name: "llvm_c_2",
  generators: [
    new cmake.CMakeGenerator(cmake_targets),
  ],
};

async function clean(args: string[]): Promise<void> {
  logger.logPush("Cleaning");

  const clean_artifacts = (): Promise<void>[] => {
    return [
      util.remove(".done"),
      util.remove("CMakeLists.txt"),
      util.remove("build", { recursive: true }),
      util.remove("cmake-build-debug", { recursive: true }),
      util.removeGlob("./*.cmake"),
    ];
  };

  const clean_vendor = (): Promise<void> => {
    return util.remove("vendor.d", { recursive: true });
  };

  const [head, ..._tail] = args;

  const arr: Promise<void>[] = [];
  switch (head) {
    case "vendor":
      arr.push(clean_vendor());
      break;

    case "all":
      {
        arr.push(...clean_artifacts());
        arr.push(clean_vendor());
      }
      break;

    default:
      arr.push(...clean_artifacts());
  }

  await Promise.allSettled(arr);
  logger.logPop();
}

async function setup(_args: string[]) {
  logger.logPush("running setup");

  logger.log("Generating project files");
  await rnn.generateProject(project);

  logger.logPop();
}

async function build(_args: string[]) {
  await setup([]);

  logger.logPush("running build");

  process.env.CC = "clang";
  process.env.CXX = "clang++";

  await cmake.setupForBuild("./");
  await cxx.runNinja(undefined, "build/");

  logger.logPop();
}

async function run(args: string[]) {
  await build([]);

  const sep_index = args.indexOf("--");
  let our_args = args;
  let passed_args: string[] = [];
  if (sep_index !== -1) {
    our_args = args.slice(0, sep_index);
    passed_args = args.slice(sep_index + 1, args.length);
  }

  let name = "";
  if (our_args.length >= 1) {
    name = our_args[0];
    our_args = our_args.slice(1, our_args.length);
  } else {
    for (const target of cmake_targets) {
      if (
        target.kind == cmake.BinaryKind.consoleApp ||
        target.kind == cmake.BinaryKind.windowedApp
      ) {
        name = target.name;
        break;
      }
    }
  }
  if (name == "") {
    throw new Error("Could not find suitable binary to run");
  }

  // for (const arg of our_args) {
  //   if (arg == "--valgrind") {}
  // }

  logger.log(`Running ${name}`);
  util.stdout.write("\n");

  const p = Bun.spawn({ cmd: [`./build/${name}`, ...passed_args] });
  await p.exited;
  if (p.exitCode != 0) {
    util.stdout.write(`\nExited with non-zero exit code: ${p.exitCode}`);
    if (p.signalCode) {
      util.stdout.write(`Signal: ${p.signalCode}`);
    }
  }
}

rnn.addSubCommands([
  {
    func: setup,
    name: "setup",
    help: "setup project for use",
  },
  {
    func: clean,
    name: "clean",
    help: "clean artifacts",
  },
  {
    func: build,
    name: "build|b",
    help: "build project",
  },
  {
    func: run,
    name: "run|r",
    help: "run executable",
  },
]);

await rnn.main(process.argv.slice(2));
