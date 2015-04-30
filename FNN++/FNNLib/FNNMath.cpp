///=================================================================================================
// file:	FNNMath.cpp
// 
// summary:	Implements the FNN mathematics class. 
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "FNNMath.h"
#include <random>
#include <iostream>
#include <time.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>

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
	
	return fnn::Math::NIntegrate(f, a, b, (a - b) * 10); //TODO: This is kinda arbitrary but,
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
			int term = i+j;
			std::cout << "Term " << term << "\t";
			double coeff = poly1[i] * poly2[j];
			std::cout <<poly1[i] << " " << poly2[j]<< " "<< coeff<< "\n";
			
			if (retPoly.size() == term)
			{
				retPoly.push_back(coeff);
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
/// <summary>   A linear interpolation algorithm </summary>
///
/// <remarks>   Phillip Kuznetsov, 4/18/2015. </remarks>
///
/// <param name="data"> 2D vector of input data points </param>
///
/// <returns>   A linear interpolation function </returns>
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
		functions.push_back([slope, intercept](double x){return x*slope + intercept; });
		ranges.push_back(pt2[0]);
	}

	auto func = [functions, ranges](double x){
		
			if (x < ranges[0]){
				std::cout << x << " is outside of the bounds: [" << ranges[0] << "," << ranges[ranges.size() - 1] << "]. \n Returning -2^32.";
				return -pow(2, 32);
			}
		
		
		for (auto i = 0; i < ranges.size()-1; i++)
		{
			if (x >= ranges[i] && x <= ranges[i + 1])
			{
				return functions[i](x);
			}
		}
		
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
	std::cout << "Polynomial: " << coef[0];
	for (auto i = 1; i < coef.size(); i++)
	{
		std::cout << " + " << coef[i] << "*x^" << i;
	}
	std::cout << "\n";
	auto func = [coef](double x){
		double output = 0;
		for (auto i = 0; i < coef.size(); i++)
		{
			output += coef[i] * pow(x, i);
			
		}
		
		return output; };
	return func;
}

///=================================================================================================
/// <summary>   Factorial implementation. </summary>
///
/// <remarks>   William, 4/26/2015. </remarks>
///
/// <param name="n">    The int to process. </param>
///
/// <returns>   An int. </returns>
///-------------------------------------------------------------------------------------------------

int fnn::Math::Factorial(int n)
{
	if (n == 0) return 1;
	
	return n*fnn::Math::Factorial(n - 1);
}

///=================================================================================================
/// <summary>   Gauss Jordan elimination for matrices. </summary>
///
/// <remarks>   Phillip Kuznetsov, 4/29/2015. </remarks>
///
/// <param name="matrix">   The systems of equation augmented matrix. </param>
///
/// <returns>   A vector of the variable values solved by completed Gauss-Jordan elimination. </returns>
///-------------------------------------------------------------------------------------------------

