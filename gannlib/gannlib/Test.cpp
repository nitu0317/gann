#include "Test.h"
#include <iostream>


Test::Test()
{
}


Test::~Test()
{
}

void Test::Hello()
{
	std::cout << "Hello ";
	World();
}

void Test::World()
{
	std::cout << " World!" << std::endl;
}


void Test::PrintVector()
{
}