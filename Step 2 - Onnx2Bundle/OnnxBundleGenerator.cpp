#include "glow/Importer/ONNXModelLoader.h"

#include "glow/Base/Tensor.h"

#include "Loader.h"


#include <iostream>
using namespace glow;

ProtobufLoader *createProtobufLoader(Loader &loader, std::string inputTensorName, TypeRef inputType) {
    return new ONNXModelLoader(loader.getOnnxModelFilename(), {inputTensorName.c_str()}, {inputType}, *loader.getFunction());
}

int main(int argc, char **argv) {
    /// INPUT DECLARATION
    ShapeVector inputShape = {1, 64};
    Tensor *inputTensor = new Tensor(ElemKind::FloatTy, inputShape);

    /// CONST NAME DECLARATIONS
    std::string modelName = "gesture.onnx";
    std::string inputTensorName = "input_1_01";
    llvm::StringRef executionBackend = {"CPU"};

    PlaceholderBindings bindings;
    Loader loader(modelName, executionBackend);
    ProtobufLoader *LD = createProtobufLoader(loader, inputTensorName, &(inputTensor->getType()));
    bindings.allocate(loader.getModule()->getPlaceholders());
    loader.compile(bindings);

    return 0;
}
