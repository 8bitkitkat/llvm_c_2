#pragma once

#include "../extern_c.h"

#include "Context.h"

#include "stddef.h"

LLVM_C_EXTERN_C_BEGIN

typedef struct llvm_Module_Opaque* llvm_ModuleRef;

llvm_ModuleRef llvm_Module_create(const char* idStringData, size_t idStringLength, llvm_ContextRef);

void llvm_Module_dispose(llvm_ModuleRef);

void llvm_Module_dump(llvm_ModuleRef);

LLVM_C_EXTERN_C_END
