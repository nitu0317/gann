///=================================================================================================
// file:	FNNDataSet.cpp
//
// summary:	Implements the fnn data set class
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNDataSet.h"

/// <summary>	Constructor that initializes the class. </summary>
///
/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>

fnn::DataSet::DataSet(void)
{
	
}

/// <summary>	Array indexer operator. </summary>
///
/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>
///
/// <param name="index">	Zero-based index of the. </param>
///
/// <returns>	The indexed value from DataPoints. </returns>

fnn::DataPoint& fnn::DataSet::operator[](int index)
{
	return dataPoints[index];
}

/// <summary>	Gets the size. </summary>
///
/// <remarks>	Phillip Kuznetsov, 5/6/2015. </remarks>
///
/// <returns>	An int size of the DataSet. </returns>

int fnn::DataSet::size(void)
{
	return dataPoints.size();
}

