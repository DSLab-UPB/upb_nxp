from keras.layers import *
from keras.models import *
from onnxmltools import convert_keras
import tensorflow as tf


# Add your own model names
keras_model_name = ''
onnx_model_name = ''

with tf.Session():
    # il define the input layer for the new model,
    # ol the output layer and
    # hdn the hidden ones
    il = None
    ol = None
    hdn = None

    model = load_model(model_name)

    # We keep the layers as in the original model,
    # with the exception of batch norm, which we replace with a lambda one
    # Note that some values are hard coded for our model (dense output, leaky relu alpha)
    for layer in model.layers:
        if layer.name == 'input':
            il = Input(shape=(layer.output_shape[1], ), name=layer.name)
            hdn = il
        elif layer.name == 'output':
            ol = Dense(7, activation='softmax', name=layer.name)(hdn)
        elif layer.name.startswith('hidden'):
            hdn = Dense(layer.output_shape[1], name=layer.name)(hdn)
            hdn = hdn
        elif layer.name.startswith('leaky'):
            hdn = LeakyReLU(0.1, name=layer.name)(hdn)
            hdn = hdn
        elif layer.name.startswith('batch'):
            center = layer.moving_mean.eval()
            offset = layer.beta.eval()
            rap = layer.gamma.eval() / np.sqrt(layer.moving_variance.eval() + 1e-3)
            hdn = Lambda(lambda ts: ts * rap + (offset - center * rap))(hdn)
            hdn = hdn

    # We create the new model
    nkm = Model(il, ol)

    # We load the original weights, where it s possible
    # In our case, this means in every dense
    for layer in nkm.layers:
        try:
            original_layer = model.get_layer(layer.name)
            layer.set_weights(original_layer.get_weights())
        except:
            pass

    # We convert and save the onnx model
    onnx_model = convert_keras(nkm)
    onnx.save_model(onnx_model, onnx_model_name)