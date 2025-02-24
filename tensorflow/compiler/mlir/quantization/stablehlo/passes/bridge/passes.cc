/* Copyright 2023 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/compiler/mlir/quantization/stablehlo/passes/bridge/passes.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"  // from @llvm-project
#include "mlir/Pass/PassManager.h"  // from @llvm-project
#include "mlir/Pass/PassOptions.h"  // from @llvm-project
#include "mlir/Transforms/Passes.h"  // from @llvm-project

namespace mlir {
namespace stablehlo {

void AddQuantizationLoweringPasses(mlir::OpPassManager& pm) {
  // These passes are grouped together and must run in this specific order.
  pm.addNestedPass<mlir::func::FuncOp>(CreateConvertTFQuantOpsToMHLOPass());
  pm.addNestedPass<mlir::func::FuncOp>(
      createConvertMHLOQuantToIntPass(/*legalize_chlo=*/false));
  pm.addNestedPass<mlir::func::FuncOp>(mlir::createCanonicalizerPass());
}

}  // namespace stablehlo
}  // namespace mlir
