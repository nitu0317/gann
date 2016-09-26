"""
A ONN implemented using the GANN framework.
"""
import tensorflow as tf
import numpy as np

from gann import GANN
from layers.n2_transitional import N2Transitional
from layers.input import ContinuousInput
from layers.input import DiscreteInput
from layers.n_discrete import NDiscrete
from common.utils import sample_function

import matplotlib.pyplot as plt
plt.ion()


def make_random_polynomial(order):
	coeff = [np.random.rand(1) for k in range(order)]
	def func(x):
		nonlocal coeff
		tot = 0
		for i, k in enumerate(coeff):
			tot+= (k)*x**(i+1)
		return tot
	return func

MAX_ORDER = 50
NUM_DP = 10000
TEST_SET = 1000

def main():
	"""
	A continuous classifier learning to classify sin curves.
	"""

	tf.set_random_seed(20)
	with tf.variable_scope("ccnn"):
		g = GANN(ContinuousInput((-1,1),100))
		g.add_layer(N2Transitional([20, 20], activation=tf.nn.relu))
		g.add_layer(NDiscrete(30, activation=tf.nn.relu))
		g.add_layer(NDiscrete(MAX_ORDER, activation=tf.nn.sigmoid))
		g.make_training_method(learning_rate=3e-2)
		g.finalize()

	tf.set_random_seed(20)
	with tf.variable_scope("discrete"):
		n = GANN(DiscreteInput([100]))
		n.add_layer(NDiscrete(20, activation=tf.nn.relu))
		n.add_layer(NDiscrete(30, activation=tf.nn.relu))
		n.add_layer(NDiscrete(MAX_ORDER, activation=tf.nn.sigmoid))
		n.make_training_method(learning_rate=3e-2)
		n.finalize()

	

	X = []
	Y = []
	for o in range(NUM_DP):
		order = np.random.randint(MAX_ORDER)
		X.append(sample_function(make_random_polynomial(order), (-1,1), 100).flatten())
		Y.append(np.array([1 if k == order else 0 for k in range(MAX_ORDER)]))

	# Test the training function
	for i in range(10000):

		loss = g.train(
				np.asarray(X[:-TEST_SET]),
				np.asarray(Y[:-TEST_SET]))
		error = g.sess.run(g.cost, {
				g.y_input: Y[-TEST_SET:],
				g._layers[0].get_output(): X[-TEST_SET:]})


		n_loss = n.train(
				np.asarray(X[:-TEST_SET]),
				np.asarray(Y[:-TEST_SET]))
		n_error = n.sess.run(n.cost, {
				n.y_input: Y[-TEST_SET:],
				n._layers[0].get_output(): X[-TEST_SET:]})

		data = g.forward([X[137]])
		print("[Epoch ", i, "] [G] Loss: ", loss, " Error: ", error, "\t |\t [N] Loss: ", n_loss, " Error: ", n_error,)
		#print(g._layers[1].get_output().eval({g._layers[0].get_output(): [X[0]]}))
		#print(g._layers[2].get_output().eval({g._layers[0].get_output(): [X[0]]}))
		#print(g._layers[3].get_output().eval({g._layers[0].get_output(): [X[0]]}))




	

if __name__ == "__main__":
	main()