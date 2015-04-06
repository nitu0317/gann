Design Log
===

## 4/5/2015
Seeing as the theoretical algorithm for the most part is completed,  we currently have two goals:

* Construct a fast FNN algorithm and write about it in our white paper,
* Design the library.

I believe that the latter can be accomplised without the former, again for the most part. So, I will try and outline the goals of the library and work on design hereafter.

### Designing the Library
To design the library simple goals should be presented with example syntax for each provided.


1. We wish to implement the fast functional neural network algorithm in C++.
 It would be adventageous if, for example I could initialize a FNN with any given non-zero positive number of layers.
 ```
 int numLayer = 3;
 FNetwork net = FNetwork(numLayer);
 ```
 Additionally changing the sigmoid would allow for optimization. For example   
 `net.activation = Sigmoid.Regression` or `net.activation = Sigmoid.Linear`. 

 The network should then be able to feed-forward on any function resulting in some output function.
 ```
 Func f(x) = x^2;
 Func output(x);

 output(x) = net.run(f(x));
 ```
 Again this would require us to have a well established mathematical/C++ function meta-framework. 

2. We wish to accomplish this using parallelism and any linear algebra API we can.

 We would probably use OpenMP for summation which we will discuss in the derivation of a fast algorithm for functional neural networks. This can't be truly developed untill we have a closed form defenition for fast functional neural networks.

3. We want the library to provide a simple method to interpret data as functions, through either linear approximation or some other method. Hence it seems important that a third party math library be chosen.
 
 Upon further research I can't find a function library for math. What does this mean? We could handle functions as function pointers and use that in that way. 

 Here is an example:
 ```
 #include<functional>
 
 static double derivative(const std::function<double(double)> &f, double x0, double eps)
 {
    double eps2 = eps/2;
    double lo = x0 - eps;
    double hi = x0 + eps;
    return(f(hi) - f(lo))/eps;
 }

 static double f(double x) { return x*x; }

 int main()
 {
    double x =1;
    std::cout << derivative(f,x,1e-5);
    return 0;
 }
 ```
 In that example it's easy to see how one could easily manipulate functions and then implement a numerical integration algorithm. However, more difficulty may come from the desired functionality of the library.

 We desired `std::function<double(double)> output = net.run(f)`, which is not possible given the definition of the C++ functional. Since C++11, however, lambda expressions were added. Check out this sick example:
 ```
 #include <algorithm>
 #include <cmath>
 void abssort(float* x, unsigned n) {
     std::sort(x, x + n,
         // Lambda expression begins
         [](float a, float b) {
             return (std::abs(a) < std::abs(b));
         } // end of lambda expression
     );
 }
 ```

 As you can see, C++ has come a long way, this will be extremely useful in implementing our functional neural network syntax. We can do simple computations on any given lambda expression like `net.run([](double x){return x*x;});`. FNNLib will be much more versitile using this input construction.

 Now we must solve the issue of output. Got it---

 As per the [MSDN tutorial](https://msdn.microsoft.com/en-us/library/dd293599.aspx), we have that functions correspond directly with lambda types. For example
 ```
 function<int(int,int)> f1 = [](int x, int y){ return x+y; };
 ```
 [Storing the function incurs the overhead of abstraction from function however](http://stackoverflow.com/questions/3218821/c0x-lambda-overhead).

4. We want to implement some form of fast error backpropagation.

