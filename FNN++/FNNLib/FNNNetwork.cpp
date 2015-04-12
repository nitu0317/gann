///=================================================================================================
// file:	FNNNetwork.cpp
//
// summary:	Implements the fnn network class.
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNNetwork.h"
#include <math.h>


///=================================================================================================
/// <summary>   Constructs a functional neural network. </summary>
///
/// <remarks>   William, 4/10/2015. </remarks>
///
/// <param name="lc">   The layer count. </param>
///-------------------------------------------------------------------------------------------------

fnn::Network::Network()
{
    this->layerCount = 0;
    this->Activator = Sigmoid::Logistic();
    this->σ_cache = std::vector<std::function<double(double)>>();
    this->weights = std::vector<WeightSurface>();
}




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

    std::vector<double> σ1coeff;

    //combine like terms.
    for (int j = 0; j < weights[0].GetSizeY(); j++){
        double sum = 0;
        for (int i = 0; i < weights[0].GetSizeX(); i++)
            sum += weights[0].GetCoefficient(i, j)*I1[i];
        σ1coeff.push_back(sum);
        
    }

    //Create the functional.
    σ_cache[1] = [=](double x)
    {
        double sum = 0;
        for (int j = 0; j < weights[0].GetSizeY(); j++)
            sum += σ1coeff[j] * std::pow(x, j);

        return Activator(sum);
    };

    
    


    
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
    this->Activator = activator;
}

///=================================================================================================
/// <summary>   Adds a layer to 'y'. </summary>
///
/// <remarks>   William Guss, 4/12/2015. </remarks>
///
/// <param name="x">    The x coordinate. </param>
/// <param name="y">    The y coordinate. </param>
///-------------------------------------------------------------------------------------------------

void fnn::Network::AddLayer(int x, int y)
{
    this->layerCount++;
    this->weights.push_back(WeightSurface(x, y));
    this->σ_cache.push_back([](double x){return x; });
}

