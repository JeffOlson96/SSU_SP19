/* Monte Carlo Solution to Estimating Pi using 4 threads

   Jeff Olson
   3/25/19
   CS 450
   Project 2

   Program splits points into 4 quadrants and then uses threads to compute how many points
   are in side the of the radius of the circle (1). 
    


*/



#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <thread>
#include <mutex>
#include <ctime>
#include <unistd.h>


const int TOTAL_POINTS = 200000000;

struct Point {
    Point(double xx, double yy): x{xx}, y{yy} {}

    void print() { std::cout << "(" << x << ", " << y << ")\n"; }
    double x, y;
};

double nextRand() {
    // return a value in the range (-1, 1)

    return (rand() / double(RAND_MAX)) * 2 - 1;
}

void countInCircle(const std::vector<Point> &points, int ret[4], int quad_num) {
    int inCircle = 0;
    for( auto iter = points.begin(); iter != points.end(); iter++ ) {
        if( sqrt( iter->x * iter->x + iter->y * iter->y ) <= 1.0 ) {
            inCircle++;
       }
    }       
    ret[quad_num] = inCircle;
}

void generatePoints(std::vector<Point> &points) {
    // Generates TOTAL_POINTS points.

    for( int i = 0; i < TOTAL_POINTS; i++ ) { 
	   points.push_back(Point(nextRand(), nextRand()));
    }
}

std::vector <Point> Quadrant_func(std::vector<Point> &points, int quad_num) {
    //returns a temp vector for the number of points in a specified quadrant
    std::vector <Point> q_temp;
    for (auto it = points.begin(); it != points.end(); it++) {
        if( it->x > 0 && it->y > 0 && quad_num == 0) {
            q_temp.push_back(*it);
        }  
        else if( it->x > 0 && it->y < 0 && quad_num == 1) {
            q_temp.push_back(*it);
        }
        else if( it->x < 0 && it->y < 0 && quad_num == 2) {
            q_temp.push_back(*it);
        }
        else if( it->x < 0 && it->y > 0 && quad_num == 3) {
            q_temp.push_back(*it);
        }
    }
    return q_temp;
}





int main() {
    // set up
    clock_t program_time;
    program_time = clock();
    
    
    srand(getpid());
    std::vector<Point> points;
    std::thread t[4];
    generatePoints(points);
    int ret_in_circle[4];
    

    clock_t thread_time;
    thread_time = clock();
    
    // create threads
    

    for (int i = 0; i < 4; i++) {
        t[i] = std::thread(&countInCircle, Quadrant_func(points, i), ret_in_circle, i);
    }

    for ( int i = 0; i < 4; i++) {
        t[i].join();
    }
    thread_time = clock() - thread_time;
    int count = 0;
    for (int i = 0; i < 4; i++) {
        count += ret_in_circle[i];
    }
    program_time = clock() - program_time;
    //std::cout << "Runtime for threads: " << (float(thread_time))/CLOCKS_PER_SEC << std::endl;
    std::cout << "Runtime for program: " << (float(program_time))/CLOCKS_PER_SEC << std::endl;
    std::cout << "PI = " << double(count) * double(4.0) / double(TOTAL_POINTS) << std::endl;
    
    return 0;
}