std::vector<double> fnn::Math::GaussJordan(std::vector<std::vector<double>> matrix)
{

	//the return vector
	std::vector<double> ret(matrix.size());
	//This for loop reorders the matrix into row-echelon form.
	for (auto i = 0; i < matrix.size(); i++)
	{
		std::vector<double> cur = matrix[i];
		if (cur[i] == 0)
		{
			for (auto kek = 0; kek < matrix.size(); kek++)
			{
				if (kek == i)
				{
					continue;
				}
				if (matrix[kek][i] != 0 && cur[kek] != 0)
				{
					matrix[i] = matrix[kek];
					matrix[kek] = cur;
				}
			}
		}
	}
	//comment this block out during regular run time.
	std::cout << "The ordered matrix\n{";
	for (auto i = 0; i < matrix.size(); i++)
	{
		std::cout << "{" << matrix[i][0];
		for (auto j = 1; j < matrix[0].size(); j++)
		{
			std::cout << "," << matrix[i][j];
		}
		std::cout << "},\n";
	}
	std::cout << "};";

	//This loop solves the row-echelon equations.
	for (auto i = 0; i < matrix.size(); i++)
	{
		std::vector<double> cur = matrix[i];
		//first reduce the specific vector component to one.
		double scaler = cur[i];
		for (auto j = 0; j < cur.size(); j++)
		{
			cur[j] = cur[j] / scaler;
		}
		matrix[i] = cur;
		//then subtract from the other matrices
		for (auto kek = 0; kek < matrix.size(); kek++)
		{
			if (kek == i)
				continue;

			double scaler = -matrix[kek][i];
			for (auto lol = 0; lol < cur.size(); lol++)
			{
				matrix[kek][lol] += cur[lol] * scaler;
			}
		}
	}
	//comment this block out during regular run time.
	std::cout << "The ordered matrix\n{";
	for (auto i = 0; i < matrix.size(); i++)
	{
		std::cout << "{" << matrix[i][0];
		for (auto j = 1; j < matrix[0].size(); j++)
		{
			std::cout << "," << matrix[i][j];
		}
		std::cout << "},\n";
	}
	std::cout << "};\n" << ret[0];

	//places everything into a neat old loop.
	for (auto i = 0; i < matrix.size(); i++)
	{
		std::vector<double> cur = matrix[i];
		ret[i] = (cur[cur.size() - 1]);
	}
	return ret;
}

 ///=================================================================================================
 /// <summary>  A simple spline interpolation algorithm as described in
 ///            http://www.geos.ed.ac.uk/~yliu23/docs/lect_spline.pdf. Makes the assumption that
 ///            the second derivative at the boundaries is equal to 0. </summary>
 ///
 /// <remarks>  Phillip Kuznetsov, 4/29/2015. </remarks>
 ///
 /// <param name="data">    2D vector of input data points. Each row is a point. </param>
 ///-------------------------------------------------------------------------------------------------

 std::function<double(double)> fnn::Math::SSpline(std::vector<std::vector<double>> data)
{
    //make sure this actually sorts anything
    fnn::Math::DataSort(data);

    std::vector<std::vector<double>> matrix;
    //the construction of the system of linear equations matrix
    // This linear equation matrix is second derivatives of the system.
    for (auto i = 1; i < data.size() - 1; i++)
    {
        
        //the three coordinates that the current spline is working with.
        std::vector<std::vector<double>> k;
        for (auto j = i - 1; j <= i + 1; j++)
        {
            k.push_back(data[j]);
        }
        
        std::vector<double> row(data.size() + 1);
        std::fill(row.begin(), row.end(), 0);

        
        std::vector<double> coefs = { (k[1][0] - k[0][0]) / 6, (k[2][0] - k[0][0]) / 3, (k[2][0] - k[1][0]) / 6 };
        auto ctr = 0;
        for (auto l = (i - 1); l < (i - 1) + 3; l++, ctr++)
        {
            row[l] = coefs[ctr];
        }
        //this is the answer to the problem/
        double d = (k[2][1] - k[1][1]) / (k[2][0] - k[1][0]) - (k[1][1] - k[0][1]) / (k[2][0] - k[1][0]);
        row[row.size() - 1] = d;
        matrix.push_back(row);
    }
    //Adds the known values as rows in the matrix.
    for (auto i = 0; i < 2; i++)
    {
        std::vector<double> row(data.size() + 1);
        std::fill(row.begin(), row.end(), 0);
        row[0 + (row.size() - 2)*i] = 1;
        row[row.size() - 1] = 0;
        matrix.push_back(row);
    }
    //the array of the second derivatives at each point. Used to plug in the equation.
    std::vector<double> secondDeriv = fnn::Math::GaussJordan(matrix);
    
    std::vector<std::function<double(double)>> functions;
    std::vector<double> ranges{ data[0][0] };
    for (auto i = 0; i < data.size() - 1; i++)
    {
        std::vector<double> pt1 = data[i];
        std::vector<double> pt2 = data[i + 1];
		auto a = [pt1, pt2](double x){return (pt2[0] - x) / (pt2[0] - pt1[0]); };
		auto b = [a](double x){return 1 - a(x); };
		auto c = [a, pt1, pt2](double x){return (1 / 6)*(pow(a(x), 3) - a(x))*pow((pt2[0] - pt1[0]), 2); };
		auto d = [b, pt1, pt2](double x){return (1 / 6)*(pow(b(x), 3) - b(x))*pow((pt2[0] - pt1[0]), 2); };
		functions.push_back([a, b, c, d, secondDeriv, pt1, pt2, i](double x){return a(x)*pt1[0] + b(x)*pt2[0] + c(x)*secondDeriv[i] + d(x)*secondDeriv[i + 1]; });
        ranges.push_back(pt2[0]);
    }
    //the creation of the equations
    auto func = [functions, ranges](double x){

        if (x < ranges[0]){
            std::cout << x << " is outside of the bounds: [" << ranges[0] << "," << ranges[ranges.size() - 1] << "]. \n Returning -2^32.";
            return -pow(2, 32);
        }


        for (auto i = 0; i < ranges.size() - 1; i++)
        {
            if (x >= ranges[i] && x <= ranges[i + 1])
            {
                return functions[i](x);
            }
        }

        std::cout << x << " is outside of the bounds: [" << ranges[0] << "," << ranges[ranges.size() - 1] << "]. \n Returning -2^32.";

        return -pow(2, 32);
    };
    return func;
}

///=================================================================================================
/// <summary>   Data sort algorthim to sort by x-values of the data. Useful for the interpolation
///             algorithms. </summary>
///
/// <remarks>   Phillip Kuznetsov, 4/29/2015. </remarks>
///
/// <param name="data"> 2D vector of input data points. Each row is a point. </param>
///
/// <returns>   A 2D vector of the same points sorted. </returns>
///-------------------------------------------------------------------------------------------------

void fnn::Math::DataSort(std::vector<std::vector<double>> &data)
{
    std::sort(data.begin(), data.end(), [](const std::vector<double>& a, const std::vector<double>& b){ return a[0] < b[0]; });
}

