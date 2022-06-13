#include "IR/Module.h"

#include "llvm/IR/Module.h"

LLVM_C_EXTERN_C_BEGIN

llvm_ModuleRef
llvm_Module_create(const char* idStringData, size_t idStringLength, llvm_ContextRef ctx_ref) {
    auto ctx = reinterpret_cast<llvm::LLVMContext*>(ctx_ref);
    auto id = llvm::StringRef(idStringData, idStringLength);
    return reinterpret_cast<llvm_ModuleRef>(new llvm::Module(id, *ctx));
}

void llvm_Module_dispose(llvm_ModuleRef ref) {
    delete reinterpret_cast<llvm::Module*>(ref);
}

void llvm_Module_dump(llvm_ModuleRef ref) {
    auto mod = reinterpret_cast<llvm::Module*>(ref);
    // mod->dump();
    mod->print(llvm::errs(), nullptr, false, true);
}

LLVM_C_EXTERN_C_END
