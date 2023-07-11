#include "Support/Error.h"

#include <llvm/Support/Error.h>

LLVM_C_EXTERN_C_BEGIN

void llvm_Error_dispose(llvm_ErrorRef ref) {
    auto err = reinterpret_cast<llvm::Error*>(ref);
    delete err;
}

bool llvm_Error_asBoolean(llvm_ErrorRef ref) {
    auto error = reinterpret_cast<llvm::Error*>(ref);
    return (bool)error;
}

LLVM_C_EXTERN_C_END
