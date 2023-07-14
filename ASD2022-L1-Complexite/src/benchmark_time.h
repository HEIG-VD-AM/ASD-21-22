/*
 ----------------------------------------------------------------------------------
 Nom du fichier : benchmark_time.h

 Auteur(s)      : Hugo Ducommun,
                  Rayane Annen,
                  Alexis Martins

 Date creation  : 23.02.2022

 Description    : -

 Remarque(s)    : -

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#ifndef BENCHMARK_TIME_H
#define BENCHMARK_TIME_H

#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>

#include "sort_algorithms.h"
#include "generator.h"
#include "data_export.h"

const unsigned SEED_BENCHMARK_TIME = 1337;

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
void measure_input_types_exec_time(Function f(typename std::vector<T>::iterator,
															 typename std::vector<T>::iterator),
											  size_t measure_count,
											  size_t max_elements_count,
											  const std::string &filename) {
	std::vector<std::vector<double>> results;
	std::vector<std::string> headers;

	for (size_t i = 0; i < 4; ++i) {
		std::vector<double> measures;
		for (size_t j = max_elements_count / measure_count; j <= max_elements_count; j += max_elements_count / measure_count) {
			if (headers.size() <= measure_count - 1)
				headers.push_back(std::to_string(j));
			auto measure = measure_time_avg<T>(f, j, 10, SEED_BENCHMARK_TIME,
														  (InputType) i);
			measures.push_back(measure.count());
		}
		results.push_back(measures);
	}

	export_csv(filename, headers, results);
}

template<typename T>
void test_4_sorts_time(T f(std::vector<int>::iterator, std::vector<int>::iterator),
							  size_t input_size) {
	std::cout << "Ascendant : "
				 << measure_time_avg<int>(f, input_size, 10, SEED_BENCHMARK_TIME,
												  InputType::ASCENDING).count()
				 << " ms" << std::endl;

	std::cout << "Descendant : "
				 << measure_time_avg<int>(f, input_size, 10, SEED_BENCHMARK_TIME,
												  InputType::DESCENDING).count()
				 << " ms" << std::endl;

	std::cout << "Non-ordonne : "
				 << measure_time_avg<int>(f, input_size, 10, SEED_BENCHMARK_TIME,
												  InputType::SHUFFLE).count()
				 << " ms" << std::endl;

	std::cout << "Partiellement ordonne : "
				 << measure_time_avg<int>(f, input_size, 10, SEED_BENCHMARK_TIME,
												  InputType::PARTIAL_SORT).count()
				 << " ms" << std::endl;
}

void benchmark_time() {
	using Iterator = std::vector<int>::iterator;

	size_t input_size = 10;
	for (size_t i = 1; i <= 10; i++) {
		std::cout << std::endl << "Nombres d'entrees dans le vecteur : "
					 << input_size
					 << " entrees";

		std::cout << std::endl << "Tri a bulles : " << std::endl;
		test_4_sorts_time(bubble_sort<Iterator>, input_size);

		std::cout << std::endl << "Tri par insertion : " << std::endl;
		test_4_sorts_time(insert_sort<Iterator>, input_size);

		std::cout << std::endl << "Tri par selection : " << std::endl;
		test_4_sorts_time(selection_sort<Iterator>, input_size);

		std::cout << std::endl << "Tri std::sort : " << std::endl;
		test_4_sorts_time(std::sort<Iterator>, input_size);

		std::cout << std::endl << "Tri std::stable_sort : " << std::endl;
		test_4_sorts_time(std::stable_sort<Iterator>, input_size);

		input_size += 10;
	}

	std::cout << std::endl;
	std::cout << "Mesure du temps d'execution et enregistrements des donnees en format csv en cours."
				 << std::endl;

	measure_input_types_exec_time<int>(bubble_sort<Iterator>, 5, 25000,
												  "time_bubble_sort.csv");
	measure_input_types_exec_time<int>(insert_sort<Iterator>, 5, 25000,
												  "time_insert_sort.csv");
	measure_input_types_exec_time<int>(selection_sort<Iterator>, 5, 25000,
												  "time_selection_sort.csv");
	measure_input_types_exec_time<int>(std::stable_sort<Iterator>, 5, 25000,
												  "time_stable_sort.csv");
	measure_input_types_exec_time<int>(std::sort<Iterator>, 5, 25000,
												  "time_sort.csv");

	std::cout << "Mesures effectuees et enregistrees." << std::endl;

}

#endif // BENCHMARK_TIME_H
