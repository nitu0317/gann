// FNN++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FNNMath.h"
#include <iostream>
#include <random>
#include <stdlib.h>
#include "FNNNetwork.h"

using namespace fnn;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<double> poly1{ -1, 1 };
	std::vector<double> poly2{ 1, -2 ,1};
	std::vector<double> ya = fnn::Math::PolyMult(poly1, poly2);
	std::cout << ya[0];

	
	/*vector<vector<double>> dataset;
	vector<double> range{ -50, 50 };
	for (auto i = 0; i < 50; i++)
	{
		vector<double> point;
		for (auto j = 0; j < 2; j++)
		{
			auto fRand = [range](){
				double f = (double)rand() / RAND_MAX;
				return range[0] + f *(range[1] - range[0]);
			};
			point.push_back(fRand());
		}
		dataset.push_back(point);
	}
	auto poly = Math::PERP(dataset);
	*/

    //Construct a network
    Network net = Network();
    net.Activator = Sigmoid::Tanh();
    net.AddLayer(10, 10);
    net.AddLayer(10, 10);

    //TODO: Fix a glitch with this paret.


   
    auto f = [](double x) { return sin(x); };

    auto output = net.FeedForward(f);

    for (double x = 0; x < 10; x += 0.05)
        cout << "" << x << "=>" << output(x) << "\n";
    
    system("pause");


    return 0;
}

