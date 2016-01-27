#ifndef COD_REALBIG_HPP_
#define COD_REALBIG_HPP_

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include <chrono>

#include "boost_multiprecision_cpp_int_ext.hpp"

using namespace std;
using namespace boost::interprocess;
using namespace boost::multiprecision;

using int101_t = number<cpp_int_backend<101, 101, signed_magnitude, unchecked, void>>;
using int201_t = number<cpp_int_backend<201, 201, signed_magnitude, unchecked, void>>;
//2 ^ 201 / 2 - 1 = 1606938044258990275541962092341162602522202993782792835301375    -> 61 chars

//using int_type = int201_t;
//using int_type = int256_t;
//using int_type = int101_t;

// Concepts
#define IntegerType typename

//unchecked bounds
template <IntegerType I, size_t N>
I range_to_bigint_with_copy(const char* buffer) {
	char bufmut[N + 1] = {};	// zero initialization
	auto non_space = find_if_not(buffer, buffer + N, [](char x) {return x == ' ';});
	memcpy(bufmut, non_space, N - (non_space - buffer));
	return I{bufmut};
}

//unchecked bounds
template <IntegerType I, size_t N>
I range_to_bigint_without_copy(const char* buffer) {
	auto non_space = find_if_not(buffer, buffer + N, [](char x) {return x == ' ';});
	I x;
	tie(x, ignore, ignore) = make_from_counted_range_dec<I>(non_space, N - (non_space - buffer));
	return x;
}


#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <fstream>
//#include <string>
//#include <vector>
//#include <cstring>
#include <cstddef>
#include <cstdlib>


template <typename IntMax, typename IntMin>
inline
void mult_big_vector(std::vector<std::pair<IntMin, IntMin>> const& c, std::vector<IntMax>& output) {
		
	for (auto&& p : c) {
		auto uno = p.first;
		auto dos = p.second;
		auto x = static_cast<IntMax>(uno) * dos;
		output.emplace_back(x);
	}
}

template <typename IntMax, typename IntMin>
inline
int64_t mult_big_vector_hot(vector<pair<IntMin, IntMin>> const& c, vector<IntMax>& output) {
	using namespace std;
	using namespace std::chrono;

	auto f = begin(c);
	auto m = f + c.size() * 0.2;
	auto l = end(c);

	//cout << "distance(f, m):  " << distance(f, m) << endl;
	//cout << "distance(m, l,): " << distance(m, l) << endl;
	//cout << "distance(f, l):  " << distance(f, l) << endl;
	//cout << "c.size() * 0.2:  " << (c.size() * 0.2) << endl;

	//auto concrete_iterations = distance(m, l);

	while (f != m) {
		auto uno = (*f).first;
		auto dos = (*f).second;
		auto x = static_cast<IntMax>(uno) * dos;
		output.emplace_back(x);
		++f;
	}


	high_resolution_clock::time_point measure_start = high_resolution_clock::now();

	while (m != l) {
		auto uno = (*m).first;
		auto dos = (*m).second;
		auto x = static_cast<IntMax>(uno) * dos;
		output.emplace_back(x);
		++m;
	}

	//cout << "concrete_iterations: " << concrete_iterations << endl;

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	return duration_cast<nanoseconds>(t2 - measure_start).count();
}

