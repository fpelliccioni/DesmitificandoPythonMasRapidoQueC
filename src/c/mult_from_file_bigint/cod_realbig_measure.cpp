
// Clang: clang++ -O3 -std=c++1y cod_masreal_measure.cpp
// GCC:   g++ -Wall -Wextra -pedantic -O3 -std=c++1y cod_masreal_measure.cpp
// MSVC:  

#include "../measurements.hpp"
#include "cod_realbig.hpp"
#include <iostream>
#include <numeric>
#include <random>
//#include "boost/random.hpp"
//#include "boost/random/random_device.hpp"
//#include <boost/random/random_number_generator.hpp>

//using namespace std;


//-----------------------------------------------------------------------

//int main(int /*argc*/, char const * /*argv*/[]) {
//
//	cout.precision(25);
//
//	//std::vector<real_type> data {1.0, 2.0, 3.0, 4.0, 8.0, 17.0};
//
//	std::vector<real_type> data;// {1.0, 2.0, 3.0, 4.0, 8.0, 17.0};
//	for (size_t i = 0; i < 1000000; i++) {
//		data.push_back(i * 55);
//	}
//
//	//std::vector<real_type> data {10000, 10001, 10002};
//	//std::vector<real_type> data{ 1.4592859018312442e+63, 1.4592859018312442e+63, 1.4592859018312442e+63 };
//
//	
//
//
//	auto pv1 = population_variance(data);
//	auto sv1 = sample_variance(data);
//	//auto pv2 = population_variance_2(data);
//
//
//	cout << pv1 << endl;
//	cout << sv1 << endl;
//
//	//cout << pv2 << endl;
//	//cout << (pv1 == pv2) << endl;
//	//cout << (pv1 - pv2) << endl;
//
//
//	//cout << population_variance_2(data) << endl;
//	//cout << sample_variance(data) << endl;
//	//cout << sample_variance_2(data) << endl;
//
//	cin.get();
//}

//-----------------------------------------------------------------------


#define RandomEngine typename
#define Sequence typename
#define Container typename


template <unsigned int From, unsigned int To>
struct random_int_generator {
	using dis_t = uniform_int_distribution<>;
	static constexpr unsigned int from = From;
	static constexpr unsigned int to = To;

	random_int_generator()
		: mt{ rd() }
		, dis{ from, to }  // closed range [1, 1000]		
	{}

	random_int_generator(random_int_generator const&) = default;

	auto operator()() {
		return dis(mt);
	}

	random_device rd;
	mt19937 mt;
	dis_t dis;
}; // Models: RandomIntGenerator


template <typename BigIntType>
struct random_bigint_generator {
	using dis_t = uniform_int_distribution<>;

	//static constexpr unsigned int from = From;
	//static constexpr unsigned int to = To;

	random_bigint_generator()
		: mt{ rd() }
		, dis{}
	{}

	random_bigint_generator(random_bigint_generator const&) = default;

	auto operator()() {

		auto x1 = BigIntType(dis(mt));
		auto x2 = BigIntType(dis(mt)) << 32;
		auto x3 = BigIntType(dis(mt)) << 64;
		auto x4 = BigIntType(dis(mt)) << 96;
		auto x5 = BigIntType(dis(mt)) << 128;
		auto x6 = BigIntType(dis(mt)) << 160;
		auto x7 = BigIntType(dis(mt)) << 192;
		auto x8 = BigIntType(dis(mt)) << 224;

		auto res = x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8;

		//cout << x1 << endl;
		//cout << x2 << endl;
		//cout << x3 << endl;
		//cout << x4 << endl;
		//cout << x5 << endl;
		//cout << x6 << endl;
		//cout << x7 << endl;
		//cout << x8 << endl;
		//cout << res << endl;

		return res;
	}

	random_device rd;
	mt19937 mt;
	dis_t dis;
}; // Models: RandomIntGenerator


template <typename IntGen>
struct random_pair_generator {

	random_pair_generator(IntGen& gen)
		: gen{ gen }
	{}

	random_pair_generator(random_pair_generator const&) = default;

	auto operator()() {
		return make_pair(gen(), gen());
	}

	IntGen& gen;
};


//
//std::vector<std::pair<int_type, int_type>> load_from_file() {
//
//	std::vector<std::pair<int_type, int_type>> res;
//	res.reserve(1'000'000);
//
//	file_mapping f_mapped("D:\\src_realbig.txt", read_only);
//	mapped_region f_region(f_mapped, read_only);
//
//	const char* buffer = (const char*)(f_region.get_address());
//	const char* end = buffer + f_region.get_size();
//
//	while (buffer != end) {
//
//		++buffer;
//		auto uno = range_to_bigint_without_copy<int_type, 31>(buffer);
//
//		buffer += 33; //31 + 2 (spaces)
//		auto dos = range_to_bigint_without_copy<int_type, 31>(buffer);
//		buffer += 33; //31 + 2 (CRLF)
//
//		res.emplace_back(uno, dos);
//	}
//	return res;
//}



