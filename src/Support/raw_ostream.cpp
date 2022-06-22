#include "Support/raw_ostream.h"

#include "llvm/Support/raw_ostream.h"

LLVM_C_EXTERN_C_BEGIN

llvm__raw_fd_ostream__ref llvm__raw_fd_ostream__create(int fd, bool shouldClose, bool unbuffered, llvm_OStreamKind K) {
    return reinterpret_cast<llvm__raw_fd_ostream__ref>(
        new llvm::raw_fd_ostream(fd, shouldClose, unbuffered, static_cast<llvm::raw_ostream::OStreamKind>(K)));
}

void llvm__raw_fd_ostream__dispose(llvm__raw_fd_ostream__ref ref) {
    delete reinterpret_cast<llvm::raw_fd_ostream*>(ref);
}

LLVM_C_EXTERN_C_END
