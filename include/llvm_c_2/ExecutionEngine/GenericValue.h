#pragma once

#include "../extern_c.h"

LLVM_C_EXTERN_C_BEGIN

typedef struct llvm_GenericValue_Opaque* llvm_GenericValueRef;

void llvm_GenericValue_free(llvm_GenericValueRef);

LLVM_C_EXTERN_C_END
