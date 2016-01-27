// Clang: clang++ -O3 -std=c++1y mult.cpp

// GCC:   g++ -Wall -Wextra -pedantic -O3 -std=c++1y mult.cpp
// GCC:   g++ -Wall -Wextra -pedantic -std=c++1y mult.cpp
// GCC:   g++ -S -Wall -Wextra -pedantic -O3 -std=c++1y mult.cpp
// GCC:   g++ -S -Wall -Wextra -pedantic -std=c++1y mult.cpp

// MSVC:  

#include "mult.hpp"

int main(int /*argc*/, char const * /*argv*/[]) {
	mult();
	
	return 0;
}
