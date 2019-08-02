This is a Glow Tool that can convert an Onnx model to a bundle. As such, all files should be placed under a new folder in /glow/tools, folder that should be added to CMakeListst.txt of /glow/tools.

This tool is mainly inspired from image-classifier, but it's simplified by hard coding some values and supporting only Onnx.

The following changes should be made to support another model:
1. In OnnxBundleGenerator.cpp inputShape variable should have the shape of the input layer. This can be checked with Netron for example (https://lutzroeder.github.io/netron/)
2. In OnnxBundleGenerator.cpp modelName variable should have the name of the .onnx model.
3. In OnnxBundleGenerator.cpp inputTensorName variable should have the name of the input layer. This can be checked with Netron for example.
4. In Loader.cpp bundle folder name is hard coded as "bundle" (under backend->save).
5. In Loader.cpp network name is hard coded as "network" (under backend->save).

Also, please note that this tool work under a late May 2019 Glow version. Using the most recent version of Glow may cause the tool to stop working or misbehave.
