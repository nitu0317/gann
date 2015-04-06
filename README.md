FNN++
===

FNN++ is an implementation of the Functional Neural Network algorithm created by William Guss. 
FNN++ acts as a scientific computation suite accompanied by an API for managing all computations with functional neural networks.
This library was created by William Guss, Phillip Kuznetsov, and Patrick Chen, and is licensed under the MIT license. 
Feel free to fork the code here on GitHub or create pull requests for any features you might want added.


## Functional Neural Networks
Functional neural networks (FNNs) are an analytical abstraction of neural networks such as those proposed in McCulloch and Pitts to the continuous domain.
Essentialy with FNNs one can map through arbitrary operation, any family of functions to another family of functions. 
If one considers standard feed-forward artificial neural networks, they act as sigmoidal transformations; that is,

>N: R -> R.

whereas functional neural networks act on any banach space, such as the set of continous functions over compact Hausdorf spaces X; that is,

>F: C(A) -> C(B)

where F denotes the action of a functional neural network and A, B are closed intervals in R.

Interestingly enough it has been shown that functional neural networks are universal approximators of arbitrary operations, and furthermore that all feed-forward neural networks are a subset of the family of functional neural networks. 
If you would like to know more about FNNs, [read our white-paper](./documentation/FunctionalNN.pdf).