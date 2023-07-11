#include "IR/InlineAsm.h"

#include <llvm/IR/InlineAsm.h>
#include <llvm/Support/Error.h>

LLVM_C_EXTERN_C_BEGIN

llvm_InlineAsmRef llvm_InlineAsm_get(
    llvm_FunctionTypeRef ty_ref,
    const char* AsmStringData,
    size_t AsmStringLength,
    const char* ConstraintsData,
    size_t ConstraintsLength,
    bool hasSideEffects,
    bool isAlignStack,
    llvm_InlineAsm_AsmDialect dialect,
    bool canThrow //
) {
    auto ty = reinterpret_cast<llvm::FunctionType*>(ty_ref);
    return reinterpret_cast<llvm_InlineAsmRef>(llvm::InlineAsm::get(
        ty,
        llvm::StringRef(AsmStringData, AsmStringLength),
        llvm::StringRef(ConstraintsData, ConstraintsLength),
        hasSideEffects,
        isAlignStack,
        static_cast<llvm::InlineAsm::AsmDialect>(dialect),
        canThrow));
}

llvm_ErrorRef llvm_InlineAsm_verify(
    llvm_FunctionTypeRef ty_ref,
    const char* ConstraintsData,
    size_t ConstraintsLength //
) {
    auto ty = reinterpret_cast<llvm::FunctionType*>(ty_ref);
    auto err = llvm::InlineAsm::verify(ty, llvm::StringRef(ConstraintsData, ConstraintsLength));
    auto err_ptr = new llvm::Error(std::move(err));
    return reinterpret_cast<llvm_ErrorRef>(err_ptr);
}

LLVM_C_EXTERN_C_END
