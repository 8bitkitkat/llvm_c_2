#include "IR/Type.h"

#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Type.h"

#include "llvm/IR/DataLayout.h"

#include <vector>

namespace std {
void __throw_length_error(char const*) {
    abort();
}
void __throw_bad_array_new_length() {
    abort();
}
} // namespace std

LLVM_C_EXTERN_C_BEGIN

// =-=-=
// Type

llvm_TypeRef llvm_Type_getVoidTy(llvm_ContextRef ref) {
    auto ctx = reinterpret_cast<llvm::LLVMContext*>(ref);
    return reinterpret_cast<llvm_TypeRef>(llvm::Type::getVoidTy(*ctx));
}

llvm_TypeRef llvm_Type_getIntNTy(llvm_ContextRef ref, unsigned int N) {
    auto ctx = reinterpret_cast<llvm::LLVMContext*>(ref);
    return reinterpret_cast<llvm_TypeRef>(llvm::Type::getIntNTy(*ctx, N));
}

llvm_PointerTypeRef llvm_Type_getPointerTo(const llvm_TypeRef ref, unsigned AddrSpace) {
    auto ty = reinterpret_cast<const llvm::Type*>(ref);
    return reinterpret_cast<llvm_PointerTypeRef>(ty->getPointerTo(AddrSpace));
}

llvm_TypeID llvm_Type_getTypeID(const llvm_TypeRef ref) {
    auto ty = reinterpret_cast<const llvm::Type*>(ref);
    return static_cast<llvm_TypeID>(ty->getTypeID());
}

// =-=-=-=-=-=-=
// IntegerType

llvm_TypeRef llvm_IntegerType_get(llvm_ContextRef ctx_ref, unsigned int num_bits) {
    auto ctx = reinterpret_cast<llvm::LLVMContext*>(ctx_ref);
    return reinterpret_cast<llvm_TypeRef>(llvm::IntegerType::get(*ctx, num_bits));
}

llvm_TypeRef llvm_IntegerType_getInt64Ty(llvm_ContextRef ctx_ref) {
    auto ctx = reinterpret_cast<llvm::LLVMContext*>(ctx_ref);
    return reinterpret_cast<llvm_TypeRef>(llvm::IntegerType::getInt64Ty(*ctx));
}

// =-=-=-=-=-=-=
// FunctionType

llvm_FunctionTypeRef llvm_FunctionType_get(
    llvm_TypeRef Result, llvm_TypeRef* Params, size_t ParamsLength, bool isVarArg //
) {
    auto ret_ty = reinterpret_cast<llvm::Type*>(Result);
    auto args = std::vector<llvm::Type*>();
    for (size_t i = 0; i < ParamsLength; i++) {
        auto arg = reinterpret_cast<llvm::Type*>(Params[i]);
        args.emplace_back(arg);
    }
    return reinterpret_cast<llvm_FunctionTypeRef>(llvm::FunctionType::get(ret_ty, args, isVarArg));
}

// =-=-=-=-=-=
// StructType

llvm_StructTypeRef llvm_StructType_get(
    llvm_ContextRef ctx_ref,
    const llvm_TypeRef* ElementsData,
    size_t ElementsLength,
    bool isPacked //
) {
    auto ctx = reinterpret_cast<llvm::LLVMContext*>(ctx_ref);
    auto elems_data = reinterpret_cast<llvm::Type* const*>(ElementsData);
    auto elems = std::vector<llvm::Type*>(elems_data, elems_data + ElementsLength);
    return reinterpret_cast<llvm_StructTypeRef>(llvm::StructType::get(*ctx, elems, isPacked));
}

void llvm_StructType_setName(llvm_StructTypeRef ref, const char* NameData, size_t NameLength) {
    auto struct_type = reinterpret_cast<llvm::StructType*>(ref);
    auto name = llvm::StringRef(NameData, NameLength);
    struct_type->setName(name);
}

// =-=-=-=-=-=
// ArrayType

llvm_TypeRef llvm_ArrayType_get(llvm_TypeRef ElementType, uint64_t NumElements) {
    auto ty = reinterpret_cast<llvm::Type*>(ElementType);
    return reinterpret_cast<llvm_TypeRef>(llvm::ArrayType::get(ty, NumElements));
}

// =-=-=-=-=-=-=
// PointerType

llvm_PointerTypeRef llvm_PointerType_get(llvm_TypeRef ref, unsigned AddrSpace) {
    auto ty = reinterpret_cast<llvm::Type*>(ref);
    return reinterpret_cast<llvm_PointerTypeRef>(llvm::PointerType::get(ty, AddrSpace));
}

llvm_PointerTypeRef llvm_PointerType_getOpaque(llvm_ContextRef ref, unsigned AddrSpace) {
    auto ctx = reinterpret_cast<llvm::LLVMContext*>(ref);
    return reinterpret_cast<llvm_PointerTypeRef>(llvm::PointerType::get(*ctx, AddrSpace));
}

bool llvm_PointerType_isOpaque(const llvm_PointerTypeRef ref) {
    auto ty = reinterpret_cast<const llvm::PointerType*>(ref);
    return ty->isOpaque();
}

LLVM_C_EXTERN_C_END
