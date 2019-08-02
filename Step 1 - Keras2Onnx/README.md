This Python script transforms a model from keras to Onnx, using Keras2Onnx package (https://github.com/onnx/keras-onnx).

However, we had a problem with the conversion of BatchNormalization layer, so we implemented a solution which consists of replacing the BatchNormalization layer with a Lambda one. This script also does, that.

Please be careful that some values are hard coded for our model. Also, the Keras2Onnx package may have other bugs we are not aware of.