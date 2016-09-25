"""
A standard neural network implemented using the GANN framework.
"""
from gann import GANN
from layers.n_discrete import NDiscrete

import numpy as np

def main():
	"""
	A normal neural network learning XOR.
	"""

	g = GANN([2])
	g.add_layer(NDiscrete(3))
	g.add_layer(NDiscrete(2))
	g.add_layer(NDiscrete(1))
	g.finalize()

	# Test the forward function
	print(g.forward(np.array([[1,1]])))
	

if __name__ == "__main__":
	main()