import tensorflow as tf

from layer import Layer

LEARNING_RATE=1e-3

class GANN:
	def __init__(self, input_layer):
		"""
		Initializes a generalized artificial neural network.
		"""
		# TODO: Specify GPU usage if on GPU
		self.sess = tf.InteractiveSession()

		self._layers = []
		self.add_layer(input_layer)


	def forward(self, in_tens):
		result = self.sess.run(self.get_output_tensor(),
			{self.get_input_tensor(): in_tens})
		return result

	def train(self, inputs, desired):
		"""
		Trains the GANN.
		"""
		results, loss = self.sess.run([self.get_optimizer(), self.cost],
			{self.get_input_tensor(): inputs,
			self.get_desired_output_tensor(): desired})
		return loss



	########################################
	#             Construction             #
	########################################
	def add_layer(self, layer : Layer):
		"""
		Adds a layer to the GANN and calls make_layer
		"""
		prev_layer = self._layers[-1] if self._layers else None
		layer._add_to_network(prev_layer)
		print(
			"Adding layer: ", layer.get_output().name,
			 " with shape ", layer.get_shape())
		self._layers.append(layer)

	def finalize(self):
		self.sess.run(tf.initialize_all_variables())


	def make_training_method(self, loss=None, learning_rate=LEARNING_RATE):
		"""
		Makes a training method for the GANN.
		If the loss is unspecified, we use MSE.

		Returns the desired input and the optimizer.
		"""
		out_tens = self.get_output_tensor()

		# TODO: Add Batch Norm, L2 Regularization.
		self.y_input = tf.placeholder(dtype="float",shape=self.get_output_shape(),name="desired")
		if not loss:
			self.cost = tf.reduce_mean(tf.square(self.y_input - out_tens)) 
		else:
			self.cost = loss(self.y_input, out_tens)
		self.optimizer = tf.train.AdamOptimizer(learning_rate).minimize(self.cost)

		return self.y_input, self.optimizer



	########################################
	#             Getters/Setters          #
	########################################
	def get_output_tensor(self):
		return self._layers[-1].get_output()

	def get_output_shape(self):
		return self._layers[-1].get_shape()

	def get_input_tensor(self):
		# Slightly jank.
		return self._layers[0].get_output()

	def get_optimizer(self):
		return self.optimizer

	def get_desired_output_tensor(self):
		return self.y_input