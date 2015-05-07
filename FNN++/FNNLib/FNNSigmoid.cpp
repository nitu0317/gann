///=================================================================================================
// file:	FNNSigmoid.cpp
//
// summary:	Implements the fnn sigmoid class
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNSigmoid.h"
#include <math.h>

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
    return Sigmoid(
        [](double x){ return 1 / (1 + std::exp(-x)); },
        [](double x){ return std::exp(x) / std::pow(1 + std::exp(x), 2); }
    );
}

///=================================================================================================
/// <summary>   Gets the hyperbolic tangent activation function. </summary>
///
/// <remarks>   William, 4/10/2015. </remaqrks>
///
/// <returns>   A Sigmoid. </returns>
///-------------------------------------------------------------------------------------------------

fnn::Sigmoid fnn::Sigmoid::Tanh(void)
{
    return Sigmoid(
        [](double x){ return std::tanh(x); },
        [](double x){return 1 - std::pow(std::tanh(x), 2);  }
    );
}

///=================================================================================================
/// <summary>   Default constructor. Do nothing.t </summary>
///
/// <remarks>   William Guss, 4/12/2015. </remarks>
///-------------------------------------------------------------------------------------------------

fnn::Sigmoid::Sigmoid(std::function<double(double)> g, std::function<double(double)> gprime)
{
    this->fprime = gprime;
    this->f = g;
}

///=================================================================================================
/// <summary>   Default constructor. Do nothing.t </summary>
///
/// <remarks>   William Guss, 4/12/2015. </remarks>
///-------------------------------------------------------------------------------------------------

fnn::Sigmoid::Sigmoid()
{
    this->fprime = [](double x){ return 1;  };
    this->f = [](double x){ return x;  };
}