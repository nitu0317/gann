///=================================================================================================
// file:	FNNSigmoid.cpp
//
// summary:	Implements the fnn sigmoid class
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNSigmoid.h"

///=================================================================================================
/// <summary>   Evaluates the derivative of the activation function. </summary>
///
/// <remarks>   William, 4/10/2015. </remarks>
///
/// <param name="x">    The x coordinate. </param>
///
/// <returns>   A double. </returns>
///-------------------------------------------------------------------------------------------------

double fnn::Sigmoid::prime(double x)
{
    return fprime(x);
}

///=================================================================================================
/// <summary>   Evaluates the sigmoid. </summary>
///
/// <remarks>   William, 4/10/2015. </remarks>
///
/// <param name="x">    The x coordinate. </param>
///
/// <returns>   The result of the operation. </returns>
///-------------------------------------------------------------------------------------------------

double fnn::Sigmoid::operator()(double x)
{
    return f(x);
}

///=================================================================================================
/// <summary>   Gets the linear sigmoid activation. </summary>
///
/// <remarks>   William, 4/10/2015. </remarks>
///
/// <returns>   A Sigmoid. </returns>
///-------------------------------------------------------------------------------------------------

fnn::Sigmoid fnn::Sigmoid::Linear(void)
{
    return Sigmoid(
        [](double x) { return x; },
        [](double x) { return 1; }
        );
}

///=================================================================================================
/// <summary>   The logistic activation function. </summary>
///
/// <remarks>   William, 4/10/2015. </remarks>
///
/// <returns>   A Sigmoid. </returns>
///-------------------------------------------------------------------------------------------------

fnn::Sigmoid fnn::Sigmoid::Logistic(void)
{
    return Sigmoid
}

