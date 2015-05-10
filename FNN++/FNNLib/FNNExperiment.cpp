#include "stdafx.h"
#include "FNNExperiment.h"
#include <future> 
#include <atomic>;



/// <summary>	Constructor. </summary>
///
/// <remarks>	Phillip Kuznetsov, 5/8/2015. </remarks>
///
/// <param name="trainingSet">	Set the training belongs to. </param>
/// <param name="testingSet"> 	Set the testing belongs to. </param>

fnn::Experiment::Experiment(DataSet&trainingSet, DataSet&testingSet)
	: _trainingSet(trainingSet), _testingSet(testingSet)
{

}

/// <summary>	Executes as thread operation. </summary>
///
/// <remarks>	Phillip Kuznetsov, 5/8/2015. </remarks>
///
/// <returns>	true if it succeeds, false if it fails. </returns>

bool fnn::Experiment::RunAsThread()
{
	if (&worker == NULL)
	{
		worker = thread([this](){this->toggleThread(); this->Run(); this->toggleThread; });
		worker.join();

	}
	else if (done)
		return false;
	else
		worker.join();
	return true;
}

/// <summary>	Toggles whether the thread is running or not. </summary>
///
/// <remarks>	Phillip Kuznetsov, 5/8/2015. </remarks>

void fnn::Experiment::toggleThread()
{
	if (done)
		done = false;
	else
		done = true;
}

