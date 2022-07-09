import * as util from "./util.ts";

export type Version =
  | "default"
  | "98"
  | "11"
  | "17"
  | "20";

export type Library = {
  name: string;
  remote?: { git: string; recursive: boolean };
  includes: string[];
  linkDirs: string[];
  links: string[];
  defines: [string, string][];
  setup?: () => Promise<void>;
};

export async function runNinja(
  what?: string,
  cwd?: string,
  logger?: util.LineLogger,
  use_mold = false,
) {
  logger?.log(`Running Ninja${what ? ` on ${what}` : ""}`);

  util.stdout.write("\n");

  const cmd = use_mold ? "mold -run " : "" + `ninja${what ? ` ${what}` : ""}`;
  const p = Deno.run({ cmd: cmd.split(" "), cwd });
  const s = await p.status();
  if (!s.success) {
    // const decoder = new TextDecoder();
    // const stdout = decoder.decode(await p.output());
    // const stderr = decoder.decode(await p.stderrOutput());
    // throw new Error(`Failed executing '${cmd}'\n--- stdout:\n${stdout}\n--- stderr:\n${stderr}`);
    throw new Error(`Failed executing '${cmd}'`);
  }
  p.close();

  util.stdout.moveUp();
  util.stdout.moveUp();
  util.stdout.clearLine();
}
