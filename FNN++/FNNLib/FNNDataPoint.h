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
namespace fnn
{
	class DataPoint
	{
    public:

        ///=================================================================================================
        /// <summary>   Constructs the data point with given parameters. </summary>
        ///
        /// <remarks>   William, 5/10/2015. </remarks>
        ///
        /// <param name="input">    The input. </param>
        /// <param name="desired">  The desired. </param>
        ///-------------------------------------------------------------------------------------------------

        DataPoint(std::function<double(double)> input, std::function<double(double)> desired);

        ///=================================================================================================
        /// <summary>   Evaluates the input at a given x. </summary>
        ///
        /// <remarks>   William, 5/10/2015. </remarks>
        ///
        /// <param name="x">    The x coordinate. </param>
        ///
        /// <returns>   A double. </returns>
        ///-------------------------------------------------------------------------------------------------

        double FNNLIB Input(double x);

        ///=================================================================================================
        /// <summary>   Evaluates the desuired at a given point. </summary>
        ///
        /// <remarks>   William, 5/10/2015. </remarks>
        ///
        /// <param name="x">    The x coordinate. </param>
        ///
        /// <returns>   A double. </returns>
        ///-------------------------------------------------------------------------------------------------

        double FNNLIB Desired(double x);

        ///=================================================================================================
        /// <summary>   Gets the input. </summary>
        ///
        /// <remarks>   William, 5/10/2015. </remarks>
        ///
        /// <returns>   The input. </returns>
        ///-------------------------------------------------------------------------------------------------

        std::function<double(double)> GetInput();

        ///=================================================================================================
        /// <summary>   Gets the desired. </summary>
        ///
        /// <remarks>   William, 5/10/2015. </remarks>
        ///
        /// <returns>   The desired. </returns>
        ///-------------------------------------------------------------------------------------------------

        std::function<double(double)> GetDesired();



    private:
		std::function<double(double)> input;
		std::function<double(double)> desired;
	};
}

