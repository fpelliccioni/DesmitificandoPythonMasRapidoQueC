#ifndef MEASUREMENTS_HPP_
#define MEASUREMENTS_HPP_

#include <algorithm>	//for std::sort
#include <array>
#include <chrono>
#include <numeric>		//for std::accumulate
#include <vector>

#include <iostream>		//REMOVE THIS


//Concepts emulation
#define Function typename



using real_type = double;
//using real_type = float;

template <typename I>
real_type mean_n(I f, size_t n) {
	auto sum = std::accumulate(f, f + n, real_type(0));
	return sum / n;
}

template <typename I>
real_type variance_helper_n(I f, size_t n) {
	auto m = mean_n(f, n);
	real_type s = 0;
	std::for_each(f, f + n, [&s, m](real_type x) { s += (x - m) * (x - m); });

	return s;
}


//real_type variance_helper_2(std::vector<real_type> const& data) {
//	real_type sum = 0;
//	real_type sum_sqr = 0;
//	size_t n = 0;
//	auto K = data[0];
//
//	std::for_each(begin(data), end(data), [K, &n, &sum, &sum_sqr](real_type x) {
//		sum += x - K;
//		sum_sqr += (x - K) * (x - K);
//		++n;
//	});
//
//	real_type v = (sum_sqr - (sum * sum) / n);
//	return v;
//}


/*
Sum(i, n) (Xi - X)^2
Sum(i, n) (Xi - (Sum(i, n) Xi) / n) ^ 2
*/

template <typename I>
real_type population_variance_n(I f, size_t n) {
	auto s = variance_helper_n(f, n);
	return s / n;
}

//real_type sample_variance(std::vector<real_type> const& data) {
//	auto s = variance_helper(data);
//	return s / (data.size() - 1);
//}

template <typename I>
real_type sample_variance_n(I f, size_t n) {
	auto s = variance_helper_n(f, n);
	return s / (n - 1);
}

template <typename I>
real_type sample_std_dev_n(I f, size_t n) {
	auto s2 = sample_variance_n(f, n);
	return std::sqrt(s2);
}


//real_type population_variance_2(std::vector<real_type> const& data) {
//	auto s = variance_helper_2(data);
//	return s / data.size();
//}
//
//real_type sample_variance_2(std::vector<real_type> const& data) {
//	auto s = variance_helper_2(data);
//	return s / (data.size() - 1);
//}


double combine_std_dev_1(int n1, double u1, double s1, int n2, double u2, double s2) {

	auto t1 = n1 * n1 * s1 * s1;
	auto t2 = n2 * n2 * s2 * s2;
	auto t3 = n2      * s1 * s1;
	auto t4 = n2      * s2 * s2;
	auto t5 = n1      * s1 * s1;
	auto t6 = n1      * s2 * s2;

	auto t7 = n1 * n2 * s1 * s1;
	auto t8 = n1 * n2 * s2 * s2;

	auto t9 = n1 * n2 * (u1 - u2) * (u1 - u2);

	auto num = t1 + t2 - t3 - t4 - t5 - t6 + t7 + t8 + t9;
	auto den = (n1 + n2 - 1) * (n1 + n2);

	auto res = std::sqrt(num / den);
	return res;
}

double combine_std_dev_2(int n1, double u1, double s1, int n2, double u2, double s2) {

	auto uc = (n1 * u1 + n2 * u2) / (n1 + n2);

	auto t1 = (n1 - 1) * s1 * s1;
	auto t2 = n1 * u1 * u1;

	auto t3 = (n2 - 1) * s2 * s2;
	auto t4 = n2 * u2 * u2;
	
	auto t5 = (n1 + n2) * uc * uc;


	auto num = t1 + t2 + t3 + t4 - t5;
	auto den = n1 + n2 - 1;

	auto res = std::sqrt(num / den);
	return res;
}


template <size_t NumTrials, Function F> 
double measure_min(F f) { 
	using namespace std; 
	using namespace std::chrono; 

	// static const int num_trials{10}; 
	static const milliseconds min_time_per_trial{200}; 

	std::array<double, NumTrials> trials; 
	volatile decltype(f()) res; // to avoid optimizing f() away 

	for (size_t i{0}; i < NumTrials; ++i) { 
		
		size_t runs {0}; 
		high_resolution_clock::time_point t2; 
		high_resolution_clock::time_point measure_start = high_resolution_clock::now();

		do { 
			res = f(); 
			++runs; 
			t2 = high_resolution_clock::now(); 
		} while (t2 - measure_start < min_time_per_trial); 

		trials[i] = duration_cast<duration<double>>(t2 - measure_start).count() / runs; 
	} 

	(void)(res); // var not used warn 

	sort(begin(trials), end(trials)); 
	return accumulate(begin(trials) + 2, end(trials) - 2, 0.0) / (trials.size() - 4) * 1E6; 
}

