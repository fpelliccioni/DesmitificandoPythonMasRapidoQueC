// clang++ -O3 -std=c++1y test_size_of.cpp
// /Users/gordo/soft/llvm-build-release/Release+Asserts/bin/clang++ -O3 -std=c++1y -stdlib=libc++ -nostdinc++ -I/Users/gordo/soft/libcxx/include test_size_of.cpp
// g++ -O3 -std=c++11 test_size_of.cpp

// With linker optimization to strip the binary (not used code removal)
// /Users/gordo/soft/llvm-build-release/Release+Asserts/bin/clang++ -O3 -std=c++1y -Wl,-dead_strip -stdlib=libc++ -nostdinc++ -I/Users/gordo/soft/libcxx/include test_size_of.cpp

// g++ test_size_of.cpp -O3 -I/Users/gordo/soft/boost_1_57_0 -I/Users/gordo/soft/nt2-build/include -L/Users/gordo/soft/nt2-build/lib -lnt2
// clang++ test_size_of.cpp -O3 -I/Users/gordo/soft/boost_1_57_0 -I/Users/gordo/soft/nt2-build/include -L/Users/gordo/soft/nt2-build/lib -lnt2



#include <typeinfo>
#include <iostream>

using namespace std;
int main(int argc, char const *argv[]) {


	cout << typeid(size_t).name() << endl;
	cout << typeid(unsigned long).name() << endl;
	cout << typeid(unsigned long long).name() << endl;

	
	return 0;
}