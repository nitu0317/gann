import tensorflow as tf
import numpy as np

from layer import Layer
from common.utils import random_tensor

class OOperational(Layer):
	def __init__(self, interval, num_samples, coefficient_shape, activation=tf.nn.relu):
		"""
		Creates an OOperational layer. Assumes the previous layer outputs samples of a function.
		Args:
		    - num_samples. The number of samples desired for the output
		    - coefficient_shape. The number of coefficients in the polynomial kernel [4,4].
		"""
		self.num_samples = num_samples
		a,b = interval
		self.partition = np.array([a+ (b-a)/num_samples*n for n in range(num_samples)])
		self.coefficient_shape = coefficient_shape
		self.activation = activation
		super().__init__("o_operational")

	def make_layer(self, prev_layer):
		if not hasattr(prev_layer, "partition"):
			raise RuntimeError("Previous layer has no continuous domain.")
		p = prev_layer.partition
		gamma = self.partition

		xi = prev_layer.get_output()
		X, Y = self.coefficient_shape
		K = random_tensor(self.coefficient_shape)

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
				[[make_i_coeff(x,n) for x in range(X)] for n in range(len(p) -1)],
				dtype="float32"),
				name="I")
		Gamma = tf.constant(np.array([gamma**y for y in range(Y)], dtype="float32"), name="Gamma")

		net = tf.matmul(tf.matmul(tf.matmul(t, I), K), Gamma) 
		self.output = self.activation(net)
	
	def get_output(self):
		return self.output