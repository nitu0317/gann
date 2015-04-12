///=================================================================================================
// file:	FNNSigmoid.h
//
// summary:	Declares the fnn sigmoid class.
///-------------------------------------------------------------------------------------------------

#pragma once

#ifdef FNNDLL
#ifdef FNNLIB_EXPORTS
#define FNNLIB  __declspec(dllexport)   // export DLL information
#else
#define FNNLIB  __declspec(dllimport)   // import DLL information
#endif
#else
#define FNNLIB
#endif

#include <functional>
#include <iostream>


///=================================================================================================
/// <summary>   Different sigmoid activation functions. </summary>
///
/// <remarks>   William Guss, 4/6/2015. </remarks>
///-------------------------------------------------------------------------------------------------


namespace fnn{
    class FNNLIB Sigmoid
    {
    public:

        ///=================================================================================================
        /// <summary>   Constructs a sigmoid function </summary>
        ///
        /// <remarks>   William, 4/10/2015. </remarks>
        ///
        /// <param name="f">        The std::function&lt;double(double)&gt; to process. </param>
        /// <param name="fprime">   The fprime. </param>
        ///-------------------------------------------------------------------------------------------------

        Sigmoid(std::function<double(double)> f,
            std::function<double(double)> fprime);

        ///=================================================================================================
        /// <summary>   Default constructor. </summary>
        ///
        /// <remarks>   William Guss, 4/12/2015. </remarks>
        ///-------------------------------------------------------------------------------------------------

        Sigmoid();

        ///=================================================================================================
        /// <summary>   Evaluates the derivative of the activation function. </summary>
        ///
        /// <remarks>   William, 4/10/2015. </remarks>
        ///
        /// <param name="x">    The x coordinate. </param>
        ///
        /// <returns>   A double. </returns>
        ///-------------------------------------------------------------------------------------------------

        double prime(double x);

        ///=================================================================================================
        /// <summary>   Evaluates the sigmoid. </summary>
        ///
        /// <remarks>   William, 4/10/2015. </remarks>
        ///
        /// <param name="x">    The x coordinate. </param>
        ///
        /// <returns>   The result of the operation. </returns>
        ///-------------------------------------------------------------------------------------------------

        double operator()(double x);


        ///=================================================================================================
        /// <summary>   Gets the linear sigmoid activation. </summary>
        ///
        /// <remarks>   William, 4/10/2015. </remarks>
        ///
        /// <returns>   A Sigmoid. </returns>
        ///-------------------------------------------------------------------------------------------------

        static Sigmoid Linear();

        ///=================================================================================================
        /// <summary>   The logistic activation function. </summary>
        ///
        /// <remarks>   William, 4/10/2015. </remarks>
        ///
        /// <returns>   A Sigmoid. </returns>
        ///-------------------------------------------------------------------------------------------------

        static Sigmoid Logistic();

        ///=================================================================================================
        /// <summary>   Gets the hyperbolic tangent activation function. </summary>
        ///
        /// <remarks>   William, 4/10/2015. </remarks>
        ///
        /// <returns>   A Sigmoid. </returns>
        ///-------------------------------------------------------------------------------------------------

        static Sigmoid Tanh();

    private:

        /// <summary>   The activation function. </summary>
        std::function<double(double)> f;


        /// <summary>   The derivative of the activation function.</summary>
        std::function<double(double)> fprime;
    };
}