///=================================================================================================
// file:	FNNMath.cpp
// 
// summary:	Implements the FNN mathematics class. 
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNMath.h"
#include <random>
#include <time.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

///=================================================================================================
/// <summary>   Numerically integrates any integrable function using Simpson's rule with auto
///             scaling. </summary>
///
/// <remarks>   William Guss, 4/6/2015. </remarks>
///
/// <param name="f">    The function to integrate. </param>
/// <param name="a">    The lower bound of integration. </param>
/// <param name="b">    The upper bound of integration. </param>
///
/// <returns>   The result. </returns>
///-------------------------------------------------------------------------------------------------

double fnn::Math::NIntegrate(std::function<double(double)> f, double a, double b)
{
	
	return(0.0);
}

///=================================================================================================
/// <summary>   Numerically integrates any integrable function on a compact Hausdorff space.
///             Integration occurs using Simpson's rule. </summary>
///
/// <remarks>   William Guss, 4/6/2015. </remarks>
///
/// <param name="f">    The function to integrate. </param>
/// <param name="a">    The lower bound of integration. </param>
/// <param name="b">    The upper bound of integration. </param>
/// <param name="eps">  The step-size of integration using Simpson's rule. </param>
///
/// <returns>   The result. </returns>
///-------------------------------------------------------------------------------------------------

double fnn::Math::NIntegrate(std::function<double(double)> f, double a, double b, double eps)
{
        
    double h = (b - a) / eps;
    double s = f(a) + f(b);

    for (int i = 1; i < eps; i += 2)
        s += 4 * f(a + i*h);
    for (int i = 2; i < eps - 1; i += 2)
        s += 2 * f(a + i*h);
	
    
    return s*h /3;
}


///=================================================================================================
/// <summary>   Uniform real. </summary>
///
/// <remarks>   William Guss, 4/11/2015. </remarks>
///
/// <param name="min">  The minimum. </param>
/// <param name="max">  The maximum. </param>
///
/// <returns>   A double. </returns>
///-------------------------------------------------------------------------------------------------

double fnn::Math::UniformReal(double min, double max)
{
    std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 engine(time(NULL));
    return distribution(engine);
}

///=================================================================================================
/// <summary>   Gaussian real. </summary>
///
/// <remarks>   William Guss, 4/11/2015. </remarks>
///
/// <param name="mean"> The mean. </param>
///
/// <returns>   A double. </returns>
///-------------------------------------------------------------------------------------------------

double fnn::Math::GaussianReal(double mean, double dev)
{
    std::normal_distribution<double> distribution(mean, dev);
    static std::mt19937 engine(time(NULL));
    return distribution(engine);
}

///=================================================================================================
/// <summary>   A polynomial multiplication helper </summary>
///
/// <remarks>   Phillip Kuznetsov, 4/19/2015. </remarks>
///
/// <param name="poly1">A vector of the coefficients. Each index is the power which x is raised to</param>
///
/// <param name="poly2">A vector of the second polynomial coefficients./param>
/// 
/// <returns>   A vector of coefficients for hte polynomial </returns>
///-------------------------------------------------------------------------------------------------

std::vector<double> fnn::Math::PolyMult(std::vector<double> poly1, std::vector<double> poly2)
{
	std::vector<double> retPoly;
	for (auto i = 0; i < poly1.size(); i++)
	{
		for (auto j = 0; j < poly2.size(); j++)
		{
			//The term  = : x^term of hte polynomial. Also the index of the output vector
			int term = i*j;
			double coeff = poly1[i] * poly2[i];

				if (retPoly.size() == term)
				{
					retPoly.push_back(coeff);
				}
				else if (retPoly.size() < term)
				{
                    std::cout << "Error " << 1 << "occurred in poylnomial multiplication";
				}
				else
				{
					retPoly[term] += coeff;
				}
		}
	}
	return retPoly;
}

///=================================================================================================
/// <summary>   A linear interpolation algorithm. </summary>
///
/// <remarks>   Phillip Kuznetsov, 4/18/2015. </remarks>
///
/// <param name="data"> 2D vector of input data points. </param>
///
/// <returns>   A linear interpolation function. </returns>
///-------------------------------------------------------------------------------------------------

std::function<double(double)> fnn::Math::LERP(std::vector<std::vector<double>> data)
{
	//data has to be sorted first according to x values
	std::sort(data.begin(), data.end(), [](const std::vector<double>& a, const std::vector<double>& b){ return a[0] > b[0]; });
	//coded with the assumption it is already sorted.
	std::vector<std::function<double(double)>> functions;
	std::vector<double> ranges{ data[0][0] };
	for (auto i = 0; i < data.size() - 1; i++)
	{
		std::vector<double> pt1 = data[i];
		std::vector<double> pt2 = data[i+1];
		double slope = (pt1[1] - pt2[1]) / (pt1[0] - pt2[0]);
		double intercept = pt1[1] - slope*pt1[0];
        functions.push_back([slope, intercept](double x){ return x*slope + intercept;  });
		ranges.push_back(pt2[0]);
	}

	auto func = [functions, ranges](double x){

        if (x < ranges[0]){
            std::cout << x << " is outside of the bounds: [" << ranges[0] << "," << ranges[ranges.size() - 1] << "]. \n Returning -2^32.";
            return -pow(2, 32);
        }

		for (auto i = 0; i < ranges.size()-1; i++)
				return functions[i](x);
		
		
		std::cout << x << " is outside of the bounds: ["<<ranges[0]<<","<<ranges[ranges.size()-1]<<"]. \n Returning -2^32.";
		
		return -pow(2, 32);
	};
	return func;
}

///=================================================================================================
/// <summary>   A polynomial interpolation algorithm according to http://en.wikipedia.org/wiki/Polynomial_interpolation </summary>
///
/// <remarks>   Phillip Kuznetsov, 4/19/2015. </remarks>
///
/// <param name="data"> 2D vector of input data points. Each row is a point. </param>
///
/// <returns>   A polynomial interpolation function </returns>
///-------------------------------------------------------------------------------------------------

std::function<double(double)> fnn::Math::PERP(std::vector<std::vector<double>> data)
{
	//coefficient vector such that each num is a coefficient to x^index.
	std::vector<double> coef;
	
	for (auto i = 0; i < data.size(); i++)
	{
		std::vector<double> pti = data[i];
		std::vector<double> tempCf;
		double denom = 1;
		for (auto j = 0; j < data.size(); j++)
		{
			if (i == j) continue;
			std::vector<double> ptj = data[j];
			std::vector<double> poly{ -ptj[0], 1 };
			if (tempCf.size() == 0)
			{
				tempCf = poly;
				continue;
			}
			tempCf = fnn::Math::PolyMult(tempCf, poly);
			denom *= pti[0] - ptj[0];
		}
		double mult = denom * pti[1];
		for (auto i = 0; i < tempCf.size(); i++)
		{
				if (coef.size() == i)
				{
					coef.push_back(tempCf[i] * mult);
				}
				else if (coef.size() < i)
				{
                    std::cout << "Mismatch of tempCF and coef";
				}
				else
				{
					coef[i] += tempCf[i] * mult;
				}

		}
	}
	auto func = [coef](double x){
		double output = 0;
		for (auto i = 0; i < coef.size(); i++)
		{
			output += coef[i] * pow(x, i);
		}
		return output; };
	return func;
}

