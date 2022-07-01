// BLACK-SCHOLES-MERTON / GREEKS CALCULATOR IN C++

#include <iostream>
#include <cmath>
#include <math.h>
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
		double d1;
		double d2;
		double pv;
		double fin_price;
		double delta;
		double gamma;
		double vega;
		double theta;
		double rho;
	
	public:
		// Class constructor
		BSM() {
			cout << "Black Scholes Merton Model initiated." << endl;
		}

		// Define functions needed to get key BSM values
		void get_values();
		double norm_pdf(const double& x);
		double norm_cdf(const double& x);
		void get_years();

		// To ensure value inputs are correct
		double check();

		// To display BSM values
		void display_bsm();

		// Final Calculations
		void calculate();

		// Greek Calculations
		void get_greeks();
		void greeks_call();
		void greeks_put();
		void get_gamma();
		void get_vega();

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

	cout << "Current underlying price: ";
	cin >> i;
	stk_price = i;

	cout << "Strike price: ";
	cin >> i;
	strike = i;

	cout << "Risk-free interest rate (Eg. A 4% rate would mean your a input of 0.04): ";
	cin >> i;
	r = i;

	BSM::get_years();

	cout << "Volatility: ";
	cin >> i;
	v = i;
}

void BSM::get_years() {
	int choice_val;
	double time;

	cout << "Please input the time to maturity." << endl;
	cout << "Press 2 to input time as years." << endl;
	cout << "Press 1 to input time as months." << endl;
	cout << "Press 0 to input time as days." << endl;

	cin >> choice_val;
	if (choice_val >= 3 || choice_val < 0) {
		cout << "That was not a valid choice." << endl;
		BSM::get_years();
	}

	if (choice_val == 0) {
		cout << "Insert time as days: ";
		cin >> time;
		t = time / 365;
	}
	else if (choice_val == 1) {
		cout << "Insert time as months: ";
		cin >> time;
		t = time / 12;
	}
	else if (choice_val == 2) {
		cout << "Insert time as years: ";
		cin >> t;
	}
}

double BSM::norm_pdf(const double& x) {
	double dist = erfc(-x/sqrt(2.0))/2.0;
	return dist;
}

double BSM::norm_cdf(const double& x) {
	double dist = 0.5 * erfc(-x * (1.0/sqrt(2.0)));
	return dist;
}

double BSM::check() {
	double error = 0;

	if (strike <= 0) {
		cout << "Invalid strike price, try again." << endl << endl;
		error += 1;
	}
	if (stk_price <= 0) {
		cout << "Invalid underlying price, try again." << endl << endl;
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

	cout << "Underlying price: " << stk_price << endl;
	cout << "Strike price: " << strike << endl;
	cout << "Risk-free interest rate: " << r << endl;
	cout << "Time to maturity: " << t << " Years" << endl << endl << endl << endl;
} 

void BSM::calculate() {
	d1 = (1.0 / v * sqrt(t)) * (log10(stk_price / strike) + (r + (pow(v, 2.0) / 2.0) * t));
	d2 = d1 - v * sqrt(t);
	pv = strike * exp(-(r * t));
	
	if (opt_val == 1) {
		fin_price = BSM::norm_pdf(d1) * stk_price - BSM::norm_pdf(d2) * pv;
	}
	else if (opt_val == 0) {
		fin_price = BSM::norm_pdf(-1.0 * d2) * pv - BSM::norm_pdf(-1.0 * d1) * stk_price;
	}
	cout <<"OPTION PRICE: " << fin_price <<endl << endl;
}

void BSM::get_greeks() {

	void get_gamma();
	void get_vega();

	if (opt_val == 1) {
		BSM::greeks_call();
	}
	else if (opt_val == 0) {
		BSM::greeks_put();
	}

	cout << "Delta: " << delta << endl;
	cout << "Gamma: " << gamma << endl;
	cout << "Vega: " << vega << endl;
	cout << "Theta: " << theta << endl;
	cout << "Rho: " << rho << endl;
 }

void BSM::greeks_call() {
	delta = BSM::norm_cdf(d1);
	theta = -stk_price * v * BSM::norm_pdf(d1) / (2 * sqrt(t)) - (r * pv * BSM::norm_cdf(d2));
	rho = t * pv * norm_cdf(d2);
}

void BSM::greeks_put() {
	delta = BSM::norm_cdf(d1) - 1.0;
	theta = -(stk_price * v * BSM::norm_pdf(d1)) / (2 * sqrt(t)) + (r * pv * BSM::norm_cdf(-d2));
	rho = -1.0 * t * pv * BSM::norm_cdf(-1.0 * d2);
}

void BSM::get_gamma() {
	gamma = (BSM::norm_pdf(d1)) / (stk_price * v * sqrt(t));
}

void BSM::get_vega() {
	vega = stk_price * sqrt(t) * BSM::norm_pdf(d1);
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
	BSM::get_greeks();
	BSM::repeat();
}

void main() {
	BSM model;
	model.run();
}