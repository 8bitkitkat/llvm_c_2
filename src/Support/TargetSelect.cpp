#include "Support/TargetSelect.h"

#include <llvm/Support/TargetSelect.h>

LLVM_C_EXTERN_C_BEGIN

bool llvm_InitializeNativeTarget() {
    return llvm::InitializeNativeTarget();
}

bool llvm_InitializeNativeTargetAsmPrinter() {
    return llvm::InitializeNativeTargetAsmPrinter();
}

bool llvm_InitializeNativeTargetAsmParser() {
    return llvm::InitializeNativeTargetAsmParser();
}

LLVM_C_EXTERN_C_END