template <typename T, RandomEngine E>
vector<T> random_array_creator(size_t max, E & eng) {
	vector<T> array;
	array.reserve(max);

	// cout << "to: " << to << endl;

	for (int i = 0; i < max; ++i) {
		auto s = eng();
		array.emplace_back(s);
	}

	return array;
}

template <typename IntMax, typename IntMin>
void measure_and_print_mult_big_vector_hot(vector<pair<IntMin, IntMin>> const& data) {
	std::vector<IntMax> output;
	output.reserve(data.size());

	auto p = measure_v2<1000>(
		[&]() { output.clear(); },
		[&]() {return mult_big_vector_hot(data, output); });

	cout << "mult_big_vector_hot                    ;" << data.size() << ";" << p.first << ";" << p.second << endl;
}

template <typename IntMax, typename IntMin>
void measure_and_print_mult_big_vector_no_out_hot(vector<pair<IntMax, IntMin>>& data) {
	auto p = measure_v2<1000>(
		[]() {},
		[&]() {return mult_big_vector_no_out_hot(data); });

	cout << "mult_big_vector_no_out_hot             ;" << data.size() << ";" << p.first << ";" << p.second << endl;
}

template <typename IntMin>
void measure_and_print_mult_big_vector_do_nothing_hot(vector<pair<IntMin, IntMin>> const& data) {
	auto p = measure_v2<1000>(
		[]() {},
		[&]() {return mult_big_vector_do_nothing_hot(data); });

	cout << "mult_big_vector_do_nothing_hot         ;" << data.size() << ";" << p.first << ";" << p.second << endl;
}


//void measure_and_print_mult_big_vector_do_nothing_IntMax_hot(vector<pair<IntMax, IntMin>> const& data) {
//	auto p = measure_v2<1000>(
//		[]() {},
//		[&]() {return mult_big_vector_do_nothing_IntMax_hot(data); });
//
//	cout << "mult_big_vector_do_nothing_IntMax_hot;" << data.size() << ";" << p.first << ";" << p.second << endl;
//}

#define VectorOfPairOfIntegers typename

template <VectorOfPairOfIntegers V>
using SecondType = typename V::value_type::second_type;

template <VectorOfPairOfIntegers V>
vector<pair<SecondType<V>, SecondType<V>>> copy_convert_vector(V const& vec) {
	vector<pair<SecondType<V>, SecondType<V>>> res;
	res.reserve(vec.size());

	for (auto& x : vec) {
		res.emplace_back(SecondType<V>(x.first), x.second);
	}

	return res;
}

template <typename IntMax, typename IntMin>
void run_mearurements(size_t min_size, size_t max_size) {
	using random_big = random_bigint_generator<int32_t>;
	random_big eng;
	random_pair_generator<random_big> pair_eng(eng);

	size_t array_size = min_size;
	while (array_size <= max_size) {
		auto data1 = random_array_creator<pair<int64_t, int32_t>>(array_size, pair_eng);
		auto data2 = copy_convert_vector(data1);

		//measure_and_print_mult_big_vector_do_nothing_hot(data2);
		measure_and_print_mult_big_vector_hot<IntMax>(data2);
		measure_and_print_mult_big_vector_no_out_hot(data1);

		cout << "-------------------------" << endl;

		array_size *= 2;
	}
}

int main(int /*argc*/, char const * /*argv*/[]) {

	//std::cout <<
	//	measure_void<1>([]() {
	//	mult_files_big_buffer_with_copy();
	//}) << ";";


	//std::cout <<
	//	measure_void<1>([]() {
	//	mult_files_big_buffer_without_copy();
	//}) << ";";

	//std::cout <<
	//	measure_void<1>([]() {
	//		mult_files_big_buffer_without_copy_mm();
	//}) << ";";

	


	//-----------------------------------------------------------------------
	cout.precision(30);
	std::cout << "starting..." << endl;

	//size_t min_size = 8;
	size_t min_size = 16 * 1024;
	size_t max_size = 8 * 1024 * 1024;
	//size_t max_size = 16 * 1024 * 1024;		// Out of memory for mult_big_vector_hot

	cout << "Types int64_t and int32_t ---------------------------------------\n";
	run_mearurements<int64_t, int32_t>(min_size, max_size);
	cout << "Types int201_t and int101_t ---------------------------------------\n";
	run_mearurements<int201_t, int101_t>(min_size, max_size);

	cin.get();
	return 0;
}

//-----------------------------------------------------------------------


//int main(int /*argc*/, char const * /*argv*/[]) {
//
//	char buff[] = "12345 67890";
//	auto a = make_from_bounded_range<int128_t>(buff, buff + 5);
//	auto b = make_from_counted_range<int128_t>(buff, 5);
//
//	auto c = make_from_bounded_range<int128_t>(buff + 6, buff + 6 + 5);
//	auto d = make_from_counted_range<int128_t>(buff + 6, 5);
//
//
//	cout << get<0>(a) << '\n'
//		<< get<0>(b) << '\n'
//		<< get<0>(c) << '\n'
//		<< get<0>(d) << '\n';
//
//	cin.get();
//
//	/*
//	12345
//	12345
//	67890
//	67890
//	*/
//
//
//}