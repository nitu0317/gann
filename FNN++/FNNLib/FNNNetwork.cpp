///=================================================================================================
// file:	FNNNetwork.cpp
//
// summary:	Implements the fnn network class.
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNNetwork.h"
#include <math.h>

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
    std::vector<double> I1(this->weights[0].GetSizeX()); 
    for (int i = 0; i < I1.size(); i++)
        I1[i] = Math::NIntegrate([=](double j0){ return ξ(j0)*pow(j0, i); },
            0, 1);
    


    
    return[](double d){ return 0; };
}

///=================================================================================================
/// <summary>   Sets an activation. </summary>
///
/// <remarks>   William Guss, 4/11/2015. </remarks>
///
/// <param name="activator">    The activator. </param>
///-------------------------------------------------------------------------------------------------

void fnn::Network::SetActivation(Sigmoid activator)
{
    this->activator = activator;
}

