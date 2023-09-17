import * as util from "./util";

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
  await util.runCmd(cmd.split(" "), { cwd });

  util.stdout.moveUp();
  util.stdout.moveUp();
  util.stdout.clearLine();
}
