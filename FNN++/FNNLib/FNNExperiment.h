// file:	FNNExperiment.h
//
// summary:	Declares the fnn experiment class

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
#include <string>
#include <thread>
#include <atomic>
#include "FNNMath.h"
#include "FNNNetwork.h"
#include "FNNDataSet.h"

using std::string;
using std::thread;

namespace fnn
{
	class FNNLIB Experiment
	{

	public:

		/// <summary>	Constructor. </summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/8/2015. </remarks>
		///
		/// <param name="trainingSet">	Set the training belongs to. </param>
		/// <param name="testingSet"> 	Set the testing belongs to. </param>

		Experiment(DataSet& trainingSet, DataSet& testingSet);

		/// <summary>	Runs this object. </summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/8/2015. </remarks>

		virtual void Run() = 0; //TODO: Implemnent

		/// <summary>	Executes as thread operation. </summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/8/2015. </remarks>
		///
		/// <returns>	true if it succeeds, false if it fails. </returns>

		bool RunAsThread(); //TODO: Implement

		/// <summary>	Toggles whether the thread is running or not</summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/8/2015. </remarks>

		void ToggleThread();
	private:
		string DATASTORE;
		string PERSIST;
		thread worker;
		/// <summary>	marks whether worker is done or not </summary>
		bool done = true;
		DataSet& _trainingSet;
		DataSet& _testingSet;
	};
}

