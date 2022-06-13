#pragma once

#include "../extern_c.h"

#include "stdbool.h"

LLVM_C_EXTERN_C_BEGIN

bool llvm_InitializeNativeTarget();

bool llvm_InitializeNativeTargetAsmPrinter();

bool llvm_InitializeNativeTargetAsmParser();

LLVM_C_EXTERN_C_END
