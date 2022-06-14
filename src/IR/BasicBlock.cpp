#include "IR/BasicBlock.h"

#include "llvm/IR/BasicBlock.h"

LLVM_C_EXTERN_C_BEGIN

llvm_BasicBlockRef llvm_BasicBlock_create(
    llvm_ContextRef ctx_ref,
    const char* NameData,
    size_t NameLength,
    llvm_FunctionRef Parent,
    llvm_BasicBlockRef InsertBefore //
) {
    auto ctx = reinterpret_cast<llvm::LLVMContext*>(ctx_ref);
    auto name = llvm::StringRef(NameData, NameLength);
    auto parent = reinterpret_cast<llvm::Function*>(Parent);
    auto insert_before = reinterpret_cast<llvm::BasicBlock*>(InsertBefore);
    return reinterpret_cast<llvm_BasicBlockRef>(
        llvm::BasicBlock::Create(*ctx, name, parent, insert_before));
}

void llvm_BasicBlock_dispose(llvm_BasicBlockRef ref) {
    auto bb = reinterpret_cast<llvm::BasicBlock*>(ref);
    bb->~BasicBlock();
}

LLVM_C_EXTERN_C_END
