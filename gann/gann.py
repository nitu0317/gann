import tensorflow as tf


from layer import Layer
from layers.input import Input

class GANN:
	def __init__(self, input_shape):
		"""
		Initializes a generalized artificial neural network.
		"""
		# TODO: Specify GPU usage if on GPU
		self.sess = tf.InteractiveSession()

		# Make the inputs
		in_layer = Input(input_shape)
		in_layer._add_to_network(None):
		self._layers = [in_layer]


	def forward(self, in_tens):
		result = self.sess.run(self.get_output_tensor(),
			{self.get_input_op: in_tens})
		return result


	########################################
	#             Construction             #
	########################################
	def add_layer(self, layer : Layer):
		"""
		Adds a layer to the GANN and calls make_layer
		"""
		layer._add_to_network(self._layers[-1])
		self._layers.append(layer)


	def make_training_method(self, loss=None):
		"""
		Makes a training method for the GANN.
		If the loss is unspecified, we use MSE.

		Returns the desired input and the optimizer.
		"""
		out_tens = self.get_output_tensor()

		# TODO: Add Batch Norm, L2 Regularization.
		self.y_input = tf.placeholder(dtype="float",shape=out_tens.shape,name="desired")
		self.cost = tf.reduce_mean(tf.square(self.y_input - out_tens)) 
		self.optimizer = tf.train.AdamOptimizer(LEARNING_RATE).minimize(self.cost)

		return self.y_input, self.optimizer



	########################################
	#             Getters/Setters          #
	########################################
	def get_output_tensor(self):
		return self._layers[-1].get_output()

	def get_input_op(self):
		# Slightly jank.
		return self.layers[0].get_output()

	def get_optimizer_op(self):
		return self.optimizer

	def get_desired_output_op(self):
		return self.y_input