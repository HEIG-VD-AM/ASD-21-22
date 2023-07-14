/*
 ----------------------------------------------------------------------------------
 Nom du fichier : benchmark_counter.h

 Auteur(s)      : Hugo Ducommun,
                  Rayane Annen,
                  Alexis Martins

 Date creation  : 23.02.2022

 Description    : -

 Remarque(s)    : -

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#ifndef BENCHMARK_COUNTER_H
#define BENCHMARK_COUNTER_H

#include <vector>
#include <iostream>
#include <algorithm>

#include "sort_algorithms.h"
#include "generator.h"
#include "op_counter.h"

const unsigned SEED_BENCHMARK_COUNTER = 1337;

template<typename T, typename Function>
std::array<size_t, 2> measure_ops(Function fun, size_t elements_count,
								  unsigned seed,
								  InputType input_type) {
	std::array<size_t, 2> results{};
	auto v = vector_generator<T>(elements_count, seed, input_type);
	T::reset_static_parameters();
	fun(v.begin(), v.end());
	results[0] = T::get_comparison_count();
	results[1] = T::get_affectation_count();
	return results;
}

template<typename T, typename Function>
void measure_input_types_ops(Function f(typename std::vector<T>::iterator,
										typename std::vector<T>::iterator),
							 size_t measure_count,
							 size_t max_elements_count,
							 const std::string& func_name) {

	std::vector<std::vector<size_t>> results_affectations;
	std::vector<std::vector<size_t>> results_comparisons;
	std::vector<std::string> headers;

	for (size_t i = 0; i < 4; ++i) {
		std::vector<size_t> measures_affectations;
		std::vector<size_t> measure_comparisons;
		for (size_t j = max_elements_count / measure_count; j <= max_elements_count; j += max_elements_count / measure_count) {
			if (headers.size() <= measure_count - 1)
				headers.push_back(std::to_string(j));
			auto measure = measure_ops<T>(f, j, 1337,
										  (InputType) i);
			measure_comparisons.push_back(measure[0]);
			measures_affectations.push_back(measure[1]);
		}
		results_affectations.push_back(measures_affectations);
		results_comparisons.push_back(measure_comparisons);
	}

	export_csv(func_name + "_affectations.csv", headers, results_affectations);
	export_csv(func_name + "_comparisons.csv", headers, results_comparisons);

}

template<typename T>
void test_4_sorts_counter(T f(std::vector<OpCounter<int>>::iterator,
							  std::vector<OpCounter<int>>::iterator),
						  size_t input_size) {
	std::vector<OpCounter<int>> v = vector_generator<OpCounter<int>>(input_size,
																	 SEED_BENCHMARK_COUNTER,
																	 InputType::ASCENDING);
	f(v.begin(), v.end());
	std::cout << "Ascendant - Nbr affectations : "
			  << OpCounter<int>::get_affectation_count()
			  << ", Nbr comparaisons : "
			  << OpCounter<int>::get_comparison_count() << std::endl;
	OpCounter<int>::reset_static_parameters();

	v = vector_generator<OpCounter<int>>(input_size, SEED_BENCHMARK_COUNTER,
										 InputType::DESCENDING);
	f(v.begin(), v.end());
	std::cout << "Descendant - Nbr affectations : "
			  << OpCounter<int>::get_affectation_count()
			  << ", Nbr comparaisons : "
			  << OpCounter<int>::get_comparison_count() << std::endl;
	OpCounter<int>::reset_static_parameters();

	v = vector_generator<OpCounter<int>>(input_size, SEED_BENCHMARK_COUNTER,
										 InputType::SHUFFLE);
	f(v.begin(), v.end());
	std::cout << "Non ordonne - Nbr affectations : "
			  << OpCounter<int>::get_affectation_count()
			  << ", Nbr comparaisons : "
			  << OpCounter<int>::get_comparison_count() << std::endl;
	OpCounter<int>::reset_static_parameters();

	v = vector_generator<OpCounter<int>>(input_size, SEED_BENCHMARK_COUNTER,
										 InputType::PARTIAL_SORT);
	f(v.begin(), v.end());
	std::cout << "Presque ordonne - Nbr affectations : "
			  << OpCounter<int>::get_affectation_count()
			  << ", Nbr comparaisons : "
			  << OpCounter<int>::get_comparison_count() << std::endl;
	OpCounter<int>::reset_static_parameters();
}

void benchmark_counter() {
	using Iterator = std::vector<OpCounter<int>>::iterator;
	size_t input_size = 10;

	for (size_t i = 1; i <= 10; i++) {
		std::cout << std::endl << "Nombres d'entrees dans le vecteur : " << input_size
				  << " entrees";

		std::cout << std::endl << "Tri a bulles : " << std::endl;
		test_4_sorts_counter(bubble_sort<Iterator>,
							 input_size);

		std::cout << std::endl << "Tri par insertion : " << std::endl;
		test_4_sorts_counter(insert_sort<Iterator>,
							 input_size);

		std::cout << std::endl << "Tri par selection : " << std::endl;
		test_4_sorts_counter(selection_sort<Iterator>,
							 input_size);

		std::cout << std::endl << "Tri std::sort : " << std::endl;
		test_4_sorts_counter(std::sort<Iterator>,
							 input_size);

		std::cout << std::endl << "Tri std::stable_sort : " << std::endl;
		test_4_sorts_counter(std::stable_sort<Iterator>,
							 input_size);

		input_size += 10;
	}


	std::cout << std::endl;
	std::cout << "Mesure du nombre d'operations et enregistrements des donnees en format csv en cours."
			  << std::endl;

	measure_input_types_ops<OpCounter<int>>(bubble_sort<Iterator>, 5, 25000, "bubble_sort");
	measure_input_types_ops<OpCounter<int>>(insert_sort<Iterator>, 5, 25000, "insert_sort");
	measure_input_types_ops<OpCounter<int>>(selection_sort<Iterator>, 5, 25000, "selection_sort");
	measure_input_types_ops<OpCounter<int>>(std::stable_sort<Iterator>, 5, 25000, "stable_sort");
	measure_input_types_ops<OpCounter<int>>(std::sort<Iterator>, 5, 25000, "sort");

	std::cout << "Mesures effectuees et enregistrees." << std::endl;

}

#endif // BENCHMARK_COUNTER_H
