#ifndef MEASUREMENTS_HPP_
#define MEASUREMENTS_HPP_

#include <algorithm>	//for std::sort
#include <array>
#include <chrono>
#include <numeric>		//for std::accumulate

#include <iostream>		//REMOVE THIS


//Concepts emulation
#define Function typename

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

template <size_t NumTrials, Function F> 
double measure_void(F f) { 
	using namespace std; 
	using namespace std::chrono; 

	// static const int num_trials{10}; 
	static const milliseconds min_time_per_trial{200}; 

	std::array<double, NumTrials> trials; 

	for (size_t i{0}; i < NumTrials; ++i) { 
		high_resolution_clock::time_point measure_start = high_resolution_clock::now();
		f(); 
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

// Concepts emulation undef
#undef Function typename

#endif // MEASUREMENTS_HPP_


