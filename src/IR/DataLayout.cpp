#include "IR/DataLayout.h"

#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Module.h"

LLVM_C_EXTERN_C_BEGIN

llvm_DataLayoutRef llvm_DataLayout_create(llvm_ModuleRef ref) {
    auto mod = reinterpret_cast<llvm::Module*>(ref);
    return reinterpret_cast<llvm_DataLayoutRef>(new llvm::DataLayout(mod));
}

void llvm_DataLayout_dispose(llvm_DataLayoutRef ref) {
    auto dl = reinterpret_cast<llvm::DataLayout*>(ref);
    delete dl;
}

LLVM_C_EXTERN_C_END
