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
    this->layerCount = 0; // The first layer is always the input layer
    this->Activator = Sigmoid::Logistic();
    this->weights = std::vector<WeightSurface>();

    //Caching variables.
    this->σ_cache = std::vector<std::function<double(double)>>(1); //We add one sigmoid term for the output
    this->I_cache = std::vector <std::vector<double>>(1);
    this->Ψ_cache = std::vector<std::function<double(double)>>(1); //We add one sigmoid term for the output layer.
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

    for (int l = 0; l < this->layerCount; l++){
        // 1. Calculate the main integration of the net input, I
        //    I = Int[σ[l-1]j^{x_2l}]
        std::vector<double> I(this->weights[l].GetSizeX());

        for (int i = 0; i < this->weights[l].GetSizeX(); i++){
            std::function<double(double)> input = [this, l, i](double j0){ return this->σ_cache[l](j0)*pow(j0, i); };
            I[i] = Math::NIntegrate(input, 0, 1);
        }
        //    Push the calculated net to the integration cache for use with error backpropagation.
        this->I_cache[l] = I; //TODO: Consider making the integration cache point by reference.

        // 2. Calculate the coefficients for the polynomial representing σ[l+1]
        //    We do this by combining like terms from both the coefficients and
        //    the integration cache.
        //
        //    Consider that σ[l+1] = g
        std::vector<double> polyCoeff;
        for (int j = 0; j < weights[l].GetSizeY(); j++){
            double sum = 0;
            for (int i = 0; i < weights[l].GetSizeX(); i++)
                sum += weights[l].GetCoefficient(i, j)*I[i]; //multiply by a member of the integration cache.
            polyCoeff.push_back(sum);
        }

        //Create the functional.
        σ_cache[l + 1] = [this, polyCoeff, l](double x) //const σcoeff
        {
            double sum = 0;
            for (int j = 0; j < this->weights[l].GetSizeY(); j++)
                sum += polyCoeff[j] * std::pow(x, j);

            return this->Activator(sum);
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
    this->I_cache.push_back(std::vector<double>(x));
    this->Ψ_cache.push_back([](double x){return x; });
    this->σ_cache.push_back([](double x){return x; });
}

///=================================================================================================
/// <summary>   Back propagate using the Super Pro Algo developed by William Guss and Patrick
///             Chen. </summary>
///
/// <remarks>   William Guss, 5/6/2015. </remarks>
///
/// <param name="δ">    The desired function delta δ. </param>
///
/// <returns>   The total integrated error over the last interval. </returns>
///-------------------------------------------------------------------------------------------------

double fnn::Network::BackPropagate(std::function<double(double)> δ)
{
    // 1. Calculate and cache all ψ^(n) for 1 \leq n \leq L
    //    We iterate over all the layers and define Ψ^(l+1).
    this->BuildΨ_cache();

    // 2. Calculate dE/dk[0]
        // a. Calculate and cache the first lambda cache.

    return(0.0);
}

///=================================================================================================
/// <summary>   Calculates the ψ cache. </summary>
///
/// <remarks>   William Guss, 5/6/2015. </remarks>
///-------------------------------------------------------------------------------------------------

void fnn::Network::BuildΨ_cache(void)
{
    //    We iterate over all the layers and define Ψ^(l+1).
    for (int l = 0; l < this->layerCount; l++){
        // By the definition presented in the paper we have that
        // Ψ[l+1] is defined in terms of each previous layer. See Lemma 4.1.


        // Calculate the internal like terms of each j.
        // We use pcoeff[x_2l]
        std::vector<double> polyCoeff;
        for (int j = 0; j < this->weights[l].GetSizeY(); j++)
        {
            double sum = 0;
            for (int i = 0; i < weights[l].GetSizeX(); i++)
                sum += weights[l].GetCoefficient(i, j)*this->I_cache[l][i]; //multiply by a member of the integration cache.
            polyCoeff.push_back(sum);
        }

        int sizey = this->weights[l].GetSizeY();

        // Combine like terms and build the functional.
        Ψ_cache[l+1] = ([this, polyCoeff, sizey](double x)
        {
            double output = 0;
            for (int j = 0; j < sizey; j++)
                output += polyCoeff[j] * pow(x, j);

            return this->Activator.prime(output);

        });
    }
}

/// <summary>	Nudge weights. </summary>
///
/// <remarks>	Phillip Kuznetsov, 5/8/2015. </remarks>

void fnn::Network::NudgeWeights(void)
{
    
}

/// <summary>	Trains the network. </summary>
///
/// <remarks>	Phillip Kuznetsov, 5/8/2015. </remarks>
///
/// <param name="dp">				 	The current datapoint. </param>
/// <param name="learningParameters">	Options for controlling the learning. </param>
///
/// <returns>	A double. </returns>

double fnn::Network::Train(DataPoint&dp, std::vector<double> learningParameters)
{
    
    return(0.0);
}

