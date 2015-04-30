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
	std::vector<double> ret;
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
		std::cout << "{"<<matrix[i][0];
		for (auto j = 1; j < matrix[0].size(); j++)
		{
			std::cout << "," << matrix[i][j];
		}
		std::cout << "},\n";
	}
	std::cout << "};";

	//This loop solves the row-echelon equastion.
	for (auto i = 0; i < matrix.size(); i++)
	{
		std::vector<double> cur = matrix[i];
		//first reduce the specific vector component to one.
		for (auto j = 0; j < cur.size(); j++)
		{
			cur[j] /= cur[i];
		}
		//then subtract from the other matrices
		for (auto kek = 0; kek < matrix.size(); kek++)
		{
			if (kek == i)
			{
				continue;
			}
			//copy the value of cur into a temp solver
			std::vector<double> tempSol(cur.size());
			std::copy(cur.begin(), cur.end(), tempSol);
			double scaler = -matrix[kek][i];
			for (auto lol = 0; lol < cur.size(); lol++)
			{
				matrix[kek][lol] += tempSol[lol] * scaler;
			}
		}
	}
	//places everything into a neat old loop.
	for (auto i = 0; i < matrix.size(); i++)
	{
		ret.push_back(matrix[i][matrix.size() - 1]);
	}
	return ret;
}

