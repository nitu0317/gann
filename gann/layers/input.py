import tensorflow as tf
import numpy as np

from layer import Layer
from common.utils import random_tensor

class DiscreteInput(Layer):
	def __init__(self, size):
		self.size = size
		super().__init__("input")

	def make_layer(self, prev_layer):
		self.output = tf.placeholder(dtype="float32", shape=[None] + self.size, name="input")
	
	def get_output(self):
		return self.output

class ContinuousInput(DiscreteInput):
	def __init__(self, interval, num_samples):
		super().__init__([num_samples])
		a,b = interval
		self.partition = np.array([a + (b-a)/num_samples*n for n in range(num_samples)], dtype="float32")