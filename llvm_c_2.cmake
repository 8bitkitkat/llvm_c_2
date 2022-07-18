add_library("llvm_c_2" STATIC
  "src/ExecutionEngine/ExecutionEngine.cpp"
  "src/ExecutionEngine/GenericValue.cpp"
  "src/IR/BasicBlock.cpp"
  "src/IR/Constant.cpp"
  "src/IR/Context.cpp"
  "src/IR/DataLayout.cpp"
  "src/IR/Function.cpp"
  "src/IR/IRBuilder.cpp"
  "src/IR/InlineAsm.cpp"
  "src/IR/Module.cpp"
  "src/IR/Type.cpp"
  "src/IR/Value.cpp"
  "src/IR/Verifier.cpp"
  "src/Support/TargetSelect.cpp"
  "src/Support/raw_ostream.cpp"
  "include/llvm_c_2/ExecutionEngine/ExecutionEngine.h"
  "include/llvm_c_2/ExecutionEngine/GenericValue.h"
  "include/llvm_c_2/IR/BasicBlock.h"
  "include/llvm_c_2/IR/Constant.h"
  "include/llvm_c_2/IR/Context.h"
  "include/llvm_c_2/IR/DataLayout.h"
  "include/llvm_c_2/IR/Function.h"
  "include/llvm_c_2/IR/IRBuilder.h"
  "include/llvm_c_2/IR/InlineAsm.h"
  "include/llvm_c_2/IR/Module.h"
  "include/llvm_c_2/IR/Type.h"
  "include/llvm_c_2/IR/Value.h"
  "include/llvm_c_2/IR/Verifier.h"
  "include/llvm_c_2/Support/TargetSelect.h"
  "include/llvm_c_2/Support/raw_ostream.h"
  "include/llvm_c_2/extern_c.h"
  "include/llvm_c_2/llvm.h"
)

target_include_directories("llvm_c_2" PRIVATE
  "./include/llvm_c_2"
  "./src"
  "/usr/include"
)

target_link_directories("llvm_c_2" PRIVATE
  "/usr/lib"
)

target_link_libraries("llvm_c_2"
  "-lLLVM-14"
)

target_compile_options("llvm_c_2" PRIVATE
  -fno-exceptions
)

set_target_properties("llvm_c_2" PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  INTERPROCEDURAL_OPTIMIZATION False
  POSITION_INDEPENDENT_CODE False
)

target_compile_definitions("llvm_c_2" PUBLIC
  _GNU_SOURCE
  __STDC_CONSTANT_MACROS
  __STDC_FORMAT_MACROS
  __STDC_LIMIT_MACROS
)

