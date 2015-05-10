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
#include "FNNNetwork.h"
#include "FNNDataPoint.h"

namespace fnn
{
	class FNNLIB DataSet
	{
	public:

		///=================================================================================================
		/// <summary> Constructor that initializes the class</summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>
		///-------------------------------------------------------------------------------------------------
		DataSet();

		/// <summary>	Loads the DataSet </summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>

		virtual void Load() = 0;

		/// <summary>	Shuffles this DataSet </summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>

		void Shuffle();

		/// <summary>	Calculates the errors. </summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>
		///
		/// <param name="n">   	The Network to process. </param>
		/// <param name="step">	Amount to increment by. </param>
		///
		/// <returns>	The calculated errors. </returns>

		std::vector<double(double)> calculateErrors(Network &nn, double step = -1);

		/// <summary>	Calculates the error. </summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>
		///
		/// <param name="nn">  	The nn. </param>
		/// <param name="step">	Amount to increment by. </param>
		///
		/// <returns>	The calculated error. </returns>

		double calcError(Network &nn, double step = -1);

		/// <summary>	Gets the size. </summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>
		///
		/// <returns>	An int size of the DataSet </returns>

		int size();

		/// <summary>	Array indexer operator. </summary>
		///
		/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>
		///
		/// <param name="index">	Zero-based index of the. </param>
		///
		/// <returns>	The indexed value from DataPoints. </returns>

		DataPoint& DataSet::operator[](int index);

	private:
		std::vector<DataPoint> dataPoints;
		
	};
}

