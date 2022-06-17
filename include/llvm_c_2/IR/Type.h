#pragma once

#include "../extern_c.h"

#include "Context.h"

#include "stdbool.h"
#include "stddef.h"
#include "stdint.h"

LLVM_C_EXTERN_C_BEGIN

typedef struct llvm_Type_Opaque* llvm_TypeRef;

/// Safe to cast to `llvm_TypeRef`
typedef struct llvm_IntegerType_Opaque* llvm_IntegerTypeRef;

/// Safe to cast to `llvm_TypeRef`
typedef struct llvm_FunctionType_Opaque* llvm_FunctionTypeRef;

/// Safe to cast to `llvm_TypeRef`
typedef struct llvm_StructType_Opaque* llvm_StructTypeRef;

/// Safe to cast to `llvm_TypeRef`
typedef struct llvm_PointerType_Opaque* llvm_PointerTypeRef;

// llvm::Type::TypeID
typedef enum {
    // PrimitiveTypes
    llvm_TypeID_Half = 0,  ///< 16-bit floating point type
    llvm_TypeID_BFloat,    ///< 16-bit floating point type (7-bit significand)
    llvm_TypeID_Float,     ///< 32-bit floating point type
    llvm_TypeID_Double,    ///< 64-bit floating point type
    llvm_TypeID_X86_FP80,  ///< 80-bit floating point type (X87)
    llvm_TypeID_FP128,     ///< 128-bit floating point type (112-bit significand)
    llvm_TypeID_PPC_FP128, ///< 128-bit floating point type (two 64-bits, PowerPC)
    llvm_TypeID_Void,      ///< type with no size
    llvm_TypeID_Label,     ///< Labels
    llvm_TypeID_Metadata,  ///< Metadata
    llvm_TypeID_X86_MMX,   ///< MMX vectors (64 bits, X86 specific)
    llvm_TypeID_X86_AMX,   ///< AMX vectors (8192 bits, X86 specific)
    llvm_TypeID_Token,     ///< Tokens

    // Derived types... see DerivedTypes.h file.
    llvm_TypeID_Integer,       ///< Arbitrary bit width integers
    llvm_TypeID_Function,      ///< Functions
    llvm_TypeID_Pointer,       ///< Pointers
    llvm_TypeID_Struct,        ///< Structures
    llvm_TypeID_Array,         ///< Arrays
    llvm_TypeID_FixedVector,   ///< Fixed width SIMD vector type
    llvm_TypeID_ScalableVector ///< Scalable SIMD vector type
} llvm_TypeID;

// =-=-=
// Type

llvm_TypeRef llvm_Type_getVoidTy(llvm_ContextRef);

llvm_IntegerTypeRef llvm_Type_getIntNTy(llvm_ContextRef, unsigned int N);

llvm_PointerTypeRef llvm_Type_getPointerTo(const llvm_TypeRef, unsigned AddrSpace);

llvm_TypeID llvm_Type_getTypeID(const llvm_TypeRef);

// =-=-=-=-=-=-=
// IntegerType

llvm_IntegerTypeRef llvm_IntegerType_get(llvm_ContextRef, unsigned int num_bits);

llvm_IntegerTypeRef llvm_IntegerType_getInt64Ty(llvm_ContextRef);

// =-=-=-=-=-=-=
// FunctionType

llvm_FunctionTypeRef llvm_FunctionType_get(
    llvm_TypeRef Result, llvm_TypeRef const* Params, size_t ParamsLength, bool isVarArg);

// =-=-=-=-=-=
// StructType

llvm_StructTypeRef llvm_StructType_get(
    llvm_ContextRef,
    const llvm_TypeRef* ElementsData,
    size_t ElementsLength,
    bool isPacked /* = false */
);

// bool llvm_StructType_hasName(const llvm_StructTypeRef);
// StringRef llvm_StructType_getName(const llvm_StructTypeRef);
void llvm_StructType_setName(llvm_StructTypeRef, const char* NameData, size_t NameLength);

// =-=-=-=-=-=
// ArrayType

llvm_TypeRef llvm_ArrayType_get(llvm_TypeRef ElementType, uint64_t NumElements);

// =-=-=-=-=-=-=
// PointerType

llvm_PointerTypeRef llvm_PointerType_get(llvm_TypeRef, unsigned AddrSpace);

llvm_PointerTypeRef llvm_PointerType_getOpaque(llvm_ContextRef, unsigned AddrSpace);

bool llvm_PointerType_isOpaque(const llvm_PointerTypeRef);

LLVM_C_EXTERN_C_END
