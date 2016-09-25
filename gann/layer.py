from abc import ABCMeta
from abc import abstractmethod

import tensorflow as tf

class Layer(metaclass=ABCMeta):
	def __init__(name="GANNLayer"):
		"""
		Instantiates a layer object.
		This is used for storing hyper parameters.
		Gives it a default name, "GANNLayer".
		"""
		self.name = name

	@abstractmethod
	def make_layer(prev_layer):
		"""
		Makes the layer and returns the output tensor.
		Args:
		    prev_layer - The previous layer tensor.
		"""
		return NotImplemented

	#####################################
	# Private Hooks
	####################################
	def _add_to_network(prev_layer):
		with tf.variable_scope(self.name):
			output = make_layer(prev_layer)
		if not output:
			raise RuntimeError("make_layer must return a layer tensor")

		return output 