///=================================================================================================
// file:	FNNTrainer.cpp
//
// summary:	Implements the fnn trainer class
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNTrainer.h"
#include "FNNMath.h"

fnn::Trainer::Trainer(Network& network, fnn::DataSet& trainingSet, fnn::DataSet& testingSet) : _trainingSet(trainingSet), _testingSet(testingSet)
{	
	_network = &network;
	errorHistory = std::vector<double>(20);
}
int fnn::Trainer::Train(int epochs, double minError, bool nudging)
{
	
	errorHistory.clear();
	// current epoch and error
	int epoch = 0;
	double error = 0;
	do
	{
		epoch++;
		error = 0;
			for (int i = 0; i < _trainingSet.Size(); i++)
			{
				auto dp = _trainingSet[i];
				error+= (*_network).Train(dp);
			}
		this->errorHistory.push_back(error);
		
		//true if there has been a sugnificant change in the past two error histories.
		bool sigChange = true;
		//this figures out this situation
		int size = errorHistory.size();
		std::vector<double>::const_iterator first = errorHistory.end() - 10;
		std::vector<double>::const_iterator last = errorHistory.end();
		std::vector<double> stdVec(first, last);
		double stdDev = Math::StdDev(stdVec);
		//nudges if nudging is true and the error history standard deviation has been less than .0000075
		 
		if (nudging && stdDev < .0000075)
		{
			(*_network).NudgeWeights();
		}

	} while (epoch < epochs && error > minError);
	return epoch;
}
