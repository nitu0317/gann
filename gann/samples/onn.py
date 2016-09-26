"""
A ONN implemented using the GANN framework.
"""
import tensorflow as tf
import numpy as np

from gann import GANN
from layers.o_operational import OOperational
from layers.input import ContinuousInput

from common.utils import sample_function

import matplotlib.pyplot as plt
plt.ion()

tf.set_random_seed(4)

def main():
	"""
	A normal neural network learning XOR.
	"""

	g = GANN(ContinuousInput((-1,1),100))
	g.add_layer(OOperational((-1,1), 100, [20,20],	 activation=tf.nn.relu))
	g.add_layer(OOperational((-1,1), 100, [20,20],	 activation=tf.nn.relu))
	g.make_training_method(learning_rate=1)

	g.finalize()

	# Test the forward function
	for i in range(1,20):
		data = (g.forward(sample_function(lambda x: np.real((x - i/100.0)**(i/100+2.0)) + i/1000, (-1,1), 100)))
		print("Pass: ", i)
		plt.plot(data[0])
		plt.pause(0.01)
	plt.clf()

	X = []
	Y = []
	NUM_DP = 15
	for o in range(NUM_DP):
		X.append(sample_function(lambda x: np.sin((x - o/6)*5)+1, (-1,1), 100).flatten())
		Y.append(sample_function(lambda x: np.sin((x + o/6  -1)*5)+1, (-1,1), 100).flatten())

	# Test the training function
	for i in range(1000):

		loss = g.train(
			np.asarray(X),
			np.asarray(Y))

		print("[Epoch ", i, "] Loss: ", loss)
		plt.clf()
		data = g.forward([X[0]])
		plt.plot(X[0], color='r')
		plt.plot(data[0], color='g')
		plt.plot(Y[0], color ='b')
		plt.pause(0.01)



	

if __name__ == "__main__":
	main()