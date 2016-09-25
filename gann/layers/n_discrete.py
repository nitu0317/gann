import tensorflow as tf

from layer import Layer

class NDiscrete(Layer):
	def __init__(num_neurons, activation):
		self.num_neurons = num_neurons
		self.activation = activation
		super().__init__("n_discrete")

	def make_layer(prev_layer):
		W1 =