#ifndef TOOLS_HPP_
#define TOOLS_HPP_


#include <iostream>
#include <numeric>
#include <random>

#define RandomEngine typename
#define Sequence typename
#define Container typename

using namespace std;


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

template <typename T, RandomEngine E>
vector<T> random_array_creator(size_t max, E & eng) {
	vector<T> array;
	array.reserve(max);

	// cout << "to: " << to << endl;

	for (size_t i{0}; i < max; ++i) {
		auto s = eng();
		array.emplace_back(s);
	}

	return array;
}


#undef RandomEngine
#undef Sequence
#undef Container

#endif // TOOLS_HPP_


