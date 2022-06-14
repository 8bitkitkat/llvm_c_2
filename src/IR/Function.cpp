#include "IR/Function.h"

#include "llvm/IR/Function.h"

LLVM_C_EXTERN_C_BEGIN

llvm_FunctionRef llvm_Function_create(
    llvm_FunctionTypeRef ty_ref,
    llvm_LinkageType Linkage,
    unsigned int AddrSpace,
    const char* NameData,
    size_t NameLength,
    llvm_ModuleRef mod_ref //
) {
    auto ty = reinterpret_cast<llvm::FunctionType*>(ty_ref);
    assert(ty->getTypeID() == llvm::Type::FunctionTyID);
    auto name = llvm::StringRef(NameData, NameLength);
    auto mod = reinterpret_cast<llvm::Module*>(mod_ref);
    auto function = llvm::Function::Create(
        ty, static_cast<llvm::Function::LinkageTypes>(Linkage), AddrSpace, name, mod);
    return reinterpret_cast<llvm_FunctionRef>(function);
}

void llvm_Function_dispose(llvm_FunctionRef ref) {
    auto function = reinterpret_cast<llvm::Function*>(ref);
    function->~Function();
}

llvm_ValueRef llvm_Function_getArg(llvm_FunctionRef ref, unsigned int i) {
    auto function = reinterpret_cast<llvm::Function*>(ref);
    return reinterpret_cast<llvm_ValueRef>(function->getArg(i));
}

LLVM_C_EXTERN_C_END
