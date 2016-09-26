import tensorflow as tf
import numpy as np
import math

def random_tensor(shape, fanning=1.2):
	"""
	Makes a random tesnor with a given shape and a certain fanning.
	"""
	with tf.variable_scope("parameter"):
		var= tf.Variable(tf.random_uniform(shape,-1/math.sqrt(fanning),1/math.sqrt(fanning)))
	return var


def sample_function(f ,interval, num_sample):
	a,b = interval
	return np.array([[f(a + (b-a)/num_sample*n) for n in range(num_sample)]], dtype="float32")

def get_derivative(f, interval, num_sample):
		a,b = interval

		def make_diff_op(n,k):
			if k == n:
				return -1.0
			elif k == n+1:
				return 1.0
			else:
				return 0
		diffOp = tf.constant(
			np.array([[make_diff_op(d,n) for n in range(num_sample -1)]
				for d in range(num_sample)], dtype="float32"),
			name="diffOp")
		t= tf.matmul(f, diffOp)

		samps = np.array([[a + (b-a)/num_sample*n for n in range(num_sample)]], dtype="float32")
		delta = tf.matmul(samps, diffOp)

		return t / delta