#pragma once

#include "Function.h"
#include "Module.h"
#include "../Support/raw_ostream.h"

#include "../extern_c.h"

LLVM_C_EXTERN_C_BEGIN

bool llvm_verifyFunction(
    const llvm_FunctionRef,
    // [[nullable]]
    llvm__raw_ostream__ref /* = nullptr */);

bool llvm_verifyModule(
    const llvm_ModuleRef,
    // [[nullable]]
    llvm__raw_ostream__ref /* = nullptr */,
    // [[nullable]]
    bool* BrokenDebugInfo /* = nullptr */);

LLVM_C_EXTERN_C_END
