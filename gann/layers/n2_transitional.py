import tensorflow as tf
import numpy as np

from layer import Layer
from common.utils import random_tensor

class N2Transitional(Layer):
	def __init__(self, coefficient_shape, activation=tf.nn.relu):
		"""
		Creates an N2Transitional layer. Assumes the previous layer outputs samples of a function.
		Args:
		"""
		self.coefficient_shape = coefficient_shape
		self.activation = activation
		super().__init__("n2_transitional")

	def make_layer(self, prev_layer):
		if not hasattr(prev_layer, "partition"):
			raise RuntimeError("Previous layer has no continuous domain.")
		p = prev_layer.partition
		xi = prev_layer.get_output()
		K = random_tensor(self.coefficient_shape)
		b = random_tensor(self.coefficient_shape[1:])

		# Do affine numerical integration against a weight polynomial
		# described by coefficients.

		i_samp = prev_layer.get_shape()[-1]

		def make_diff_op(n,k):
			if k == n:
				return -1.0
			elif k == n+1:
				return 1.0
			else:
				return 0
		diffOp = tf.constant(
			np.array([[make_diff_op(d,n) for n in range(i_samp -1)]
				for d in range(i_samp)], dtype="float32"),
			name="diffOp")
		t= tf.matmul(xi, diffOp)

		def make_i_coeff(x, n):
			# Calculates the integral of xi(i)w(i,j)di from a to b
			a = p[n]
			b = p[n+1]
			return (a**(x+2) - (x+2)*a*b**(x+1) + (x+1)*b**(x+2))/((x+2)*(x+1)*(p[n+1]-p[n]))

		I = tf.constant(
			np.array(
				[[make_i_coeff(x,n) for x in range(self.coefficient_shape[0])] for n in range(len(p) -1)],
				dtype="float32"),
				name="I")

		net = tf.matmul(tf.matmul(t, I), K)
		self.output = self.activation(net + b)
	
	def get_output(self):
		return self.output