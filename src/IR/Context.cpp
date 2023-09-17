#include "IR/Context.h"

#include "llvm/IR/LLVMContext.h"

LLVM_C_EXTERN_C_BEGIN

llvm_ContextRef llvm_Context_create() {
    return reinterpret_cast<llvm_ContextRef>(new llvm::LLVMContext());
}

void llvm_Context_dispose(llvm_ContextRef ref) {
    // delete reinterpret_cast<llvm::LLVMContext*>(ref);
    auto ctx = reinterpret_cast<llvm::LLVMContext*>(ref);
    ctx->~LLVMContext();
}

LLVM_C_EXTERN_C_END
