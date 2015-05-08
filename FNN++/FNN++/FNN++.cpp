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
}