#pragma once

#include "../extern_c.h"

#include "Module.h"
#include "Type.h"
#include "Value.h"

#include "stddef.h"

LLVM_C_EXTERN_C_BEGIN

/// Safe to cast to `LLVM_IR_ValueRef`
typedef struct llvm_Function_Opaque* llvm_FunctionRef;

typedef enum {
    llvm_LinkageType_ExternalLinkage = 0,        ///< Externally visible function
    llvm_LinkageType_AvailableExternallyLinkage, ///< Available for inspection, not emission.
    llvm_LinkageType_LinkOnceAnyLinkage,  ///< Keep one copy of function when linking (inline)
    llvm_LinkageType_LinkOnceODRLinkage,  ///< Same, but only replaced by something equivalent.
    llvm_LinkageType_WeakAnyLinkage,      ///< Keep one copy of named function when linking (weak)
    llvm_LinkageType_WeakODRLinkage,      ///< Same, but only replaced by something equivalent.
    llvm_LinkageType_AppendingLinkage,    ///< Special purpose, only applies to global arrays
    llvm_LinkageType_InternalLinkage,     ///< Rename collisions when linking (static functions).
    llvm_LinkageType_PrivateLinkage,      ///< Like Internal, but omit from symbol table.
    llvm_LinkageType_ExternalWeakLinkage, ///< ExternalWeak linkage description.
    llvm_LinkageType_CommonLinkage        ///< Tentative definitions.
} llvm_LinkageType;

llvm_FunctionRef llvm_Function_create(
    llvm_FunctionTypeRef,
    llvm_LinkageType Linkage,
    unsigned int AddrSpace,
    const char* NameData,
    size_t NameLength,
    // [[nullable]]
    llvm_ModuleRef /* = nullptr */);

void llvm_Function_dispose(llvm_FunctionRef);

llvm_ValueRef llvm_Function_getArg(llvm_FunctionRef, unsigned int i);

LLVM_C_EXTERN_C_END
