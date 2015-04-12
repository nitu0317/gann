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

namespace fnn{

    ///=================================================================================================
    /// <summary>   The main class of operation on the functional neural networks. </summary>
    ///
    /// <remarks>   William, 4/9/2015. </remarks>
    ///-------------------------------------------------------------------------------------------------

    class FNNLIB Network{
    public:

        ///=================================================================================================
        /// <summary>   Constructs a functional neural network.. </summary>
        ///
        /// <remarks>   William, 4/10/2015. </remarks>
        ///
        /// <param name="lc">   The layer count. </param>
        ///-------------------------------------------------------------------------------------------------

        Network(int lc);

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
        /// <summary>   Sets an activation. </summary>
        ///
        /// <remarks>   William Guss, 4/11/2015. </remarks>
        ///
        /// <param name="activator">    The activator. </param>
        ///-------------------------------------------------------------------------------------------------

        void SetActivation(Sigmoid activator);

    private:

        /// <summary>   The number of layers in the network. </summary>
        int layerCount;

        /// <summary>   The primary activator type for the neural network. </summary>
        Sigmoid activator;

        /// <summary>   The σ-cache for layers. </summary>
        std::vector<std::function<double(double)>> σ_cache;
        
        


    };


}