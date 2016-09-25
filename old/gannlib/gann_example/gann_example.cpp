// gann_example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Test.h"

#include<iostream>

int main()
{
	std::cout << "Test C++!" << std::endl;
	// C++ is awesome!
	Test bananas = Test();
	bananas.Hello();


	std::cin.get();

    return 0;
}

