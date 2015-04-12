///=================================================================================================
// file:	FNNNetwork.cpp
//
// summary:	Implements the fnn network class.
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNNetwork.h"

///=================================================================================================
/// <summary>   Runs the network suing the fast feedforward algorithm. The algorithm caches
///             following that described in the paper. </summary>
///
/// <remarks>   William, 4/10/2015. </remarks>
///
/// <param name="ξ">    The input, ξ. </param>
///
/// <returns>   The ouput, F[ξ]. </returns>
///-------------------------------------------------------------------------------------------------

std::function<double(double)> fnn::Network::FeedForward(std::function<double(double)> ξ)
{
    //build the layers
    σ_cache[0] = ξ;
    
    //Calc Ix_1



	
    return[](double d){return 0; };
}

