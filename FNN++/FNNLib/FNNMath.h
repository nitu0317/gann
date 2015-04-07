///=================================================================================================
// file:	FNNMath.h
//
// summary:	Declares the fnn mathematics class
///-------------------------------------------------------------------------------------------------

#pragma once //DONT LOOK AT ME 2 MANY TIMES ;)

#ifdef FNNLIB_EXPORTS
#define FNNLIB  __declspec(dllexport)   // export DLL information
#else
#define FNNLIB  __declspec(dllimport)   // import DLL information
#endif 

#include <functional>


namespace fnn
{
    ///=================================================================================================
    /// <summary>  The main mathematics helper class for FNNLIB </summary>
    ///
    /// <remarks>   William Guss, 4/6/2015. </remarks>
    ///-------------------------------------------------------------------------------------------------
    class FNNLIB Math
    {

    public:
        ///=================================================================================================
        /// <summary>   Numerically integrates any integrable function on a compact Hausdorff space.
        ///             Integration occurs using Simpson's rule. </summary>
        ///
        /// <remarks>   William Guss, 4/6/2015. </remarks>
        ///
        /// <param name="f">    The function to integrate. </param>
        /// <param name="a">    The lower bound of integration. </param>
        /// <param name="b">    The upper bound of integration. </param>
        /// <param name="eps">  The step-size of integration using Simpson's rule.</param>
        ///
        /// <returns>   The result. </returns>
        ///-------------------------------------------------------------------------------------------------

        static double NIntegrate(std::function<double(double)> f, double a, double b, double eps);

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

        static double NIntegrate(std::function<double(double)> f, double a, double b);
    };

    ///=================================================================================================
    /// <summary>   Different sigmoid activation functions. </summary>
    ///
    /// <remarks>   William Guss, 4/6/2015. </remarks>
    ///-------------------------------------------------------------------------------------------------

    enum Sigmoid
    {
        /// <summary>   The linear sigmoid activation function.</summary> 
        Linear,
        /// <summary>   The logistic activation function. </summary> 
        Logistic,
        /// <summary>   The hyperbolic tangent activation function. </summary>
        Tanh
    };

}