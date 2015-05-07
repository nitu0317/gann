///=================================================================================================
// file:	WeightSurface.h
//
// summary:	Declares the weight surface class
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

#include <vector>

namespace fnn{
    class WeightSurface
    {
    public:

        ///=================================================================================================
        /// <summary>   Default constructor. </summary>
        ///
        /// <remarks>   William Guss, 4/11/2015. </remarks>
        ///-------------------------------------------------------------------------------------------------

        WeightSurface(int x, int y);

        ///=================================================================================================
        /// <summary>   Function call operator. </summary>
        ///
        /// <remarks>   William Guss, 4/11/2015. </remarks>
        ///
        /// <param name="i">    Zero-based index of the . </param>
        /// <param name="j">    The double to process. </param>
        ///
        /// <returns>   The result of the operation. </returns>
        ///-------------------------------------------------------------------------------------------------

        double operator()(double i, double j);

        ///=================================================================================================
        /// <summary>   Gets a coefficient. </summary>
        ///
        /// <remarks>   William Guss, 4/11/2015. </remarks>
        ///
        /// <param name="x">    The x coordinate. </param>
        /// <param name="y">    The y coordinate. </param>
        ///
        /// <returns>   The coefficient. </returns>
        ///-------------------------------------------------------------------------------------------------

        double GetCoefficient(int x, int y);

        ///=================================================================================================
        /// <summary>   Nudges the weight surface coefficients. </summary>
        ///
        /// <remarks>   William Guss, 4/11/2015. </remarks>
        ///-------------------------------------------------------------------------------------------------

        void Nudge();

        ///=================================================================================================
        /// <summary>   Gets size x coordinate. </summary>
        ///
        /// <remarks>   William Guss, 4/11/2015. </remarks>
        ///
        /// <returns>   The size x coordinate. </returns>
        ///-------------------------------------------------------------------------------------------------

        int GetSizeX();

        ///=================================================================================================
        /// <summary>   Gets size y coordinate. </summary>
        ///
        /// <remarks>   William Guss, 4/11/2015. </remarks>
        ///
        /// <returns>   The size y coordinate. </returns>
        ///-------------------------------------------------------------------------------------------------

        int GetSizeY();

    private:
        /// <summary>   The coefficient matrix. </summary>
        std::vector<std::vector<double>> coef;

        /// <summary>   The sizex. </summary>
        int sizex;

        /// <summary>   The sizey. </summary>
        int sizey;
    };
}