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
    char buffer[20];
    int q;
    double x = 24.3343;
    q = sprintf_s(buffer, "%f", x);
    cout << buffer;
    system("pause");
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
    vector<vector<double>> tanhdata = { { -5, -0.9999092043 }, { -4, -0.9993292997 }, { -3.75, -0.998894 }, { -3.5, -0.998178 }, { -3.25, -0.996998 }, { -3., -0.995055 }, { -2.75, -0.99186 }, { -2.5, -0.986614 }, { -2.25, -0.978026 }, { -2., -0.964028 }, { -1.75, -0.941376 }, { -1.5, -0.905148 }, { -1.25, -0.848284 }, { -1., -0.761594 }, { -0.75, -0.635149 }, { -0.5, -0.462117 }, { -0.25, -0.244919 }, { 0., 0. }, { 0.25, 0.244919 }, { 0.5, 0.462117 }, { 0.75, 0.635149 }, { 1., 0.761594 }, { 1.25, 0.848284 }, { 1.5, 0.905148 }, { 1.75, 0.941376 }, { 2., 0.964028 }, { 2.25, 0.978026 }, { 2.5, 0.986614 }, { 2.75, 0.99186 }, { 3., 0.995055 }, { 3.25, 0.996998 }, { 3.5, 0.998178 }, { 3.75, 0.998894 } };
    std::function<double(double)> perpTest = Math::SSpline(tanhdata);
    system("pause");
    return 0;
}