import { writeAllSync } from 'https://deno.land/std@0.121.0/streams/conversion.ts';
import { expandGlob } from "https://deno.land/std@0.121.0/fs/mod.ts";

export class LineLogger {
  stack: string[];

  constructor() {
    this.stack = [];
  }

  // deno-lint-ignore no-explicit-any
  public log(...args: any[]) {
    const sb = new StringBuilder();
    sb.push('[');

    for (const s of this.stack) {
      sb.push(`${s} : `);
    }

    sb.push(...args.toString());
    sb.push(']');

    stdout.clearLine();
    stdout.write(sb.string);
  }

  public logPush(str: string) {
    this.log(str);
    this.stack.push(str);
  }

  public logPop() {
    this.stack.pop();
  }
}

// deno-lint-ignore no-namespace
export namespace stdout {
  const text_encoder = new TextEncoder();

  export const ESC = "\x1b";
  export const OSC = ESC + "[";

  // deno-lint-ignore no-explicit-any
  export function write(...args: any[]) {
    // const encoder = new TextEncoder();
    for (const v of args) {
      const text = text_encoder.encode(v.toString());
      writeAllSync(Deno.stdout, text);
    }
  }

  export function clearLine() {
    write(OSC + "2K\r");
  }

  export function moveUp() {
    write(OSC + "1A");
  }
}

export class StringBuilder {
  string: string

  constructor(str: string = '') {
    this.string = str;
  }

  push(...strings: string[]) {
    this.string = this.string.concat(...strings);
  }
}

export function pathExists(path: string): boolean {
  try {
    Deno.lstatSync(path);
    return true;
  } catch (err) {
    if (err instanceof Deno.errors.NotFound)
      return false;

    throw err;
  }
}

export function remove(path: string, options?: { recursive?: boolean }, logger?: LineLogger): Promise<void> {
  logger?.log(`Trying to remove ${path}`);

  if (pathExists(path)) {
    const p = Deno.remove(path, options);
    logger?.log(`Removed ${path}`);
    return p;
  } else {
    return Promise.resolve();
  }
}

export async function removeGlob(glob: string, options?: { recursive?: boolean }): Promise<void> {
  for await (const { path } of expandGlob(glob)) {
    await remove(path, options);
  }
}

export async function runCmd(options: Deno.RunOptions, logger?: LineLogger): Promise<void> {
  logger?.log(`Running Command '${options.cmd.join(' ')}'`);

  const p = Deno.run({ stdout: 'piped', stderr: 'piped', ...options });
  const s = await p.status();
  if (!s.success) {
    const decoder = new TextDecoder();
    const stdout = decoder.decode(await p.output());
    const stderr = decoder.decode(await p.stderrOutput());
    throw new Error(`Failed executing '${options.cmd.join(' ')}'\n--- stdout:\n${stdout}\n--- stderr:\n${stderr}`);
  }
  p.close();
}

export async function cmdOutput(cmd: string[]): Promise<[string, string]> {
  const p = Deno.run({ stdout: 'piped', stderr: 'piped', cmd });
  const [_status, stdout, stderr] = await Promise.all([
    p.status(),
    p.output(),
    p.stderrOutput()
  ]);
  p.close();
  const decoder = new TextDecoder();
  return [decoder.decode(stdout), decoder.decode(stderr)];
}

export async function cmdOutputStdout(cmd: string[]): Promise<string> {
  const [stdout, _stderr] = await cmdOutput(cmd);
  return stdout;
}

export async function cmdOutputStderr(cmd: string[]): Promise<string> {
  const [_stdout, stderr] = await cmdOutput(cmd);
  return stderr;
}
