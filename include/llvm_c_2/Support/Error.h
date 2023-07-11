#pragma once

#include "../extern_c.h"

#ifndef __cplusplus
#    include "stdbool.h"
#endif

LLVM_C_EXTERN_C_BEGIN

typedef struct llvm_Error_Opaque* llvm_ErrorRef;

void llvm_Error_dispose(llvm_ErrorRef);

bool llvm_Error_asBoolean(llvm_ErrorRef);

LLVM_C_EXTERN_C_END
