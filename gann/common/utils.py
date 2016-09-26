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
