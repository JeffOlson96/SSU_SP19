/*

Proj2
Estimating Pi

square side = 2; Area = 8 (s^2)
circle radius = 1 Area = pi * (1^2)
generate N ordered pairs, (x,y) where x and y < 1
calculate distance of point to origin
dis = sqrt(x^2 + y^2)

if abs_val(dis) > 1 then inside circle


eventually want to use multiple (4) threads to handle computations, 4 quadrants

*/


#include <cmath>
#include <iostream>
#include <random>
#include <vector>    // std::vector
#include <utility>  // std::pair

using namespace std;

//random number seed
static random_device rd;
static mt19937 rng(rd());

static double pi = 3.14159265358979323846;

double random_gen() {
	static uniform_real_distribution<double> udd(-1.0,1.0);
	return udd(rng);
}
/*
dis^2 = x^2 + y^2
0.4624		0.3969		0.4624
0.5184		0.4761		0.6084
------		------		------
0.9808		0.8730		1.0708

^on^edge^	^in^		^out^


this is just to see which values were outside and to convince myself its actually < 1;
*/

int main () {
	// ask user for value
	int n = 0; //number of darts in sqr
	cout << "Enter a value for the number of random numbers generated: " << endl;
	cin >> n;
	cout << endl;
	double elements = (double)n; // number of darts in circle
	//calc basic stuff
	double estimate_pi = 0.0;

	double Area_of_circle = pi;

	//array of pairs
	pair <double,double> coordinates[n]; // probably limiting the amount of n I can use

	for (int i = 0; i < n; i++) {
		//cout << random_gen() << endl;
		double x = random_gen();
		double y = random_gen();
		pair <double,double> pair1(x,y);
		coordinates[i] = pair1;
	}

	//array of pairs in circle
	pair <double,double> coordinates_send[n];
	double in_circle_count = 0;

	for (int j = 0; j < n; j++) {
		double x_calc = pow(coordinates[j].first, 2);
		double y_calc = pow(coordinates[j].second, 2);
		double distance = sqrt(x_calc + y_calc);
		//cout << distance << endl;
		if (distance > 1) {
			//cout << "outside of the circle" << endl;
		}
		else if (distance <= 1) {
			//cout << "inside of the circle!" << endl;
			in_circle_count++;
		}
	}
	cout << "n: " << n << endl;
	cout << "in_circle_count: " << in_circle_count << endl;
	estimate_pi = (4*in_circle_count)/elements;
	cout << "pi estimate: " << estimate_pi << endl;

}
