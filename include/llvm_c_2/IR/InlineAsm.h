#pragma once

#include "../extern_c.h"

#include "Type.h"
#include "Support/Error.h"

#include "stdbool.h"
#include "stddef.h"

LLVM_C_EXTERN_C_BEGIN

/// Safe to cast to a `llvm_FunctionRef`
typedef struct llvm_InlineAsm_Opaque* llvm_InlineAsmRef;

typedef enum {
    llvm_InlineAsm_AsmDialect_ATT,
    llvm_InlineAsm_AsmDialect_Intel,
} llvm_InlineAsm_AsmDialect;

llvm_InlineAsmRef llvm_InlineAsm_get(
    llvm_FunctionTypeRef,
    const char* AsmStringData,
    size_t AsmStringLength,
    const char* ConstraintsData,
    size_t ConstraintsLength,
    bool hasSideEffects,
    bool isAlignStack,         /* = false */
    llvm_InlineAsm_AsmDialect, /* = llvm_InlineAsm_AsmDialect_ATT */
    bool canThrow              /* = false */
);

llvm_ErrorRef llvm_InlineAsm_verify(
    llvm_FunctionTypeRef, const char* ConstraintsData, size_t ConstraintsLength);

LLVM_C_EXTERN_C_END
