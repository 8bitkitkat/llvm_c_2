import * as util from './util';

export type SubCommand = {
  func: (args: string[]) => Promise<void>,
  name: string,
  help: string,
};

const subCommands: SubCommand[] = [
];

export function addSubCommand(sub_command: SubCommand) {
  subCommands.push(sub_command);
}

export function addSubCommands(sub_command: SubCommand[]) {
  subCommands.push(...sub_command);
}

// deno-lint-ignore require-await
async function help(_args: string[]) {
  console.log(`Usage: ${process.argv0} ACTION [arguments]\n`);

  for (const subcmd of subCommands) {
    console.log(`  ${subcmd.name}    \t${subcmd.help}`)
  }
}

export async function main(args: string[]) {
  const [head, ...tail] = args;

  subCommands.push({ func: help, name: 'help|--help|-h', help: 'print this message' });

  let found_cmd = false;
  for (const subcmd of subCommands) {
    const names = subcmd.name.split('|');
    for (const name of names) {
      if (name == head) {
        await subcmd.func(tail);
        found_cmd = true;
      }
    }
  }

  if (!found_cmd) {
    console.error(`Unknown action: '${head}', use 'help' for help`)
  }

  // util.clearLine();
  util.stdout.clearLine();
}

export type Project = {
  name: string,
  generators: Generator[],
}

export interface Generator {
  generate(project: Project): Promise<void>;
  clean(): Promise<void>;
}

export async function generateProject(proj: Project) {
  for (const gener of proj.generators) {
    await gener.generate(proj);
  }
}
