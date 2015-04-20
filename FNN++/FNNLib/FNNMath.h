///=================================================================================================
// file:	FNNMath.h
//
// summary:	Declares the fnn mathematics class
///-------------------------------------------------------------------------------------------------

#pragma once //DONT LOOK AT ME 2 MANY TIMES ;)

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
#include <random>
#include <time.h>
#include <vector>

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

        ///=================================================================================================
        /// <summary>   Uniform real. </summary>
        ///
        /// <remarks>   William Guss, 4/11/2015. </remarks>
        ///
        /// <param name="min">  The minimum. </param>
        /// <param name="max">  The maximum. </param>
        ///
        /// <returns>   A double. </returns>
        ///-------------------------------------------------------------------------------------------------

        static double UniformReal(double min = 0.0, double max = 0.0);

        ///=================================================================================================
        /// <summary>   Gaussian real. </summary>
        ///
        /// <remarks>   William Guss, 4/11/2015. </remarks>
        ///
        /// <param name="mean"> The mean. </param>
        ///
        /// <returns>   A double. </returns>
        ///-------------------------------------------------------------------------------------------------

        static double GaussianReal(double mean = 0.0, double dev = 1.0);
		
		///=================================================================================================
		/// <summary>   A polynomial multiplication helper </summary>
		///
		/// <remarks>   Phillip Kuznetsov, 4/19/2015. </remarks>
		///
		/// <param name="poly1">A vector of the coefficients. Each index is the power which x is raised to</param>
		///
		/// <param name="poly2">A vector of the second polynomial coefficients./param>
		/// 
		/// <returns>   A vector of coefficients for hte polynomial </returns>
		///-------------------------------------------------------------------------------------------------
		
		static std::vector<double> PolyMult(std::vector<double> poly1, std::vector<double> poly2);
		///=================================================================================================
		/// <summary>   A linear interpolation algorithm </summary>
		///
		/// <remarks>   Phillip Kuznetsov, 4/18/2015. </remarks>
		///
		/// <param name="data"> 2D vector of input data points </param>
		///
		/// <returns>   A linear interpolation function </returns>
		///-------------------------------------------------------------------------------------------------

		static std::function<double(double)> LERP(std::vector<std::vector<double>> data);

		///=================================================================================================
		/// <summary>   A polynomial interpolation algorithm according to http://en.wikipedia.org/wiki/Polynomial_interpolation </summary>
		///
		/// <remarks>   Phillip Kuznetsov, 4/19/2015. </remarks>
		///
		/// <param name="data"> 2D vector of input data points. Each row is a point. </param>
		///
		/// <returns>   A polynomial interpolation function </returns>
		///-------------------------------------------------------------------------------------------------

		static std::function<double(double)> PERP(std::vector<std::vector<double>> data);
    private:

    };
}