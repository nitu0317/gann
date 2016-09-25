"""
A standard neural network implemented using the GANN framework.
"""
import tensorflow as tf
import numpy as np

from gann import GANN
from layers.n_discrete import NDiscrete

def main():
	"""
	A normal neural network learning XOR.
	"""
	tf.set_random_seed(1)

	g = GANN([2])
	g.add_layer(NDiscrete(3, activation=tf.nn.relu))
	g.add_layer(NDiscrete(1, activation=tf.nn.sigmoid))
	g.make_training_method(learning_rate=1e-2)

	g.finalize()

	# Test the forward function
	print(g.forward(np.array([[1,1]])))

	# Test the training function
	for i in range(1000):
		loss = g.train(
			np.array([
				[1,1],
				[0,0],
				[0,1],
				[1,0]]),
			np.array([
				[0],
				[0],
				[1],
				[1]]))
		print("[Epoch ", i, "] Loss: ", loss)


	# Test the forward function after training
	print("Testing net: Output should be: 0,1,1,0.")
	print(g.forward(np.array([[1,1]])))
	print(g.forward(np.array([[0,1]])))
	print(g.forward(np.array([[1,0]])))
	print(g.forward(np.array([[0,0]])))
	

if __name__ == "__main__":
	main()