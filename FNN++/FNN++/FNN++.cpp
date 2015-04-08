// FNN++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FNNMath.h"
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
    auto f = [](double x) { return 2*x; };

    std::cout << fnn::Math::NIntegrate(f, 0, 100, 2) << std::endl;
    
    system("pause");


    return 0;
}

