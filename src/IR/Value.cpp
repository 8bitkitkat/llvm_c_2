#include "IR/Value.h"

#include "llvm/IR/Value.h"

LLVM_C_EXTERN_C_BEGIN

llvm_TypeRef llvm_Value_getType(llvm_ValueRef ref) {
    auto value = reinterpret_cast<llvm::Value*>(ref);
    return reinterpret_cast<llvm_TypeRef>(value->getType());
}

LLVM_C_EXTERN_C_END
