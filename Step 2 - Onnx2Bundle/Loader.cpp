/**
 * Copyright (c) 2017-present, Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Loader.h"

#include "glow/Base/Tensor.h"
#include "glow/Converter/TypeAToTypeBFunctionConverter.h"
#include "glow/IR/IR.h"
#include "glow/Quantization/Quantization.h"
#include "glow/Quantization/Serialization.h"
#include "glow/Runtime/RuntimeTypes.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/Timer.h"
#include "llvm/Support/raw_ostream.h"

#include <sstream>

using namespace glow;


static std::vector<std::unique_ptr<runtime::DeviceConfig>> generateDeviceConfigs(llvm::StringRef backendName) {
  std::vector<std::unique_ptr<runtime::DeviceConfig>> configs;

  auto config = llvm::make_unique<runtime::DeviceConfig>(backendName);
  configs.push_back(std::move(config));

  return configs;
}

void Loader::compile(PlaceholderBindings &bindings) {
    CompilationContext cctx{&bindings, &loweredMap_};
    PrecisionConfiguration &precConfig = cctx.precisionConfig;

    precConfig.convertToFP16 = false;

    auto module = M_.get();

    auto error = ::glow::optimizeFunction(F_, *backend_, cctx);
    EXIT_ON_ERR(std::move(error));
    backend_->save(F_, "bundle", "network");

}

Loader::Loader(std::string modelFilename, llvm::StringRef executionBackend) {
  onnxModelFilename_ = modelFilename;
  M_.reset(new Module);

  std::vector<std::unique_ptr<runtime::DeviceConfig>> configs = generateDeviceConfigs(executionBackend);

  hostManager_ = llvm::make_unique<runtime::HostManager>(std::move(configs));
  backend_ = createBackend(executionBackend);
  F_ = M_->createFunction(modelFilename);
  functionName_ = modelFilename;
}
