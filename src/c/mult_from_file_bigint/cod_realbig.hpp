#ifndef COD_REALBIG_HPP_
#define COD_REALBIG_HPP_


#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::interprocess;
using namespace boost::multiprecision;

using int101_t = number<cpp_int_backend<101, 101, signed_magnitude, unchecked, void>>;
using int201_t = number<cpp_int_backend<201, 201, signed_magnitude, unchecked, void>>;
//2 ^ 201 / 2 - 1 = 1606938044258990275541962092341162602522202993782792835301375    -> 61 chars

//using int_type = int201_t;
using int_type = int256_t;
//using int_type = int101_t;

// Concepts
#define IntegerType typename

//unchecked bounds
template <IntegerType I, size_t N>
I range_to_bigint(const char* buffer) {
	char bufmut[N + 1] = {};	// zero initialization
	auto non_space = find_if_not(buffer, buffer + N, [](char x) {return x == ' ';});
	memcpy(bufmut, non_space, N - (non_space - buffer));
	return I{bufmut};
}

void mult_files_big_buffer() {
	file_mapping f_mapped("src_realbig.txt", read_only);
	mapped_region f_region(f_mapped, read_only);

	const char* buffer = (const char*)(f_region.get_address());
	const char* end = buffer + f_region.get_size();
	FILE* out = fopen("out_realbig.txt", "w");

	while (buffer != end) {

		++buffer;
		auto uno = range_to_bigint<int_type, 31>(buffer);

		buffer += 33; //31 + 2 (spaces)
		auto dos = range_to_bigint<int_type, 31>(buffer);
		buffer += 33; //31 + 2 (CRLF)

		//auto resultado = static_cast<int201_t>(uno) * dos;
		auto resultado = uno * dos;

		fprintf(out, "%s\n", resultado.str().c_str());
		//cout << "resultado: " << resultado << endl;
	}

	fclose(out);
}

#endif // COD_REALBIG_HPP_


