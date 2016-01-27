// Clang: clang++ -O3 -std=c++1y mult_100.cpp

// GCC:   g++ -Wall -Wextra -pedantic -O3 -std=c++1y mult_100.cpp
// GCC:   g++ -Wall -Wextra -pedantic -std=c++1y mult_100.cpp
// GCC:   g++ -S -Wall -Wextra -pedantic -O3 -std=c++1y mult_100.cpp
// GCC:   g++ -S -Wall -Wextra -pedantic -std=c++1y mult_100.cpp

// MSVC:  

#include "mult_100.hpp"

int main(int /*argc*/, char const * /*argv*/[]) {
	mult_100();
	
	return 0;
}
