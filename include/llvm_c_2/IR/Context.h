#pragma once

#include "../extern_c.h"

LLVM_C_EXTERN_C_BEGIN

typedef struct llvm_Context_Opaque* llvm_ContextRef;

llvm_ContextRef llvm_Context_create();

void llvm_Context_dispose(llvm_ContextRef);

LLVM_C_EXTERN_C_END
