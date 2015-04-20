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
    this->layerCount = 0; // The first layer is always the inp;ut layer
    this->Activator = Sigmoid::Logistic();
    this->σ_cache = std::vector<std::function<double(double)>> (1); //We add one sigmoid term for the output
    this->weights = std::vector<WeightSurface>();
}




///=================================================================================================
/// <summary>   Runs the network using the fast feedforward algorithm. The algorithm caches
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
    std::vector<std::vector<double>> I_cache;

    for (int l = 0; l < this->layerCount; l++){

        // 1. Calculate the main integration of the net input, I
        //    I = Int[σ[l-1]j^{x_2l}]
        std::vector<double> I(this->weights[l].GetSizeX());

        for (int i = 0; i < I.size(); i++)
            I[i] = Math::NIntegrate([=](double j0){ return σ_cache[l](j0)*pow(j0, i); },
            0, 1);

        //    Push the calculated net to the integration cache.        
        I_cache.push_back(I);



        // 2. Calculate the coefficients for the polynomial representing σ[l+1]
        //    We do this by combining like terms from both the coefficients and
        //    the integration cache.
        //     
        //    Consider that σ[l+1] = g(
        std::vector<double> σcoeff;
        for (int j = 0; j < weights[l].GetSizeY(); j++){
            double sum = 0;
            for (int i = 0; i < weights[l].GetSizeX(); i++)
                sum += weights[l].GetCoefficient(i, j)*I[i];
            σcoeff.push_back(sum);

        }

        //Create the functional.
        σ_cache[l+1] = [=](double x)
        {
            double sum = 0;
            for (int j = 0; j < weights[l].GetSizeY(); j++)
                sum += σcoeff[j] * std::pow(x, j);

            return Activator(sum);
        };
    }
    
    


    
    return σ_cache[this->layerCount];
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

