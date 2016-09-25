import tensorflow as tf

from layer import Layer
from common.utils import random_tensor

class NDiscrete(Layer):
	def __init__(self, num_neurons, activation):
		self.num_neurons = num_neurons
		self.activation = activation
		super().__init__("n_discrete")

	def make_layer(self, prev_layer):
		input_tens= prev_layer.output()
		W = random_tensor(input_tens.shape[1:] + [num_neurons])
		b = random_tensor([num_neurons])
		self.output = activation(tf.matmul(input_tens, W) + b)
	
	def get_output(self):
		return self.output