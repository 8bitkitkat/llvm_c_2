import { StringBuilder } from "./util";
import { globIterateSync } from 'glob';

import * as rnn from "./rnn";
import * as cxx from "./cxx";
import * as util from "./util";

export enum BinaryKind {
  consoleApp,
  windowedApp,
  sharedLib,
  staticLib,
}

export class CMakeGenerator implements rnn.Generator {
  targets: BuildTarget[];

  constructor(targets: BuildTarget[]) {
    this.targets = targets;
  }

  generate(project: rnn.Project): Promise<void> {
    generate(project.name, this.targets);
    return (async () => {})();
  }

  clean(): Promise<void> {
    throw new Error("Method not implemented.");
  }
}

export type BuildTarget = {
  name: string;
  kind: BinaryKind;
  dir: string;
  files: string[];
  includeDirs: string[];
  links: string[];
  linkDirs: string[];
  cxx_version: cxx.Version;
  build_options: string[];
  position_independent_code?: boolean;
  precompiled_header?: string;
  defines: [string, string][];
  libraries: cxx.Library[];
};

function makePathRelative(str: string): string {
  const cwd = process.cwd();
  return str.replace(`${cwd}/`, "");
}

function generateBuildTarget(target: BuildTarget): string {
  // setup
  const properties = new Map<string, string>();
  if (target.cxx_version != "default") {
    properties.set("CXX_STANDARD", target.cxx_version);
    properties.set("CXX_STANDARD_REQUIRED", "YES");
  }
  properties.set("CXX_EXTENSIONS", "NO");
  properties.set("INTERPROCEDURAL_OPTIMIZATION", "False");

  if (target.kind == BinaryKind.sharedLib) {
    properties.set("POSITION_INDEPENDENT_CODE", "True");
    target.build_options.push("-fPIC");
  } else {
    properties.set("POSITION_INDEPENDENT_CODE", "False");
  }

  if (!target.dir.endsWith("/")) {
    target.dir = target.dir + "/";
  }

  const sb = new StringBuilder();

  // binary kind
  switch (target.kind) {
    case BinaryKind.consoleApp:
    case BinaryKind.windowedApp:
      sb.push(`add_executable("${target.name}"\n`);
      properties.set("POSITION_INDEPENDENT_CODE", "False");
      break;

    case BinaryKind.staticLib:
      sb.push(`add_library("${target.name}" STATIC\n`);
      break;
    case BinaryKind.sharedLib:
      sb.push(`add_library("${target.name}" SHARED\n`);
      break;
  }

  for (let glob of target.files) {
    if (!glob.startsWith("./")) {
      glob = target.dir + glob;
    }
    for (const path of globIterateSync(glob, {})) {
      sb.push(`  "${makePathRelative(path)}"\n`);
    }
  }
  sb.push(")\n\n");

  // include
  sb.push(`target_include_directories("${target.name}" PRIVATE\n`);
  for (let glob of target.includeDirs) {
    if (!glob.startsWith("/") && !glob.startsWith("./")) {
      glob = target.dir + glob;
    }

    if (glob.indexOf("*") != -1) {
      for (const dir of globIterateSync(glob)) {
        sb.push(`  "${dir}"\n`);
      }
    } else {
      sb.push(`  "${glob}"\n`);
    }
  }
  sb.push(")\n\n");

  // link dirs
  sb.push(`target_link_directories("${target.name}" PRIVATE\n`);
  for (let glob of target.linkDirs) {
    if (!glob.startsWith("/") && !glob.startsWith("./")) {
      glob = target.dir + glob;
    }

    if (glob.indexOf("*") != -1) {
      for (const file of globIterateSync(glob)) {
        sb.push(`  "${file}"\n`);
      }
    } else {
      sb.push(`  "${glob}"\n`);
    }
  }
  sb.push(")\n\n");

  // links
  sb.push(`target_link_libraries("${target.name}"\n`);
  for (const link of target.links) {
    sb.push(`  "${link}"\n`);
  }
  sb.push(")\n\n");

  // build options
  sb.push(`target_compile_options("${target.name}" PRIVATE\n`);
  for (const option of target.build_options) {
    sb.push(`  ${option}\n`);
  }
  sb.push(")\n\n");

  // properties
  sb.push(`set_target_properties("${target.name}" PROPERTIES\n`);
  for (const [key, value] of properties.entries()) {
    sb.push(`  ${key} ${value}\n`);
  }
  sb.push(")\n\n");

  // Defines
  sb.push(`target_compile_definitions("${target.name}" PUBLIC\n`);
  for (const [key, value] of target.defines) {
    sb.push(`  ${key}${value !== "" ? `="${value}"` : ""}\n`);
  }
  sb.push(")\n\n");

  // pre-compiled header
  if (target.precompiled_header) {
    sb.push(
      `target_precompile_headers("${target.name}" PUBLIC "${
        target.dir + target.precompiled_header
      }")\n\n`,
    );
  }

  // windows && windowed
  if ((process.platform.match("windows")) && (target.kind == BinaryKind.windowedApp)) {
    sb.push(`target_link_options("${target.name}" PRIVATE -mwindows)\n\n`);
  }

  return sb.string;
}

