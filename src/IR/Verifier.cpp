#include "IR/Verifier.h"

#include "llvm/IR/Verifier.h"

LLVM_C_EXTERN_C_BEGIN

bool llvm_verifyFunction(
    const llvm_FunctionRef ref,
    llvm__raw_ostream__ref os //
) {
    auto func = reinterpret_cast<llvm::Function*>(ref);
    return llvm::verifyFunction(*func, reinterpret_cast<llvm::raw_ostream*>(os));
}

bool llvm_verifyModule(
    const llvm_ModuleRef ref,
    llvm__raw_ostream__ref os,
    bool* BrokenDebugInfo //
) {
    auto mod = reinterpret_cast<llvm::Module*>(ref);
    return llvm::verifyModule(*mod, reinterpret_cast<llvm::raw_ostream*>(os), BrokenDebugInfo);
}

LLVM_C_EXTERN_C_END
