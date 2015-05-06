///=================================================================================================
// file:	FNNNetwork.h
//
// summary:	Declares the functional neural network's primary class of operation
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

#include <functional>
#include <vector>
#include "FNNMath.h"
#include "FNNSigmoid.h"
#include "FNNWeightSurface.h"
#include "FNNLoggable.h"

namespace fnn{

    ///=================================================================================================
    /// <summary>   The main class of operation on the functional neural networks. </summary>
    ///
    /// <remarks>   William, 4/9/2015. </remarks>
    ///-------------------------------------------------------------------------------------------------

    class FNNLIB Network : Loggable
    {
    public:

        ///=================================================================================================
        /// <summary>   Constructs a functional neural network.. </summary>
        ///
        /// <remarks>   William, 4/10/2015. </remarks>
        ///
        /// <param name="lc">   The layer count. </param>
        ///-------------------------------------------------------------------------------------------------

        Network();

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

        std::function<double(double)> FeedForward(std::function<double(double)> ξ);

        ///=================================================================================================
        /// <summary>   Back propagate using the Super Pro Algo developed by William Guss and Patrick Chen. </summary>
        ///
        /// <remarks>   Madcow D, 5/6/2015. </remarks>
        ///
        /// <param name="δ">    The desired function delta δ. </param>
        ///
        /// <returns>   The total integrated error over the last interval. </returns>
        ///-------------------------------------------------------------------------------------------------

        double BackPropagate(std::function<double(double)> δ);

        ///=================================================================================================
        /// <summary>   Sets an activation. </summary>
        ///
        /// <remarks>   William Guss, 4/11/2015. </remarks>
        ///
        /// <param name="activator">    The activator. </param>
        ///-------------------------------------------------------------------------------------------------

        void SetActivation(Sigmoid activator);

        ///=================================================================================================
        /// <summary>   Adds a layer to 'y'. </summary>
        ///
        /// <remarks>   William Guss, 4/12/2015. </remarks>
        ///
        /// <param name="x">    The x coordinate. </param>
        /// <param name="y">    The y coordinate. </param>
        ///-------------------------------------------------------------------------------------------------

        void AddLayer(int x, int y);

        /// <summary>   The primary activator type for the neural network. </summary>
        Sigmoid Activator;

    private:

        /// <summary>   The number of layers in the network. </summary>
        int layerCount;

        /// <summary>   The weights. </summary>
        std::vector<WeightSurface> weights; 


        ///======================
        ///  CACHING
        ///======================        

        /// <summary>   The integration cache for I = NInt(σ[l]j_l^(i). </summary>
        std::vector<std::vector<double>> I_cache;

        /// <summary>   The σ-cache for layers. </summary>
        std::vector<std::function<double(double)>> σ_cache;

        /// <summary>   The Ψ_cache for layers. </summary>
        std::vector<std::function<double(double)>> Ψ_cache;


    };


}