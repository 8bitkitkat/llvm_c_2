#include "IR/Constant.h"

#include "llvm/ADT/APInt.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Type.h"

#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/GlobalVariable.h"

LLVM_C_EXTERN_C_BEGIN

llvm_ConstantRef llvm_Constant_getIntegerValue(llvm_TypeRef ref, uint64_t val) {
    auto type = reinterpret_cast<llvm::IntegerType*>(ref);
    auto i = llvm::APInt(type->getBitWidth(), val);
    return reinterpret_cast<llvm_ConstantRef>(llvm::Constant::getIntegerValue(type, i));
    // llvm::GlobalVariable()
}

LLVM_C_EXTERN_C_END
