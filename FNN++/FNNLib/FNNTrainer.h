///=================================================================================================
// file:	FNNTrainer.h
//
// summary:	Declares the fnn trainer class
///-------------------------------------------------------------------------------------------------
#pragma once //DONT LOOK AT ME 2 MANY TIMES ;)

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
#include <random>
#include <time.h>
#include <vector>
#include "FNNMath.h"
#include "FNNNetwork.h"
#include "FNNDataSet.h"

namespace fnn
{
	///=================================================================================================
	/// <summary>	The Trainer for the Network </summary>
	///
	/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>
	///-------------------------------------------------------------------------------------------------

	class FNNLIB Trainer : public Loggable
	{
	public:

		/// <summary>	FNNTrainer that takes a 2D vector for the trainingSet and testingSet. </summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>
		///
		/// <param name="network">	  	The Network being operated on. </param>
		/// <param name="trainingSet">	The training dataset. </param>
		/// <param name="testingSet"> 	The traiing dataset. </param>
		///

		Trainer(Network& network, fnn::DataSet& trainingSet, fnn::DataSet& testingSet);

		///=================================================================================================
		/// <summary>	Trains the network according to the parameters </summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>
		///
		/// <param name="epochs">			 	The epochs. </param>
		/// <param name="minError">			 	The minimum error. </param>
		/// <param name="learningParameters">	Options for controlling the learning. </param>
		/// <param name="nudging">			 	Whether the trainer uses nudging  </param>
		///
		/// <returns>	An int. </returns>
		///-------------------------------------------------------------------------------------------------

		int Train(int epochs, double minError, bool nudging = false);

	private:
		DataSet& _testingSet;
		DataSet& _trainingSet;
		/// <summary>	The currrent network </summary>
		Network* _network;
		/// <summary>	The error history. </summary>
		std::vector<double> errorHistory;
	};
}