template <typename IntMax, typename IntMin>
inline
int64_t mult_big_vector_no_out_hot(std::vector<std::pair<IntMax, IntMin>>& c) {
	using namespace std;
	using namespace std::chrono;

	auto f = begin(c);
	auto m = f + c.size() * 0.2;
	auto l = end(c);

	while (f != m) {
		auto uno = (*f).first;
		auto dos = (*f).second;
		//(*f).first = static_cast<IntMax>(uno) * dos;
		(*f).first = uno * dos;
		++f;
	}

	high_resolution_clock::time_point measure_start = high_resolution_clock::now();

	while (m != l) {
		auto uno = (*m).first;
		auto dos = (*m).second;
		//(*m).first = static_cast<IntMax>(uno) * dos;
		(*m).first = uno * dos;
		++m;
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	return duration_cast<nanoseconds>(t2 - measure_start).count();
}


template <typename IntMin>
inline
int64_t mult_big_vector_do_nothing_hot(std::vector<std::pair<IntMin, IntMin>> const& c) {
	using namespace std;
	using namespace std::chrono;

	auto f = begin(c);
	auto m = f + c.size() * 0.2;
	auto l = end(c);

	while (f != m) {
		auto uno = (*f).first;
		auto dos = (*f).second;
		//auto prod = static_cast<IntMax>(uno) * dos;
		++f;
	}

	high_resolution_clock::time_point measure_start = high_resolution_clock::now();

	while (m != l) {
		auto uno = (*m).first;
		auto dos = (*m).second;
		//auto prod = static_cast<IntMax>(uno) * dos;
		++m;
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	return duration_cast<nanoseconds>(t2 - measure_start).count();
}

//inline
//int64_t mult_big_vector_do_nothing_int201_t_hot(std::vector<std::pair<int201_t, int101_t>> const& c) {
//	using namespace std;
//	using namespace std::chrono;
//
//	auto f = begin(c);
//	auto m = f + c.size() * 0.2;
//	auto l = end(c);
//
//	int201_t prod;
//
//	while (f != m) {
//		auto uno = (*f).first;
//		auto dos = (*f).second;
//		prod = uno * dos;
//		++f;
//	}
//
//	high_resolution_clock::time_point measure_start = high_resolution_clock::now();
//
//	while (m != l) {
//		auto uno = (*m).first;
//		auto dos = (*m).second;
//		prod = uno;
//		//prod *= dos;
//		//prod = uno * dos;
//		++m;
//	}
//
//	high_resolution_clock::time_point t2 = high_resolution_clock::now();
//	return duration_cast<nanoseconds>(t2 - measure_start).count();
//}

std::vector<std::pair<int101_t, int101_t>> load_from_file() {

	std::vector<std::pair<int101_t, int101_t>> res;
	res.reserve(1'000'000);

	file_mapping f_mapped("D:\\src_realbig.txt", read_only);
	mapped_region f_region(f_mapped, read_only);

	const char* buffer = (const char*)(f_region.get_address());
	const char* end = buffer + f_region.get_size();

	while (buffer != end) {

		++buffer;
		auto uno = range_to_bigint_without_copy<int101_t, 31>(buffer);

		buffer += 33; //31 + 2 (spaces)
		auto dos = range_to_bigint_without_copy<int101_t, 31>(buffer);
		buffer += 33; //31 + 2 (CRLF)

		res.emplace_back(uno, dos);
	}
	return res;
}

void mult_files_big_buffer_without_copy_mm() {
	file_mapping f_mapped("D:\\src_realbig.txt", read_only);
	mapped_region f_region(f_mapped, read_only);

	const char* buffer = (const char*)(f_region.get_address());
	const char* end = buffer + f_region.get_size();
	//FILE* out = fopen("out_realbig.txt", "w");

	using namespace boost::interprocess;

	//Define file names
	const char *FileName = "out_realbig.txt";
	const std::size_t FileSize = 60651 * 1024; // 10000;

	{  //Create a file
		file_mapping::remove(FileName);
		std::filebuf fbuf;
		//fbuf.open(FileName, std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
		fbuf.open(FileName, std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
		//Set the size
		fbuf.pubseekoff(FileSize - 1, std::ios_base::beg);
		fbuf.sputc(0);
	}

	file_mapping m_file(FileName, read_write);
	mapped_region region(m_file, read_write);
	void* addr_out = region.get_address();


	while (buffer != end) {

		++buffer;
		auto uno = range_to_bigint_without_copy<int101_t, 31>(buffer);

		buffer += 33; //31 + 2 (spaces)
		auto dos = range_to_bigint_without_copy<int101_t, 31>(buffer);
		buffer += 33; //31 + 2 (CRLF)

		auto resultado = static_cast<int201_t>(uno) * dos;
		//auto resultado = uno * dos;

		//fprintf(out, "%s\n", resultado.str().c_str());
		//cout << "resultado: " << resultado << endl;
		std::strcpy((char*)addr_out, resultado.str().c_str());
	}

	//std::size_t size = region.get_size();
	//std::memset(addr, 1, size);
	



}

void mult_files_big_buffer_without_copy() {
	file_mapping f_mapped("D:\\src_realbig.txt", read_only);
	mapped_region f_region(f_mapped, read_only);

	const char* buffer = (const char*)(f_region.get_address());
	const char* end = buffer + f_region.get_size();
	FILE* out = fopen("out_realbig.txt", "w");

	while (buffer != end) {

		++buffer;
		auto uno = range_to_bigint_without_copy<int101_t, 31>(buffer);

		buffer += 33; //31 + 2 (spaces)
		auto dos = range_to_bigint_without_copy<int101_t, 31>(buffer);
		buffer += 33; //31 + 2 (CRLF)

		auto resultado = static_cast<int201_t>(uno) * dos;
		//auto resultado = uno * dos;

		fprintf(out, "%s\n", resultado.str().c_str());
		//cout << "resultado: " << resultado << endl;
	}

	fclose(out);
}


void mult_files_big_buffer_with_copy() {

	//---------------------------------------------------------------------
	////int256_t x{ "256256" };

	////char buf[] = "256256256 2";
	////char buf[] = "0x256256";
	////char buf[] = "256 256";
	//char buf[] = "02562562562 123";

	//const char* bufptr = buf;

	////auto x = make_from_bounded_range<int256_t>(bufptr, bufptr + 10);
	//int256_t x;
	//tie(x, ignore) = make_from_bounded_range<int256_t>(bufptr, bufptr + 15);


	////auto y = make_from_counted_range<int256_t>(bufptr, 10);
	//int256_t y;
	//tie(y, ignore, ignore) = make_from_counted_range<int256_t>(bufptr, 15);


	////int256_t z{ "0x2 56256" };
	////int256_t z{ "256256256" };
	//int256_t z{ "02562562562" };

	////x *= 2;
	//cout << x << endl;
	//cout << y << endl;
	//cout << z << endl;
	//---------------------------------------------------------------------






	file_mapping f_mapped("D:\\src_realbig.txt", read_only);
	mapped_region f_region(f_mapped, read_only);

	const char* buffer = (const char*)(f_region.get_address());
	const char* end = buffer + f_region.get_size();
	FILE* out = fopen("out_realbig.txt", "w");

	while (buffer != end) {

		++buffer;
		auto uno = range_to_bigint_with_copy<int101_t, 31>(buffer);

		buffer += 33; //31 + 2 (spaces)
		auto dos = range_to_bigint_with_copy<int101_t, 31>(buffer);
		buffer += 33; //31 + 2 (CRLF)

					  //auto resultado = static_cast<int201_t>(uno) * dos;
		auto resultado = uno * dos;

		fprintf(out, "%s\n", resultado.str().c_str());
		//cout << "resultado: " << resultado << endl;
	}

	fclose(out);
}

#endif // COD_REALBIG_HPP_


