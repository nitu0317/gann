///=================================================================================================
// file:	WeightSurface.cpp
//
// summary:	Implements the weight surface class
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNWeightSurface.h"
#include "FNNMath.h"

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

    Nudge();
    
}

///=================================================================================================
/// <summary>   Nudges the weight surface coefficients. </summary>
///
/// <remarks>   William Guss, 4/11/2015. </remarks>
///-------------------------------------------------------------------------------------------------

void fnn::WeightSurface::Nudge(void)
{
    for (int i = 0; i < sizex; i++)
        for (int j = 0; j < sizex; j++)
            coef[i][j] = Math::GaussianReal();
}

///=================================================================================================
/// <summary>   Gets size x coordinate. </summary>
///
/// <remarks>   William Guss, 4/11/2015. </remarks>
///
/// <returns>   The size x coordinate. </returns>
///-------------------------------------------------------------------------------------------------

int fnn::WeightSurface::GetSizeX(void)
{
    
    return sizex;
}

///=================================================================================================
/// <summary>   Gets size y coordinate. </summary>
///
/// <remarks>   William Guss, 4/11/2015. </remarks>
///
/// <returns>   The size y coordinate. </returns>
///-------------------------------------------------------------------------------------------------

int fnn::WeightSurface::GetSizeY(void)
{
    
    return sizey;
}

