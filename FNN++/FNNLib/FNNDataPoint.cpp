
#include "stdafx.h"

#include <functional>
#include "FNNDataPoint.h"

///=================================================================================================
/// <summary>   Constructs the data point with given parameters. </summary>
///
/// <remarks>   William, 5/10/2015. </remarks>
///
/// <param name="input">    The input. </param>
/// <param name="desired">  The desired. </param>
///-------------------------------------------------------------------------------------------------


fnn::DataPoint::DataPoint(std::function<double(double)> input, std::function<double(double)> desired)
{
    this->input = input;
    this->desired = desired;
}

///=================================================================================================
/// <summary>   Evaluates the input at a given x. </summary>
///
/// <remarks>   William, 5/10/2015. </remarks>
///
/// <param name="x">    The x coordinate. </param>
///
/// <returns>   A double. </returns>
///-------------------------------------------------------------------------------------------------

double FNNLIB fnn::DataPoint::Input(double x)
{
    return input(x);
}

///=================================================================================================
/// <summary>   Evaluates the desuired at a given point. </summary>
///
/// <remarks>   William, 5/10/2015. </remarks>
///
/// <param name="x">    The x coordinate. </param>
///
/// <returns>   A double. </returns>
///-------------------------------------------------------------------------------------------------

double FNNLIB fnn::DataPoint::Desired(double x)
{
    return desired(x);
}

///=================================================================================================
/// <summary>   Gets the input. </summary>
///
/// <remarks>   William, 5/10/2015. </remarks>
///
/// <returns>   The input. </returns>
///-------------------------------------------------------------------------------------------------

std::function<double(double)> fnn::DataPoint::GetInput(void)
{
    return input;
}

///=================================================================================================
/// <summary>   Gets the desired. </summary>
///
/// <remarks>   William, 5/10/2015. </remarks>
///
/// <returns>   The desired. </returns>
///-------------------------------------------------------------------------------------------------

std::function<double(double)> fnn::DataPoint::GetDesired(void)
{
    return desired;
}

