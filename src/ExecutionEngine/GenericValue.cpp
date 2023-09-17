#include "ExecutionEngine/GenericValue.h"

#include "llvm/ExecutionEngine/GenericValue.h"

#include <cstdlib>

LLVM_C_EXTERN_C_BEGIN

void llvm_GenericValue_free(llvm_GenericValueRef ref) {
    auto val = reinterpret_cast<llvm::GenericValue*>(ref);
    free(val);
}

LLVM_C_EXTERN_C_END
