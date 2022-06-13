#include "IR/IRBuilder.h"

#include "llvm/IR/IRBuilder.h"

LLVM_C_EXTERN_C_BEGIN

llvm_IRBuilderDefaultRef llvm_IRBuilderDefault_create(llvm_ContextRef ctx_ref) {
    auto ctx = reinterpret_cast<llvm::LLVMContext*>(ctx_ref);
    return reinterpret_cast<llvm_IRBuilderDefaultRef>(new llvm::IRBuilder<>(*ctx));
}

void llvm_IRBuilderDefault_dispose(llvm_IRBuilderDefaultRef ref) {
    delete reinterpret_cast<llvm::IRBuilder<>*>(ref);
}

void llvm_IRBuilderDefault_setInsertionPoint_BasicBlock(
    llvm_IRBuilderDefaultRef builder_ref, llvm_BasicBlockRef bb_ref //
) {
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(builder_ref);
    auto bb = reinterpret_cast<llvm::BasicBlock*>(bb_ref);
    builder->SetInsertPoint(bb);
}

llvm_ValueRef llvm_IRBuilderDefault_createAdd(
    llvm_IRBuilderDefaultRef ref,
    llvm_ValueRef LHS,
    llvm_ValueRef RHS,
    const char* NameData,
    size_t NameLength //
) {
    auto lhs = reinterpret_cast<llvm::Value*>(LHS);
    auto rhs = reinterpret_cast<llvm::Value*>(RHS);
    auto name = llvm::StringRef(NameData, NameLength);
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    return reinterpret_cast<llvm_ValueRef>(builder->CreateAdd(lhs, rhs, name));
}

llvm_ValueRef llvm_IRBuilderDefault_createRet(llvm_IRBuilderDefaultRef ref, llvm_ValueRef val_ref) {
    auto val = reinterpret_cast<llvm::Value*>(val_ref);
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    return reinterpret_cast<llvm_ValueRef>(builder->CreateRet(val));
}

llvm_ValueRef llvm_IRBuilderDefault_createRetVoid(llvm_IRBuilderDefaultRef ref) {
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    return reinterpret_cast<llvm_ValueRef>(builder->CreateRetVoid());
}

llvm_ValueRef llvm_IRBuilderDefault_createCall(
    llvm_IRBuilderDefaultRef ref,
    llvm_FunctionTypeRef Ty,
    llvm_ValueRef Callee,
    const llvm_ValueRef* ArgsData,
    size_t ArgsLength,
    const char* NameData,
    size_t NameLength //
) {
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    auto ty = reinterpret_cast<llvm::FunctionType*>(Ty);
    auto callee = reinterpret_cast<llvm::Value*>(Callee);
    auto args = std::vector<llvm::Value*>();
    for (size_t i = 0; i < ArgsLength; i++) {
        auto arg = reinterpret_cast<llvm::Value*>(ArgsData[i]);
        args.emplace_back(arg);
    }
    auto name = llvm::StringRef(NameData, NameLength);
    return reinterpret_cast<llvm_ValueRef>(builder->CreateCall(ty, callee, args, name));
}

llvm_ValueRef llvm_IRBuilderDefault_createAlloca(
    llvm_IRBuilderDefaultRef ref,
    llvm_TypeRef Ty,
    unsigned AddrSpace,
    llvm_ValueRef ArraySize,
    const char* NameData,
    size_t NameLength //
) {
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    auto ty = reinterpret_cast<llvm::Type*>(Ty);
    auto size = reinterpret_cast<llvm::Value*>(ArraySize);
    auto name = llvm::StringRef(NameData, NameLength);
    return reinterpret_cast<llvm_ValueRef>(builder->CreateAlloca(ty, AddrSpace, size, name));
}

llvm_ValueRef llvm_IRBuilderDefault_createStore(
    llvm_IRBuilderDefaultRef ref, llvm_ValueRef Val, llvm_ValueRef Ptr, bool isVolatile //
) {
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    auto val = reinterpret_cast<llvm::Value*>(Val);
    auto ptr = reinterpret_cast<llvm::Value*>(Ptr);
    return reinterpret_cast<llvm_ValueRef>(builder->CreateStore(val, ptr, isVolatile));
}

