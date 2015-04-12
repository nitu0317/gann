///=================================================================================================
// file:	WeightSurface.cpp
//
// summary:	Implements the weight surface class
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNWeightSurface.h"


#include <random>



///=================================================================================================
/// <summary>   Default constructor. </summary>
///
/// <remarks>   William Guss, 4/11/2015. </remarks>
///
/// <param name="x">    The x depth. </param>
/// <param name="y">    The y depth. </param>
///-------------------------------------------------------------------------------------------------

fnn::WeightSurface::WeightSurface(int x, int y)
{
    sizex = x;
    sizey = y;

    coef = std::vector<std::vector<double>>(x);
    for (int i = 0; i < x; i++)
        coef[i] = std::vector<double>(y);

    //randomize each coefficient./
    std::default_random_engine
}
