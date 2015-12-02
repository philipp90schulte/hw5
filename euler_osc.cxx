/**
 * Homework 5
 * Author: Philipp Schulte
 * Date: 01.12.2015
 * 
 * Description:
 * Write a program that solves the linear oscillator equation
 * subject to the given initial conditions. Implement the Euler forward and the Euler backward method. 
 * Integrate from t=0 to t=20pi and create a plot which compares both numerical solutions x(t) to the analytic solution. 
 * Next to your code submit two plots, one for dt = pi/10 and one for dt = pi/100.
 * 
 * 			x^(2) + x = 0;  x(0) = 1, x^(1)(0) = 0;
 * 
 * Note:
 * You will need arrays of length two (since this results in a two-dimensional ODE system)
 * For the implicit method:
 * 		write down the formal implicit Euler method
 * 		insert your right-hand side f
 * 		now analytically solve for y_{n+1} to obtain the formula you have to implement
 * 
 * 
 * 
 * 
 */


#include <cmath>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

// Define the needed functions
void calcanalytical(double* e, const int N, const double tstep);
void calceulerfor(double* e, const int N, const double tstep);
void calceulerback(double* e, const int N, const double tstep);
void printresult(double* e, const int N, const string outputname, const double tstep);

// main function
int main() {
	int N = 200;
	double* e = new double[2*(N+1)];
	double tstep = M_PI / 10;
	
	// fill in the start conditions
	e[0] = 1;
	e[1] = 0;
	
	
	// Calculate forward Euler with step size Pi/10
	calcanalytical(e, N, tstep);
	printresult(e, N, "analytical.txt", tstep);
	calceulerfor(e, N, tstep);
	printresult(e, N, "eulerfor.txt", tstep);
	calceulerback(e, N, tstep);
	printresult(e, N, "eulerback.txt", tstep);
	
	tstep = tstep / 10;
	N = 2000;
	
	// Calculate forward Euler with step size Pi/100
	calcanalytical(e, N, tstep);
		printresult(e, N, "analytical2.txt", tstep);
	calceulerfor(e, N, tstep);
	printresult(e, N, "eulerfor2.txt", tstep);
	calceulerback(e, N, tstep);
	printresult(e, N, "eulerback2.txt", tstep);
	
	
	//delete the created arrays
	delete[] e; 
	
	
	return 0;
}

void calcanalytical(double* e, const int N, const double tstep) {
	for (int i = 1; i <= N; i++) {
		e[i*2] = cos (i * tstep);
	}
	
}

void calceulerfor(double* e, const int N, const double tstep) {
	for (int i = 1; i <= N; i++) {
			e[i*2] = e[(i-1)*2] + tstep * e[(i*2)-1];
			e[(i*2)+1] = e[(i*2)-1] - tstep * e[(i-1)*2];
		}
	
}

void calceulerback(double* e, const int N, const double tstep) {
	for (int i = 1; i <= N; i++) {
		e[i*2] =e[i*2-1] * tstep + e[(i-1)*2] * (1 - tstep * tstep);
		e[i*2+1] = -1 * e[(i-1)*2] * tstep + e[i*2-1] * (1 - tstep * tstep);
	}	
}

void printresult(double* e, const int N, const string outputname, const double tstep) {
	ofstream out(outputname.c_str());
	double t;
	for (int i = 0; i <= N; i++) {
		t = i * tstep;
		out << t << "\t" << e[i*2] << endl;
	}
	
	out.close();
}
