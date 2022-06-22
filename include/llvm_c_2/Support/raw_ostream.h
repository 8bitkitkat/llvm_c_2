#pragma once

#include "../extern_c.h"

LLVM_C_EXTERN_C_BEGIN

typedef struct llvm__raw_ostream__opaque* llvm__raw_ostream__ref;

/// Safe to cast to `llvm__raw_ostream__ref`
typedef struct llvm__raw_fd_ostream__opaque* llvm__raw_fd_ostream__ref;

typedef enum {
    llvm_OStreamKind__OK_OStream,
    llvm_OStreamKind__OK_FDStream,
} llvm_OStreamKind;

llvm__raw_fd_ostream__ref llvm__raw_fd_ostream__create(int fd, bool shouldClose, bool unbuffered /* = false */, llvm_OStreamKind K /* = llvm_OStreamKind__OK_OStream */);

void llvm__raw_fd_ostream__dispose(llvm__raw_fd_ostream__ref);

LLVM_C_EXTERN_C_END
