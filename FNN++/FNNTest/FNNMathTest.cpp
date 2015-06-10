#include "stdafx.h"
#include "FNNMath.h"
#include "CppUnitTest.h"

#include <vector>
#include <functional>
#include <iostream>
using std::vector;
using std::cout;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fnn;

namespace FNNTest
{
    TEST_CLASS(FNNMathTest)
    {
    public:

        ///=================================================================================================
        /// <summary>   Tests NIntegrate. </summary>
        ///
        /// <remarks>   William, 5/3/2015. </remarks>
        ///
        /// <param name="parameter1">   The first parameter. </param>
        ///-------------------------------------------------------------------------------------------------

        TEST_METHOD(NIntegrateTest)
        {
            auto f = [](double x) { return 3 * x*x;  };
/*            Assert::AreEqual((int)8.0, (int)fnn::Math::NIntegrate(f, 0, 2, 20));
            Assert::AreEqual(1000.0, Math::NIntegrate(f, 0, 10, 20)*/
        }

        ///=================================================================================================
        /// <summary>   Tests datasorting. </summary>
        ///
        /// <remarks>   William, 5/3/2015. </remarks>
        ///
        /// <param name="parameter1">   . </param>
        ///-------------------------------------------------------------------------------------------------

        TEST_METHOD(DataSortTest){
            vector<vector<double>> unsorteddata = { { -5, -0.9999092043 }, { 3.25, 0.996998 }, { 1., 0.761594 }, { 2.25,
                0.978026 }, { -1.75, -0.941376 }, { -1., -0.761594 }, { 3.,
                0.995055 }, { -1.75, -0.941376 }, { 3.5, 0.998178 }, { 2.75,
                0.99186 }, { 2.25, 0.978026 }, { 0.75,
                0.635149 }, { -2.25, -0.978026 }, { -0.75, -0.635149 }, { 0.5,
                0.462117 }, { -2., -0.964028 }, { 0., 0. }, { 3.5, 0.998178 }, { 3.25,
                0.996998 }, { -1.25, -0.848284 }, { 2.5, 0.986614 }, { 2.25,
                0.978026 }, { -1.5, -0.905148 }, { 1.25, 0.848284 }, { 1.25,
                0.848284 }, { -2., -0.964028 }, { 2.75,
                0.99186 }, { -3.5, -0.998178 }, { 1., 0.761594 }, { 3.,
                0.995055 }, { -3.5, -0.998178 }, { 0.5, 0.462117 }, { 1.75, 0.941376 } };

            Math::DataSort(unsorteddata);
            std::cout << "\n{";
            for (unsigned int i = 0; i < unsorteddata.size(); i++)
            {
                cout << "{";
                for (auto j = 0; j < 2; j++)
                {
                    cout << unsorteddata[i][j] << ",";
                }
                cout << "},\n";
            }
        }

        ///=================================================================================================
        /// <summary>   Tests polynomial . </summary>
        ///
        /// <remarks>   William, 5/3/2015. </remarks>
        ///
        /// <param name="parameter1">   The first parameter. </param>
        ///-------------------------------------------------------------------------------------------------

        TEST_METHOD(PolyMultTest){
            std::vector<double> poly1{ -1, 1, 4, 5, -2 };
            std::vector<double> poly2{ 1, -2, 1, -3, 9, 1 };
            std::vector<double> ya = fnn::Math::PolyMult(poly1, poly2);
            std::cout << ya[0];

            cout << "\nPolynomial multiplication: \nPoly1: {";
            for (unsigned int i = 0; i < poly1.size(); i++)
                cout << poly1[i] << ",";
            cout << "}\nPoly2: {";
            for (unsigned int i = 0; i < poly2.size(); i++)
                cout << poly2[i] << ",";
            cout << "}\nResult: {";
            for (unsigned int i = 0; i < ya.size(); i++)
                cout << ya[i] << ",";
            cout << "}";
        }

        ///=================================================================================================
        /// <summary>   Tests the simple spline test. </summary>
        ///
        /// <remarks>   William, 5/3/2015. </remarks>
        ///
        /// <param name="parameter1">   The first parameter. </param>
        ///-------------------------------------------------------------------------------------------------

        TEST_METHOD(SSplineTest){
            vector<vector<double>> tanhdata = { { -5, -0.9999092043 }, { -4, -0.9993292997 }, { -3.75, -0.998894 }, { -3.5, -0.998178 }, { -3.25, -0.996998 }, { -3., -0.995055 }, { -2.75, -0.99186 }, { -2.5, -0.986614 }, { -2.25, -0.978026 }, { -2., -0.964028 }, { -1.75, -0.941376 }, { -1.5, -0.905148 }, { -1.25, -0.848284 }, { -1., -0.761594 }, { -0.75, -0.635149 }, { -0.5, -0.462117 }, { -0.25, -0.244919 }, { 0., 0. }, { 0.25, 0.244919 }, { 0.5, 0.462117 }, { 0.75, 0.635149 }, { 1., 0.761594 }, { 1.25, 0.848284 }, { 1.5, 0.905148 }, { 1.75, 0.941376 }, { 2., 0.964028 }, { 2.25, 0.978026 }, { 2.5, 0.986614 }, { 2.75, 0.99186 }, { 3., 0.995055 }, { 3.25, 0.996998 }, { 3.5, 0.998178 }, { 3.75, 0.998894 } };
            std::function<double(double)> perpTest = Math::SSpline(tanhdata);
			std::function<double(double)> results;
			/*Assert::AreEqual(perpTest, results);*/
        }
    };
}