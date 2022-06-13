#include "ExecutionEngine/ExecutionEngine.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"

template <typename T>
static T* T_malloc() {
    return (T*)malloc(sizeof(T));
}

LLVM_C_EXTERN_C_BEGIN

// =-=-=-=-=-=-=-=
// EngineBuilder

llvm_EngineBuilderRef llvm_EngineBuilder_construct() {
    return reinterpret_cast<llvm_EngineBuilderRef>(new llvm::EngineBuilder());
}

llvm_EngineBuilderRef llvm_EngineBuilder_construct_Module(llvm_ModuleRef ref) {
    auto mod = reinterpret_cast<llvm::Module*>(ref);
    return reinterpret_cast<llvm_EngineBuilderRef>(
        new llvm::EngineBuilder(static_cast<std::unique_ptr<llvm::Module>>(mod)));
}

void llvm_EngineBuilder_deconstruct(llvm_EngineBuilderRef ref) {
    return delete reinterpret_cast<llvm::EngineBuilder*>(ref);
}

llvm_ExecutionEngineRef llvm_EngineBuilder_create(llvm_EngineBuilderRef ref) {
    auto eb = reinterpret_cast<llvm::EngineBuilder*>(ref);
    return reinterpret_cast<llvm_ExecutionEngineRef>(eb->create());
}

// =-=-=-=-=-=-=-=
// ExecutionEngine

void llvm_ExecutionEngine_deconstruct(llvm_ExecutionEngineRef ref) {
    auto ee = reinterpret_cast<llvm::ExecutionEngine*>(ref);
    ee->~ExecutionEngine();
}

llvm_FunctionRef llvm_ExecutionEngine_findFunctionNamed(
    llvm_ExecutionEngineRef ref, const char* NameData, size_t NameLength //
) {
    auto ee = reinterpret_cast<llvm::ExecutionEngine*>(ref);
    auto name = llvm::StringRef(NameData, NameLength);
    return reinterpret_cast<llvm_FunctionRef>(ee->FindFunctionNamed(name));
}

llvm_GenericValueRef llvm_ExecutionEngine_runFunction(
    llvm_ExecutionEngineRef ref,
    llvm_FunctionRef F,
    const llvm_GenericValueRef* ArgValuesData,
    size_t ArgValuesLength //
) {
    auto ee = reinterpret_cast<llvm::ExecutionEngine*>(ref);
    auto f = reinterpret_cast<llvm::Function*>(F);

    auto args = std::vector<llvm::GenericValue>();
    for (uint i = 0; i < ArgValuesLength; i++) {
        args.emplace_back(ArgValuesData[i]);
    }

    auto ret = T_malloc<llvm::GenericValue>();
    *ret = ee->runFunction(f, args);
    return reinterpret_cast<llvm_GenericValueRef>(ret);
}

LLVM_C_EXTERN_C_END