llvm_ValueRef llvm_IRBuilderDefault_createGEP(
    llvm_IRBuilderDefaultRef ref,
    llvm_TypeRef Ty,
    llvm_ValueRef Ptr,
    llvm_ValueRef Idx,
    const char* NameData,
    size_t NameLength //
) {
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    auto ty = reinterpret_cast<llvm::Type*>(Ty);
    auto ptr = reinterpret_cast<llvm::Value*>(Ptr);
    auto idx = reinterpret_cast<llvm::Value*>(Idx);
    auto name = llvm::StringRef(NameData, NameLength);
    return reinterpret_cast<llvm_ValueRef>(builder->CreateGEP(ty, ptr, idx, name));
}

llvm_ValueRef llvm_IRBuilderDefault_createGEP_arr(
    llvm_IRBuilderDefaultRef ref,
    llvm_TypeRef Ty,
    llvm_ValueRef Ptr,
    const llvm_ValueRef* IdxListData,
    size_t IdxListLength,
    const char* NameData,
    size_t NameLength //
) {
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    auto ty = reinterpret_cast<llvm::Type*>(Ty);
    auto ptr = reinterpret_cast<llvm::Value*>(Ptr);
    auto list = llvm::ArrayRef<llvm::Value*>(
        reinterpret_cast<llvm::Value* const*>(IdxListData), IdxListLength);
    auto name = llvm::StringRef(NameData, NameLength);
    return reinterpret_cast<llvm_ValueRef>(builder->CreateGEP(ty, ptr, list, name));
}

llvm_ValueRef llvm_IRBuilderDefault_createLoad(
    llvm_IRBuilderDefaultRef ref,
    llvm_TypeRef Ty,
    llvm_ValueRef Ptr,
    bool isVolatile,
    const char* NameData,
    size_t NameLength //
) {
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    auto ty = reinterpret_cast<llvm::Type*>(Ty);
    auto ptr = reinterpret_cast<llvm::Value*>(Ptr);
    auto name = llvm::StringRef(NameData, NameLength);
    return reinterpret_cast<llvm_ValueRef>(builder->CreateLoad(ty, ptr, isVolatile, name));
}

llvm_ConstantRef llvm_IRBuilderDefault_createGlobalString(
    llvm_IRBuilderDefaultRef ref,
    const char* StrData,
    size_t StrLength,
    const char* NameData,
    size_t NameLength,
    unsigned AddressSpace,
    llvm_ModuleRef M_ref //
) {
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    auto str = llvm::StringRef(StrData, StrLength);
    auto name = llvm::StringRef(NameData, NameLength);
    auto mod = reinterpret_cast<llvm::Module*>(M_ref);
    return reinterpret_cast<llvm_ConstantRef>(
        builder->CreateGlobalString(str, name, AddressSpace, mod));
}

llvm_ConstantRef llvm_IRBuilderDefault_createGlobalStringPtr(
    llvm_IRBuilderDefaultRef ref,
    const char* StrData,
    size_t StrLength,
    const char* NameData,
    size_t NameLength,
    unsigned AddressSpace,
    llvm_ModuleRef M_ref //
) {
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    auto str = llvm::StringRef(StrData, StrLength);
    auto name = llvm::StringRef(NameData, NameLength);
    auto mod = reinterpret_cast<llvm::Module*>(M_ref);
    return reinterpret_cast<llvm_ConstantRef>(
        builder->CreateGlobalStringPtr(str, name, AddressSpace, mod));
}

llvm_ValueRef llvm_IRBuilderDefault_createIntToPtr(
    llvm_IRBuilderDefaultRef ref,
    llvm_ValueRef V,
    llvm_TypeRef DestTy,
    const char* NameData,
    size_t NameLength //
) {
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    auto v = reinterpret_cast<llvm::Value*>(V);
    auto dest_ty = reinterpret_cast<llvm::Type*>(DestTy);
    auto name = llvm::StringRef(NameData, NameLength);
    return reinterpret_cast<llvm_ValueRef>(builder->CreateIntToPtr(v, dest_ty, name));
}

llvm_ValueRef llvm_IRBuilderDefault_createPtrToInt(
    llvm_IRBuilderDefaultRef ref,
    llvm_ValueRef V,
    llvm_TypeRef DestTy,
    const char* NameData,
    size_t NameLength //
) {
    auto builder = reinterpret_cast<llvm::IRBuilder<>*>(ref);
    auto v = reinterpret_cast<llvm::Value*>(V);
    auto dest_ty = reinterpret_cast<llvm::Type*>(DestTy);
    auto name = llvm::StringRef(NameData, NameLength);
    return reinterpret_cast<llvm_ValueRef>(builder->CreatePtrToInt(v, dest_ty, name));
}

LLVM_C_EXTERN_C_END
