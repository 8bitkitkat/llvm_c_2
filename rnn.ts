#!/usr/bin/env -S deno run --allow-all

import * as cmake from "./.rnn/lib/cmake.ts";
import * as util from "./.rnn/lib/util.ts";
import * as cxx from "./.rnn/lib/cxx.ts";
import * as rnn from "./.rnn/lib/rnn.ts";

const logger = new util.LineLogger();

const cmake_targets: cmake.BuildTarget[] = [
  {
    name: "llvm_c_2",
    kind: cmake.BinaryKind.staticLib,
    dir: "./",
    files: ["**\/*.cpp", "**\/*.hpp", "**\/*.h"],
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
  name: "zinc",
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

  const arr = [];
  switch (head) {
    case "vendor":
      arr.push(clean_vendor());
      break;

    case "all":
      {
        arr.push(clean_artifacts());
        arr.push(clean_vendor());
      }
      break;

    default:
      arr.push(clean_artifacts());
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

  Deno.env.set("CC", "clang");
  Deno.env.set("CXX", "clang++");
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

  // const name = HelloWorld.build_targets[0].name;
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

  const p = Deno.run({ cmd: [`./build/${name}`, ...passed_args] });
  const s = await p.status();
  if (!s.success) {
    util.stdout.write(`\nExited with non-zero exit code: ${s.code}`);
    if (s.signal) {
      util.stdout.write(`Signal: ${s.signal}`);
    }
  }

  p.close();
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

await rnn.main(Deno.args);
