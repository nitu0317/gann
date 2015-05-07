#pragma once

#ifdef FNNDLL
#ifdef FNNLIB_EXPORTS
#define FNNLIB  __declspec(dllexport)   // export DLL information
#else
#define FNNLIB  __declspec(dllimport)   // import DLL information
#endif
#else
#define FNNLIB
#endif

#include <functional>
namespace fnn
{
	struct DataPoint
	{
		std::function<double(double)> input;
		std::function<double(double)> desired;
	};
}

