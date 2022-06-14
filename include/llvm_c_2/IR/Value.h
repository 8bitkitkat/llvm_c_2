#pragma once

#include "../extern_c.h"

#include "Type.h"

LLVM_C_EXTERN_C_BEGIN

typedef struct llvm_Value_Opaque* llvm_ValueRef;

llvm_TypeRef llvm_Value_getType(llvm_ValueRef);

LLVM_C_EXTERN_C_END
