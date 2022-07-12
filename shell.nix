{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "llvm_c_2 env";

  # Build-time deps
  nativeBuildInputs = [
    pkgs.deno
    pkgs.ninja
    pkgs.cmake
    pkgs.clang_13
  ];

  # Run/link time deps
  buildInputs = [
    pkgs.llvmPackages_13.libllvm
  ];
}