type Path = string; // just for readability

function generateCMakeSources(
  name: string,
  targets: BuildTarget[],
): Map<Path, string> {
  const sb = new StringBuilder();
  const map = new Map<Path, string>();

  sb.push("cmake_minimum_required(VERSION 3.16)\n\n");
  sb.push(`project("${name}")\n\n`);

  for (const target of targets) {
    const path = `${target.name}.cmake`;

    map.set(path, generateBuildTarget(target));

    sb.push(`include(${path})\n`);
  }

  map.set("CMakeLists.txt", sb.string);

  return map;
}

export async function generate(name: string, targets: BuildTarget[]) {
  const root = process.cwd();

  for (const target of targets) {
    for (const lib of target.libraries) {
      const vendor_root = `./vendor.d/${lib.name}`;
      const new_includeDirs: string[] = [];
      const new_linkDirs: string[] = [];

      for (const dir of lib.includes) {
        if (dir.startsWith("/") || dir.startsWith("./")) {
          new_includeDirs.push(dir);
        } else {
          new_includeDirs.push(`${vendor_root}/${dir}`);
        }
      }
      for (const dir of lib.linkDirs) {
        if (dir.startsWith("/") || dir.startsWith("./")) {
          new_linkDirs.push(dir);
        } else {
          new_linkDirs.push(`${vendor_root}/${dir}`);
        }
      }

      target.includeDirs.push(...new_includeDirs);
      target.linkDirs.push(...new_linkDirs);
      target.links.push(...lib.links);
      target.defines.push(...lib.defines);

      process.chdir(root);

      if (await util.pathExists(vendor_root)) {
        if (await util.pathExists(`${vendor_root}/.done`)) {
          continue;
        } else {
          await util.remove(vendor_root, { recursive: true });
        }
      }

      Bun.spawnSync({ cmd: ["mkdir", "-p", vendor_root] });

      if (lib.remote) {
        await util.runCmd(
          `git clone --depth 1 ${lib.remote.recursive ? "--recursive" : ""} ${lib.remote.git} ${vendor_root}`
            .replace(/\s\s+/g, " ") // collapse multiple spaces into one
            .split(" "),
          { cwd: root, }
        );
      }

      if (lib.setup) {
        process.chdir(vendor_root);
        await lib.setup();
      }

      process.chdir(root);
      process.chdir(vendor_root);
      await Bun.write(".done", "");
    }
  }
  process.chdir(root);

  const encoder = new TextEncoder();
  const files = generateCMakeSources(name, targets);

  for (const [path, source] of files.entries()) {
    const text = encoder.encode(source);
    await Bun.write(path, text);
  }
}

export async function setupForBuild(
  projectDir: string,
  generator = "Ninja",
  buildDir = "build",
) {
  const dir = projectDir + "/" + buildDir;
  Bun.spawnSync({ cmd: ["mkdir", "-p", dir] });
  await util.runCmd(["/usr/bin/cmake", "-G", generator, "../"], { cwd: dir });
}
