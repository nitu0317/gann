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


void testMath();

int _tmain(int argc, _TCHAR* argv[])
{
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


void testMath(){
  
    system("pause");
    //A test of LERP
    vector<vector<double>> tanhdata = { { -5, -0.9999092043 }, { -4, -0.9993292997 }, { -3.75, -0.998894 }, { -3.5, -0.998178 }, { -3.25, -0.996998 }, { -3., -0.995055 }, { -2.75, -0.99186 }, { -2.5, -0.986614 }, { -2.25, -0.978026 }, { -2., -0.964028 }, { -1.75, -0.941376 }, { -1.5, -0.905148 }, { -1.25, -0.848284 }, { -1., -0.761594 }, { -0.75, -0.635149 }, { -0.5, -0.462117 }, { -0.25, -0.244919 }, { 0., 0. }, { 0.25, 0.244919 }, { 0.5, 0.462117 }, { 0.75, 0.635149 }, { 1., 0.761594 }, { 1.25, 0.848284 }, { 1.5, 0.905148 }, { 1.75, 0.941376 }, { 2., 0.964028 }, { 2.25, 0.978026 }, { 2.5, 0.986614 }, { 2.75, 0.99186 }, { 3., 0.995055 }, { 3.25, 0.996998 }, { 3.5, 0.998178 }, { 3.75, 0.998894 } };
    
    system("pause");
    function<double(double)> perpTest = Math::SSpline(tanhdata);
    system("pause");
}