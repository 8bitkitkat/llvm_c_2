#pragma once

#include "../extern_c.h"

#include "BasicBlock.h"
#include "Constant.h"
#include "Context.h"
#include "Type.h"
#include "Value.h"

#include "stddef.h"

LLVM_C_EXTERN_C_BEGIN

typedef struct llvm_IRBuilderDefault_Opaque* llvm_IRBuilderDefaultRef;

llvm_IRBuilderDefaultRef llvm_IRBuilderDefault_create(llvm_ContextRef);

void llvm_IRBuilderDefault_dispose(llvm_IRBuilderDefaultRef);

void llvm_IRBuilderDefault_setInsertionPoint_BasicBlock(
    llvm_IRBuilderDefaultRef, llvm_BasicBlockRef);

llvm_ValueRef llvm_IRBuilderDefault_createAdd(
    llvm_IRBuilderDefaultRef,
    llvm_ValueRef LHS,
    llvm_ValueRef RHS,
    const char* NameData,
    size_t NameLength);

llvm_ValueRef llvm_IRBuilderDefault_createRet( //
    llvm_IRBuilderDefaultRef,
    // [[nullable]]
    llvm_ValueRef);

llvm_ValueRef llvm_IRBuilderDefault_createRetVoid(llvm_IRBuilderDefaultRef);

llvm_ValueRef llvm_IRBuilderDefault_createCall(
    llvm_IRBuilderDefaultRef,
    llvm_FunctionTypeRef Ty,
    llvm_ValueRef Callee,
    const llvm_ValueRef* ArgsData,
    size_t ArgsLength,
    const char* NameData,
    size_t NameLength);

llvm_ValueRef llvm_IRBuilderDefault_createAlloca(
    llvm_IRBuilderDefaultRef,
    llvm_TypeRef Ty,
    unsigned AddrSpace,
    // [nullable]
    llvm_ValueRef ArraySize /* = nullptr */,
    const char* NameData,
    size_t NameLength);

llvm_ValueRef llvm_IRBuilderDefault_createStore(
    llvm_IRBuilderDefaultRef, //
    llvm_ValueRef Val,
    llvm_ValueRef Ptr,
    bool isVolatile /* = false */);

llvm_ValueRef llvm_IRBuilderDefault_createGEP(
    llvm_IRBuilderDefaultRef,
    llvm_TypeRef Ty,
    llvm_ValueRef Ptr,
    llvm_ValueRef Idx,
    const char* NameData,
    size_t NameLength);

llvm_ValueRef llvm_IRBuilderDefault_createGEP_arr(
    llvm_IRBuilderDefaultRef,
    llvm_TypeRef Ty,
    llvm_ValueRef Ptr,
    const llvm_ValueRef* IdxListData,
    size_t IdxListLength,
    const char* NameData,
    size_t NameLength);

llvm_ValueRef llvm_IRBuilderDefault_createLoad(
    llvm_IRBuilderDefaultRef,
    llvm_TypeRef Ty,
    llvm_ValueRef Ptr,
    bool isVolatile,
    const char* NameData,
    size_t NameLength);

llvm_ConstantRef llvm_IRBuilderDefault_createGlobalString(
    llvm_IRBuilderDefaultRef ref,
    const char* StrData,
    size_t StrLength,
    const char* NameData,
    size_t NameLength,
    unsigned AddressSpace,
    // [[nullable]]
    llvm_ModuleRef M /* = nullptr */
);

llvm_ConstantRef llvm_IRBuilderDefault_createGlobalStringPtr(
    llvm_IRBuilderDefaultRef,
    const char* StrData,
    size_t StrLength,
    const char* NameData,
    size_t NameLength,
    unsigned AddressSpace,
    // [[nullable]]
    llvm_ModuleRef M /* = nullptr */
);

llvm_ValueRef llvm_IRBuilderDefault_createIntToPtr(
    llvm_IRBuilderDefaultRef,
    llvm_ValueRef V,
    llvm_TypeRef DestTy,
    const char* NameData,
    size_t NameLength);

llvm_ValueRef llvm_IRBuilderDefault_createPtrToInt(
    llvm_IRBuilderDefaultRef,
    llvm_ValueRef V,
    llvm_TypeRef DestTy,
    const char* NameData,
    size_t NameLength);

LLVM_C_EXTERN_C_END
