// BLACK-SCHOLES-MERTON CALCULATOR IN C++

#include <iostream>
#include <cmath>
#include <random>
using namespace std;

class BSM {
	private:
		// Define values taken into BSM model
		
		double opt_val; 
		double opt_price; 
		double stk_price;
		double strike; 
		double r; 
		double t; 
		double v;
		double fin_price;
	
	public:
		// Class constructor
		BSM() {
			cout << "Black Scholes Model initiated." << endl;
		}

		// Define functions needed to get key BSM values
		void get_values();
		double norm_pdf(const double& x);

		// To ensure value inputs are correct
		double check();

		// To display BSM values
		void display_bsm();

		// Final Calculations
		void calculate();

		// Call repeat
		double repeat();

		// Calls function in a flow
		void run();

};

void BSM::get_values() {
	double i;
	cout << "For PUT option press 0." << endl;
	cout << "For CALL option press 1." << endl;
	cin >> i;
	if (i == 0) {
		cout << "PUT option selected." << endl;
		opt_val = 0;
	}
	else if (i == 1) {
		cout << "CALL option selected." << endl;
		opt_val = 1;
	}
	else {
		cout << "That was not a valid input." << endl;
	}

	cout << "Stock price: ";
	cin >> i;
	stk_price = i;

	cout << "Strike price: ";
	cin >> i;
	strike = i;

	cout << "Risk-free interest rate (Eg. A 4% rate would mean your a input of 0.04): ";
	cin >> i;
	r = i;

	cout << "Time to maturity (In years): ";
	cin >> i;
	t = i;

	cout << "Volatility: ";
	cin >> i;
	v = i;
}

double BSM::norm_pdf(const double& x) {
	double dist = erfc(-x/sqrt(2))/2;
	return dist;
}

double BSM::check() {
	double error = 0;

	if (strike <= 0) {
		cout << "Invalid strike price, try again." << endl << endl;
		error += 1;
	}
	if (stk_price <= 0) {
		cout << "Invalid stock price, try again." << endl << endl;
		error += 1;
	}
	if (r < 0 || r > 1) {
		cout << "Invalid risk-free rate, try again." << endl << endl;
		error += 1;
	}
	if (t <= 0) {
		cout << "Invalid time to maturity, try again." << endl << endl;
		error += 1;
	}
	if (v <= 0) {
		cout << "Invalid volatility, try again." << endl << endl;
		error += 1;
	}

	return error;
}

void BSM::display_bsm() {
	if (opt_val == 1) {
		cout << "BLACK SCHOLES MERTON MODEL (CALL)" << endl;
	}
	else {
		cout << "BLACK SCHOLES MERTON MODEL (PUT)" << endl;
	}

	cout << "Stock price: " << stk_price << endl;
	cout << "Strike price: " << strike << endl;
	cout << "Risk-free interest rate: " << r << endl;
	cout << "Time to maturity: " << t << " Years" << endl << endl << endl << endl;
} 

void BSM::calculate() {
	double d1 = (1.0 / v * sqrt(t)) * (log10(stk_price / strike) + (r + (pow(v, 2.0) / 2.0) * t));
	double d2 = d1 - v * sqrt(t);
	double pv = strike * exp(-(r * t));
	
	if (opt_val == 1) {
		fin_price = BSM::norm_pdf(d1) * strike - BSM::norm_pdf(d2) * pv;
	}
	else if (opt_val == 0) {
		fin_price = BSM::norm_pdf(-1.0 * d2) * pv - BSM::norm_pdf(-1.0 * d2) * strike;
	}
	BSM::display_bsm();
	cout <<"OPTION PRICE: " << fin_price <<endl << endl;
}

double BSM::repeat() {

	char pick;
	cout << "Do you wish to make another calculation? Y/N" << endl;
	cin >> pick;
	
	if (pick == 'y' || pick == 'Y') {
		BSM::run();
	}
	else if (pick == 'n' || pick == 'N') {
		return(0);
	}
	else {
		cout << "That was not a valid input, please try again." << endl;
		BSM::repeat();
	}
	
}

void BSM::run() {

	BSM::get_values();
	double error = BSM::check();

	if (error >= 1) {
		BSM::run();
	}

	BSM::display_bsm();
	BSM::calculate();
	BSM::repeat();
}

void main() {
	BSM model;
	model.run();
}