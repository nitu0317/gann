//Polynomial.h
//Author William Guss
#include<vector>
#include<string>

using std::vector;

class Polynomial1{
	public:
		Polynomial1();
		Polynomial1(vector<double> coeff);
		Polynomial1(double arr[], int size);
		
		//Evaluating the polynomial
		double operator() (double val);
		
		//Getters and setters
		double getCoeff(int i);
		double setCoeff(int i, double val);
		
		//Prints the exponential form of the polynomial.
		std::string toString();
	private:
		vector<double> coefficients;
};

//Sudo toString
std::ostream& operator<<(std::ostream &strm, const Polynomial &a) {
  return strm << a.toString();
}
