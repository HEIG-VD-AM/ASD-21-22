/*
 ----------------------------------------------------------------------------------
 Nom du fichier : benchmark_time.hpp

 Auteur(s)      : Rayane Annen, Hugo Ducommun, Alexis Martins

 Date creation  : 23.02.2022

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#ifndef BENCHMARK_TIME_HPP
#define BENCHMARK_TIME_HPP

#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>

#include "benchmark_info.hpp"
#include "check_info.hpp"
#include "generator.hpp"
#include "data_export.hpp"
#include "quick_sort.hpp"
#include "radix_sort.hpp"

template<typename T, typename Function>
std::chrono::duration<double, std::milli> measure_time_avg(Function fun,
														   size_t elements_count,
														   size_t iterations_count,
														   unsigned seed,
														   InputType input_type) {
	std::chrono::duration<double, std::milli> time_ms{};

	for (size_t i = 0; i < iterations_count; ++i) {
		auto v = vector_generator<T>(elements_count, seed, input_type);
		auto t1 = std::chrono::high_resolution_clock::now();
		fun(v.begin(), v.end());
		auto t2 = std::chrono::high_resolution_clock::now();
		time_ms += t2 - t1;
	}

	return time_ms / iterations_count;
}

template<typename T, typename Function>
void measure_exec_time(const BenchmarkInfo* const info,
					   Function fun(typename std::vector<T>::iterator,
									typename std::vector<T>::iterator)) {
	std::vector<std::vector<double>> results;
	std::vector<std::string> headers;
	std::vector<double> measures;
	const unsigned int ITERATIONS = 5;
	const unsigned int SEED = 0xdeadbeef;
	size_t measure_count = info->samples.size();
	std::cout << "Mesure de " << info->function_name << std::endl;

	for (size_t j = 0; j < info->samples.size(); ++j) {
		if (headers.size() <= measure_count) headers.push_back(std::to_string(info->samples[j]));
		auto measure = measure_time_avg<T>(fun, info->samples[j], ITERATIONS, SEED, info->input_type);
		measures.push_back(measure.count());
	}

	results.push_back(measures);

	export_csv(info->function_name + ".csv", headers, results);
}

void check_exec_time() {
	using T = unsigned int;
	using Iterator = std::vector<T>::iterator;
	const size_t SAMPLE_SIZE = 10000;
	const unsigned int SEED = 0xdeadbeef;
	auto type = InputType::SHUFFLE;

	const CheckInfo<T> function_info[] = {
			CheckInfo<T>{"radix", "base 16", type, SEED, 5, SAMPLE_SIZE},
			CheckInfo<T>{"quicksort", "", type, SEED, 5, SAMPLE_SIZE},
	};

	auto functions = {
			radix_sort<Iterator, 16>,
			quick_sort<Iterator>
	};

	std::cout << std::endl;
	std::cout << "Mesure du temps de d'execution" << std::endl;
	std::cout << "==============================" << std::endl;
	std::cout << "Taille de l'echantillon : " << SAMPLE_SIZE << std::endl;
	std::cout << "Graine : " << SEED << std::endl;

	for (size_t i = 0; i < functions.size(); ++i) {
		auto dt = measure_time_avg<T>(*(functions.begin() + i),
									  function_info[i].sample_size,
									  function_info[i].measure_count,
									  function_info[i].seed,
									  function_info[i].input_type);
		std::cout << "(" << function_info[i].function_name
				  << (function_info[i].info.empty() ? ") : " : " " + function_info[i].info + ") : ")
				  << dt.count() << " ms" << std::endl;
	}

}

void benchmark_time() {
	using T = unsigned int;
	using Iterator = std::vector<T>::iterator;
	const size_t
			MIN_SAMPLE_SIZE = 10,
			MAX_SAMPLE_SIZE = 1'000'000;
	auto type = InputType::SHUFFLE;
	std::vector<size_t> samples = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 1'000, 2'500, 5'000, 7'500, 10'000, 25'000,
								   50'000, 75'000, 100'000, 250'000, 500'000, 750'000, 1'000'000};
	const BenchmarkInfo function_info[] = {
			BenchmarkInfo{"radix16", type, MIN_SAMPLE_SIZE, MAX_SAMPLE_SIZE, samples},
			BenchmarkInfo{"radix8", type, MIN_SAMPLE_SIZE, MAX_SAMPLE_SIZE, samples},
			BenchmarkInfo{"radix4", type, MIN_SAMPLE_SIZE, MAX_SAMPLE_SIZE, samples},
			BenchmarkInfo{"radix2", type, MIN_SAMPLE_SIZE, MAX_SAMPLE_SIZE, samples},
			BenchmarkInfo{"radix1", type, MIN_SAMPLE_SIZE, MAX_SAMPLE_SIZE, samples},
			BenchmarkInfo{"quicksort", type, MIN_SAMPLE_SIZE, MAX_SAMPLE_SIZE, samples},
	};

	auto functions = {
			radix_sort<Iterator, 16>,
			radix_sort<Iterator, 8>,
			radix_sort<Iterator, 4>,
			radix_sort<Iterator, 2>,
			radix_sort<Iterator, 1>,
			quick_sort<Iterator>
	};

	std::cout <<
			  std::endl;
	std::cout << "Mesure et enregistrement du temps d'execution des algorithmes" <<
			  std::endl;
	std::cout << "============================================================="
			  << std::endl <<
			  std::endl;
	std::cout << "Taille minimum d'echantillon : " << MIN_SAMPLE_SIZE <<
			  std::endl;
	std::cout << "Taille maximum d'echantillon : " << MAX_SAMPLE_SIZE <<
			  std::endl;
	for (size_t i = 0; i < functions.size(); ++i)
		measure_exec_time<T>(&function_info[i], *(functions.begin() + i));

	std::cout << "Mesures effectuees et enregistrees en format csv." <<
			  std::endl;

}

#endif // BENCHMARK_TIME_HPP