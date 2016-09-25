def random_tensor(shape, fanning=1):
	"""
	Makes a random tesnor with a given shape and a certain fanning.
	"""
	with tf.variable_scope("parameter"):
		var= tf.Variable(tf.random_uniform(shape,-1/math.sqrt(fanning),1/math.sqrt(fanning)))
	return var

	