template <size_t NumTrials, Function F> 
double measure_min_void(F f) { 
	using namespace std; 
	using namespace std::chrono; 

	// static const int num_trials{10}; 
	static const milliseconds min_time_per_trial{200}; 

	std::array<double, NumTrials> trials; 

	for (size_t i{0}; i < NumTrials; ++i) { 
		
		size_t runs {0}; 
		high_resolution_clock::time_point t2; 
		high_resolution_clock::time_point measure_start = high_resolution_clock::now();

		do { 
			f(); 
			++runs; 
			t2 = high_resolution_clock::now(); 
		} while (t2 - measure_start < min_time_per_trial); 

		// cout << "runs: " << runs << endl;
		// auto ns = duration_cast<nanoseconds>(t2 - measure_start).count(); 
		// auto x1 = duration_cast<nanoseconds>(t2 - measure_start).count() / runs; 
		// auto x2 = duration_cast<duration<double>>(t2 - measure_start).count() / runs; 
		// cout << "ns: " << ns << endl;
		// cout << "x1: " << x1 << endl;
		// cout << "x2: " << x2 << endl;


		trials[i] = duration_cast<duration<double>>(t2 - measure_start).count() / runs; 
	} 

	sort(begin(trials), end(trials)); 

	auto n = distance(begin(trials) + size_t(NumTrials * 0.2), end(trials) - size_t(NumTrials * 0.2));
	//cout << "distance: " << n << endl;


	// auto a = accumulate(begin(trials) + size_t(NumTrials * 0.2), end(trials) - size_t(NumTrials * 0.2), 0.0);
	// cout << "1E6: " << 1E6 << endl;
	// cout << "a: " << a << endl;
	// cout << "a / (NumTrials * 0.6): " << (a / (NumTrials * 0.6)) << endl;
	// cout << "a / (NumTrials * 0.6) * 1E6: " << (a / (NumTrials * 0.6) * 1E6) << endl;

	return accumulate(begin(trials) + size_t(NumTrials * 0.2), end(trials) - size_t(NumTrials * 0.2), 0.0) / n * 1E6; 
	// return accumulate(begin(trials) + size_t(NumTrials * 0.2), end(trials) - size_t(NumTrials * 0.2), 0.0) / (NumTrials * 0.6) * 1E6; 
	// return accumulate(begin(trials) + 2, end(trials) - 2, 0.0) / (trials.size() - 4) * 1E6; 


}

template <size_t NumTrials, Function F1, Function F2> 
double measure_void_v1(F1 setUp, F2 test) { 
	using namespace std; 
	using namespace std::chrono; 

	// static const int num_trials{10}; 
	static const milliseconds min_time_per_trial{200}; 

	std::array<double, NumTrials> trials; 

	for (size_t i{0}; i < NumTrials; ++i) { 
		setUp();
		high_resolution_clock::time_point measure_start = high_resolution_clock::now();
		test(); 
		high_resolution_clock::time_point t2 = high_resolution_clock::now(); 

		// auto ns = duration_cast<nanoseconds>(t2 - measure_start).count(); 
		// auto x2 = duration_cast<duration<double>>(t2 - measure_start).count(); 

		// cout << "ns: " << ns << endl;
		// cout << "x2: " << x2 << endl;

		trials[i] = duration_cast<duration<double>>(t2 - measure_start).count(); 
	} 

	// cout << "SORTING..." << endl;
	//for_each(begin(trials), end(trials), [](double x) { cout << "trial: " << x << endl;}); 

	sort(begin(trials), end(trials)); 

	auto n = distance(begin(trials) + size_t(NumTrials * 0.2), end(trials) - size_t(NumTrials * 0.2));
	//cout << "distance: " << n << endl;


	// auto a = accumulate(begin(trials) + size_t(NumTrials * 0.2), end(trials) - size_t(NumTrials * 0.2), 0.0);
	// cout << "1E6: " << 1E6 << endl;
	// cout << "a: " << a << endl;
	// cout << "a / (NumTrials * 0.6): " << (a / (NumTrials * 0.6)) << endl;
	// cout << "a / (NumTrials * 0.6) * 1E6: " << (a / (NumTrials * 0.6) * 1E6) << endl;

	return accumulate(begin(trials) + size_t(NumTrials * 0.2), end(trials) - size_t(NumTrials * 0.2), 0.0) / n * 1E6; 
	// return accumulate(begin(trials) + size_t(NumTrials * 0.2), end(trials) - size_t(NumTrials * 0.2), 0.0) / (NumTrials * 0.6) * 1E6; 
	// return accumulate(begin(trials) + 2, end(trials) - 2, 0.0) / (trials.size() - 4) * 1E6; 


}


template <size_t NumTrials, Function F1, Function F2>
std::pair<double, double> measure_v2(F1 setUp, F2 test) {
	using namespace std;
	using namespace std::chrono;

	// static const int num_trials{10}; 
	//static const milliseconds min_time_per_trial {200};

	constexpr size_t NumConcreteTrials = NumTrials * 0.8;

	//std::array<double, NumConcreteTrials> trials;
	std::array<int64_t, NumConcreteTrials> trials;

	for (size_t i{0}; i < size_t(NumTrials * 0.2); ++i) {
		setUp();
		test();
	}

	for (size_t i{0}; i < NumConcreteTrials; ++i) {
		setUp();
		auto ns = test();
		trials[i] = ns;
	}

	auto ssd = sample_std_dev_n(begin(trials), trials.size());

	//cout << "sample standard deviation " << ssd << endl;
	//cout << "trials.size() " << trials.size() << endl;
	//cout << "NumConcreteTrials " << NumConcreteTrials << endl;

	double mean = accumulate(begin(trials), end(trials), 0.0) / NumConcreteTrials;

	// mean-median test
	//sort(begin(trials), end(trials));
	//double median = trials[NumConcreteTrials / 2];
	//auto mmtest = std::abs(mean - median) / max(mean, median);
	//cout << "mean: " << mean << " - median: " << median << " - mean-median test: " << mmtest << endl;

	return {mean, ssd};
}



// Concepts emulation undef
#undef Function typename


#endif // MEASUREMENTS_HPP_


