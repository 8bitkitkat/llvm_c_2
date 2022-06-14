#pragma once

#include "../extern_c.h"

#include "Context.h"
#include "Function.h"

#include "stddef.h"

LLVM_C_EXTERN_C_BEGIN

typedef struct llvm_BasicBlock_Opaque* llvm_BasicBlockRef;

llvm_BasicBlockRef llvm_BasicBlock_create(
    llvm_ContextRef,
    const char* NameData,
    size_t NameLength,
    // [[nullable]]
    llvm_FunctionRef Parent /* = nullptr */,
    // [[nullable]]
    llvm_BasicBlockRef InsertBefore /* = nullptr */);

void llvm_BasicBlock_dispose(llvm_BasicBlockRef);

LLVM_C_EXTERN_C_END
