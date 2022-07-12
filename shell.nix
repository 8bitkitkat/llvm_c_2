{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "dev_env";
  nativeBuildInputs = [
    pkgs.deno
    pkgs.ninja
    pkgs.cmake
    pkgs.clang_13
    pkgs.llvmPackages_13.libllvm
  ];
}
