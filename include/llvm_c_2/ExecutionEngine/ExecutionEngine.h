#pragma once

#include "../extern_c.h"

#include "../IR/Function.h"
#include "../IR/Module.h"
#include "GenericValue.h"

LLVM_C_EXTERN_C_BEGIN

typedef struct llvm_EngineBuilder_Opaque* llvm_EngineBuilderRef;

typedef struct llvm_ExecutionEngine_Opaque* llvm_ExecutionEngineRef;

// =-=-=-=-=-=-=-=
// EngineBuilder

llvm_EngineBuilderRef llvm_EngineBuilder_construct();

llvm_EngineBuilderRef llvm_EngineBuilder_construct_Module(llvm_ModuleRef);

void llvm_EngineBuilder_deconstruct(llvm_EngineBuilderRef);

llvm_ExecutionEngineRef llvm_EngineBuilder_create(llvm_EngineBuilderRef);

// =-=-=-=-=-=-=-=
// ExecutionEngine

void llvm_ExecutionEngine_deconstruct(llvm_ExecutionEngineRef);

llvm_FunctionRef llvm_ExecutionEngine_findFunctionNamed(
    llvm_ExecutionEngineRef, const char* NameData, size_t NameLength);

llvm_GenericValueRef llvm_ExecutionEngine_runFunction(
    llvm_ExecutionEngineRef,
    llvm_FunctionRef F,
    const llvm_GenericValueRef* ArgValuesData,
    size_t ArgValuesLength);

LLVM_C_EXTERN_C_END
