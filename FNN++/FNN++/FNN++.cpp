// FNN++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FNNMath.h"
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
    auto f = [](double x) { return 2*x; };
	std::vector<double> poly1{ -1, 1 };
	std::vector<double> poly2{ -1, 1 };
	std::vector<double> ya = fnn::Math::PolyMult(poly1, poly2);
	std::cout << ya[0];
	for (int i = 1; i < ya.size(); i++)
	{
		std::cout << " + " << ya[i] << "x^" << i;
	}
    system("pause");


    return 0;
}

