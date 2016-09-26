"""
A ONN implemented using the GANN framework.
"""
import tensorflow as tf
import numpy as np

from gann import GANN
from layers.o_operational import OOperational
from layers.input import ContinuousInput
from layers.input import DiscreteInput
from layers.n_discrete import NDiscrete
from common.utils import sample_function, get_derivative

import matplotlib.pyplot as plt
plt.ion()


def derivative_loss(desired, out):
	int_cost = tf.reduce_mean(tf.square(desired - out)) 
	desired_prime = get_derivative(desired, (-1,1), 100)
	out_prime = get_derivative(out, (-1,1), 100)
	der_cost = tf.reduce_mean(tf.square(desired_prime - out_prime)) 
	return int_cost + 0.001*der_cost

def main():
	"""
	An operational neural network learning to sqrt and move a sin function.
	"""

	tf.set_random_seed(4)
	with tf.variable_scope("onn"):
			g = GANN(ContinuousInput((-1,1),100))
			g.add_layer(OOperational((-1,1), 100, [20,20],   activation=tf.nn.relu))
			g.add_layer(OOperational((-1,1), 100, [20,30],   activation=tf.nn.relu))
			g.make_training_method(learning_rate=1)
			g.finalize()

	tf.set_random_seed(4)
	with tf.variable_scope("normal_net"):
			n = GANN(DiscreteInput([100]))
			n.add_layer(NDiscrete(20, activation=tf.nn.relu))
			n.add_layer(NDiscrete(10, activation=tf.nn.relu))
			n.add_layer(NDiscrete(100, activation=tf.nn.relu))
			n.make_training_method(learning_rate=1e-3)
			n.finalize()

	# Test the forward function
	for i in range(1,20):
		data = (g.forward(sample_function(lambda x: np.real((x - i/100.0)**(i/100+2.0)) + i/1000, (-1,1), 100)))
		print("Pass: ", i)
		plt.plot(data[0])
		plt.pause(0.01)
	plt.clf()

	X = []
	Y = []
	NUM_DP = 150
	for o in range(NUM_DP):
		X.append(sample_function(lambda x: np.sin((x - o/50.0)*5)+1, (-1,1), 100).flatten())
		Y.append(sample_function(lambda x: np.sqrt(np.sin((x + o/50.0  -1)*5)+1), (-1,1), 100).flatten())

	# Test the training function
	for i in range(10000):

		loss = g.train(
			np.asarray(X[:-70]),
			np.asarray(Y[:-70]))
		error = g.sess.run(g.cost, {
			g.y_input: Y[-70:],
			g._layers[0].get_output(): X[-70:]})

		n_loss = n.train(
			np.asarray(X[:-70]),
			np.asarray(Y[:-70]))
		n_error = n.sess.run(n.cost, {
			n.y_input: Y[-70:],
			n._layers[0].get_output(): X[-70:]})

		print("[Epoch ", i, "] G: Loss: ", loss, " Error: ", error, "\t\t N:  Loss: ", n_loss, "Error:", n_error)

		plt.clf()#
		data = g.forward([X[0]])
		data2 = n.forward([X[0]])
		plt.plot(X[0], color='r')
		plt.plot(data[0], color='g')
		plt.plot(Y[0], color ='b')
		plt.plot(data2[0], color ='b')
		plt.pause(0.05)


	

if __name__ == "__main__":
	main()
