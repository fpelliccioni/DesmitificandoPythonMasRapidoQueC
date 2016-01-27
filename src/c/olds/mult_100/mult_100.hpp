#ifndef MULT_100_HPP_
#define MULT_100_HPP_

#include <cstddef>

void mult_100() {
	int a = 5, b = 10;

	for (size_t i{0}; i < 100000; ++i) {
	    int c = a * b;
	}
}

#endif // MULT_100_HPP_
