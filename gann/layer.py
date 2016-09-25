from abc import ABCMeta
from abc import abstractmethod

import tensorflow as tf

class Layer(metaclass=ABCMeta):
	def __init__(self, name="GANNLayer"):
		"""
		Instantiates a layer object.
		This is used for storing hyper parameters.
		Gives it a default name, "GANNLayer".
		"""
		self.name = name

	@abstractmethod
	def make_layer(self, prev_layer):
		"""
		Makes the layer given the previous layers output
		Args:
		    prev_layer - The previous layer tensor.
		"""
		return NotImplemented

	@abstractmethod
	def get_output(self):
		"""
		Returns the the layers output tensor.
		"""
		return NotImplemented

	#####################################
	# Private Hooks
	####################################
	def _add_to_network(self, prev_layer):
		with tf.variable_scope(self.name):
			make_layer(prev_layer)