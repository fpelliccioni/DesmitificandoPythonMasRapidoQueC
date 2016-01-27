// Clang: clang++ -O3 -std=c++1y mult_100_measure.cpp
// GCC:   g++ -Wall -Wextra -pedantic -O3 -std=c++1y mult_100_measure.cpp
// MSVC:  

#include "../measurements.hpp"
#include "mult_100.hpp"
#include <iostream>

using namespace std;

int main(int /*argc*/, char const * /*argv*/[]) {

	// std::cout << 
	// 			measure_min_void<100>([](){
	//     			mult_100();
	//   			}) 
	//   		  << ";";

	std::cout << 
				measure_void<10000>([](){
        			mult_100();
      			}) 
      		  << ";";

	return 0;
}



