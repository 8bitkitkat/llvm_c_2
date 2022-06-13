#pragma once

#ifdef __cplusplus
#    define LLVM_C_EXTERN_C_BEGIN extern "C" {
#    define LLVM_C_EXTERN_C_END }
#else
#    define LLVM_C_EXTERN_C_BEGIN
#    define LLVM_C_EXTERN_C_END
#endif
