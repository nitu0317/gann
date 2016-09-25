import tensorflow as tf

from layer import Layer
from common.utils import random_tensor

class Input(Layer):
	def __init__(self, size):
		self.size = size
		super().__init__("input")

	def make_layer(self, prev_layer):
		self.output = tf.placeholder(dtype="float", shape=[None] + self.size, name="input")
	
	def get_output(self):
		return self.output