#pragma once

#include "../extern_c.h"

#include "Type.h"

#include "stdint.h"

LLVM_C_EXTERN_C_BEGIN

/// Safe to cast to `LLVM_IR_ValueRef`
typedef struct llvm_Constant_Opaque* llvm_ConstantRef;

llvm_ConstantRef llvm_Constant_getIntegerValue(llvm_IntegerTypeRef, uint64_t);

llvm_ConstantRef llvm_Constant_getNullValue(llvm_TypeRef);

LLVM_C_EXTERN_C_END
