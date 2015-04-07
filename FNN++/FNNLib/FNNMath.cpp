///=================================================================================================
// file:	FNNMath.cpp
// 
// summary:	Implements the FNN mathematics class. 
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNMath.h"

///=================================================================================================
/// <summary>   Numerically integrates any integrable function using Simpson's rule with auto
///             scaling. </summary>
///
/// <remarks>   William Guss, 4/6/2015. </remarks>
///
/// <param name="f">    The function to integrate. </param>
/// <param name="a">    The lower bound of integration. </param>
/// <param name="b">    The upper bound of integration. </param>
///
/// <returns>   The result. </returns>
///-------------------------------------------------------------------------------------------------

double fnn::Math::NIntegrate(std::function<double(double)> f, double a, double b)
{
	
	return(0.0);
}

///=================================================================================================
/// <summary>   Numerically integrates any integrable function on a compact Hausdorff space.
///             Integration occurs using Simpson's rule. </summary>
///
/// <remarks>   William Guss, 4/6/2015. </remarks>
///
/// <param name="f">    The function to integrate. </param>
/// <param name="a">    The lower bound of integration. </param>
/// <param name="b">    The upper bound of integration. </param>
/// <param name="eps">  The step-size of integration using Simpson's rule. </param>
///
/// <returns>   The result. </returns>
///-------------------------------------------------------------------------------------------------

double fnn::Math::NIntegrate(std::function<double(double)> f, double a, double b, double eps)
{

    double h = (b - a) / eps;
    double s = f(a) + f(b);

    for (int i = 1; i < eps; i += 2)
        s += 4 * f(a + i*h);
    for (int i = 2; i < eps - 1; i += 2)
        s += 2 * f(a + i*h);
	
    
    return s*h /3;
}

