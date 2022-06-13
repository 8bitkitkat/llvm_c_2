#pragma once

#include "../extern_c.h"

#include "Module.h"
#include "Type.h"

// #include "stddef.h"
// #include "stdint.h"
// #ifndef __cplusplus
// #    include "stdbool.h"
// #endif

LLVM_C_EXTERN_C_BEGIN

typedef struct llvm_DataLayout_Opaque* llvm_DataLayoutRef;

llvm_DataLayoutRef llvm_DataLayout_create(llvm_ModuleRef);

void llvm_DataLayout_dispose(llvm_DataLayoutRef);

LLVM_C_EXTERN_C_END
