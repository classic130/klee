//===-- ubsan_handlers.h ----------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Entry points to the runtime library for Clang's undefined behavior sanitizer.
//
//===----------------------------------------------------------------------===//
#ifndef UBSAN_HANDLERS_H
#define UBSAN_HANDLERS_H

#include "ubsan_value.h"

#include "klee/Config/Version.h"

using namespace __ubsan;

struct TypeMismatchData {
  SourceLocation Loc;
  const TypeDescriptor &Type;
#if LLVM_VERSION_MAJOR >= 4
  unsigned char LogAlignment;
#else
  uptr Alignment;
#endif
  unsigned char TypeCheckKind;
};

#if LLVM_VERSION_MAJOR >= 8
struct AlignmentAssumptionData {
  SourceLocation Loc;
  SourceLocation AssumptionLoc;
  const TypeDescriptor &Type;
};
#endif

struct OverflowData {
  SourceLocation Loc;
  const TypeDescriptor &Type;
};

struct ShiftOutOfBoundsData {
  SourceLocation Loc;
  const TypeDescriptor &LHSType;
  const TypeDescriptor &RHSType;
};

struct OutOfBoundsData {
  SourceLocation Loc;
  const TypeDescriptor &ArrayType;
  const TypeDescriptor &IndexType;
};

struct UnreachableData {
  SourceLocation Loc;
};

struct VLABoundData {
  SourceLocation Loc;
  const TypeDescriptor &Type;
};

struct InvalidValueData {
  SourceLocation Loc;
  const TypeDescriptor &Type;
};

#if LLVM_VERSION_MAJOR >= 7
/// Known implicit conversion check kinds.
/// Keep in sync with the enum of the same name in CGExprScalar.cpp
enum ImplicitConversionCheckKind : unsigned char {
  ICCK_IntegerTruncation = 0, // Legacy, was only used by clang 7.
  ICCK_UnsignedIntegerTruncation = 1,
  ICCK_SignedIntegerTruncation = 2,
  ICCK_IntegerSignChange = 3,
  ICCK_SignedIntegerTruncationOrSignChange = 4,
};
#endif

#if LLVM_VERSION_MAJOR >= 7
struct ImplicitConversionData {
  SourceLocation Loc;
  const TypeDescriptor &FromType;
  const TypeDescriptor &ToType;
  /* ImplicitConversionCheckKind */ unsigned char Kind;
};
#endif

#if LLVM_VERSION_MAJOR >= 6
struct InvalidBuiltinData {
  SourceLocation Loc;
  unsigned char Kind;
};
#endif

struct NonNullReturnData {
  SourceLocation AttrLoc;
};

struct NonNullArgData {
  SourceLocation Loc;
  SourceLocation AttrLoc;
  int ArgIndex;
};

#if LLVM_VERSION_MAJOR >= 5
struct PointerOverflowData {
  SourceLocation Loc;
};
#endif

#endif // UBSAN_HANDLERS_H