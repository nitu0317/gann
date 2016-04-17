#pragma once
#include <gsl/gsl_vector.h>

class Test
{
public:
	Test();
	~Test();
	void PrintVector();
	void Hello();
private:
	void World();
	gsl_vector * test;
};

