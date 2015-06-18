#include "stdafx.h"
#include "FNNLaplaceDataSet.h"
#include "FNNMath.h"

#include <functional>

LaplaceDataSet::LaplaceDataSet()
{
}


LaplaceDataSet::~LaplaceDataSet()
{
}

///=================================================================================================
/// <summary>   Loads this object. </summary>
///
/// <remarks>   William, 5/10/2015. </remarks>
///-------------------------------------------------------------------------------------------------

void LaplaceDataSet::Load(void)
{
    // Go throught the laplace transform table.
    //1. 1
    this->dataPoints.push_back(fnn::DataPoint(
        [](double x){return 1; },
        [](double x){return (1.0 / x); }
    ));
    this->dataPoints.push_back(fnn::DataPoint(
        [](double x){return x; },
        [](double x){return (1.0 / std::pow(x, 2)); }
    ));

    this->dataPoints.push_back(fnn::DataPoint(
        [](double x){return std::pow(x, 2); },
        [](double x){return (2.0 / std::pow(x, 3)); }
    ));

    for (int i = 0; i < 20; i++){
        this->dataPoints.push_back(fnn::DataPoint(
            [i](double x){return std::pow(x,i); },
            [i](double x){return ((fnn::Math::Factorial(i)*1.0) / std::pow(x, i+1)); }
        ));
    }

    for (int a = 0; a < 10; a++)
    {
        this->dataPoints.push_back(fnn::DataPoint(
            [a](double x){return std::exp(a*x); },
            [a](double x){return (1.0 / (x - a)); }
        ));

    }

    for (int a = 0; a < 10; a++)
        this->dataPoints.push_back(fnn::DataPoint(
            [a](double x){return std::cos(a*x); },
            [a](double x){return (pow(x,1) / (std::pow(x, 2)+std::pow(a,2))); }
        ));


}

