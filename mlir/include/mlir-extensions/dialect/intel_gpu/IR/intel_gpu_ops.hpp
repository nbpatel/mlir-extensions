// Copyright 2022 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <mlir/Dialect/Tensor/IR/Tensor.h>
#include <mlir/IR/BuiltinTypes.h>
#include <mlir/IR/Dialect.h>
#include <mlir/IR/OpDefinition.h>
#include <mlir/IR/Types.h>
#include <mlir/Interfaces/ControlFlowInterfaces.h>
#include <mlir/Interfaces/LoopLikeInterface.h>
#include <mlir/Interfaces/SideEffectInterfaces.h>
#include <mlir/Interfaces/ViewLikeInterface.h>

#include <mlir/Dialect/GPU/GPUDialect.h>

#include "mlir-extensions/dialect/intel_gpu/IR/IntelGpuOpsDialect.h.inc"

#include "mlir-extensions/dialect/intel_gpu/IR/IntelGpuOpsEnums.h.inc"

#define GET_ATTRDEF_CLASSES
#include "mlir-extensions/dialect/intel_gpu/IR/IntelGpuOpsAttributes.h.inc"

#define GET_OP_CLASSES
#include "mlir-extensions/dialect/intel_gpu/IR/IntelGpuOps.h.inc"

// TODO: OpaqueType is not tied to gpu dialect. Move this or create separate
// types
namespace intel_gpu {
class OpaqueType : public ::mlir::Type::TypeBase<OpaqueType, ::mlir::Type,
                                                 ::mlir::TypeStorage> {
public:
  using Base::Base;

  static OpaqueType get(mlir::MLIRContext *context);
};

mlir::StringRef getGpuAccessibleAttrName();

} // namespace intel_gpu