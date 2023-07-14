/*
 ----------------------------------------------------------------------------------
 Nom du fichier : check_sort.hpp

 Auteur(s)      : Rayane Annen, Hugo Ducommun, Alexis Martins

 Date creation  : 23.02.2022

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#ifndef CHECK_SORT_HPP
#define CHECK_SORT_HPP

#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
#include <typeinfo>
#include <algorithm>
#include <string>

#include "generator.hpp"
#include "check_info.hpp"
#include "radix_sort.hpp"
#include "quick_sort.hpp"

/**
 *
 * @tparam T
 * @tparam Function
 * @param check_info
 * @param fun
 * @param show_array
 */
template <typename T, typename Function>
void check_algorithm(const CheckInfo<T> *check_info, Function fun,
							bool show_array = false) {
	auto join = [](const auto& a, auto b) -> std::string {
		return a + (a.length() > 0 ? "," : "") + std::to_string(b);
	};

	auto v = vector_generator<T>(check_info->sample_size,
										  check_info->seed,
										  check_info->input_type);
	if (show_array) {
		std::cout << "(" << check_info->function_name << ")"
					 << " Avant le tri: [";
		std::cout << std::accumulate(v.begin(), v.end(), std::string(), join);
		std::cout << "]" << std::endl;
	}

	fun(v.begin(), v.end());
	std::cout << "(" << check_info->function_name
				 << (check_info->info.empty() ? ") " : " " + check_info->info + ") ")
				 << (std::is_sorted(v.begin(), v.end()) ? "VALIDE" : "INVALIDE")
				 << std::endl;

	if (show_array) {
		std::cout << "(" << check_info->function_name << ")"
					 << " Apres le tri: [";
		std::cout << std::accumulate(v.begin(), v.end(), std::string(), join);
		std::cout << "]" << std::endl;
	}


}

bool check_partition(unsigned vector_size, unsigned seed) {
	using T = unsigned int;
	auto v = vector_generator<T>(vector_size, seed, InputType::SHUFFLE);
	auto pivot = partition(v.begin(), v.end());

	for (auto i = v.begin(), j = v.end() - 1;
		  std::distance(i, pivot) > 0 || std::distance(pivot, j) > 0;
		  i++, j--) {
		if ((std::distance(i, pivot) > 0 && *i > *pivot) ||
			 (std::distance(pivot, j) > 0 && *j < *pivot)) {
			return false;
		}
	}

	return true;
}

void check_sort_algorithms() {
	using T = unsigned int;
	using Iterator = std::vector<T>::iterator;
	const unsigned SEED = 0xdeadbeef;
	const unsigned MEASURE_COUNT = 100;
	const unsigned SAMPLE_SIZE = 1000;
	auto type = InputType::SHUFFLE;

	const CheckInfo<T> function_info[] = {
		CheckInfo<T>{"radix", "base 16", type, SEED, MEASURE_COUNT, SAMPLE_SIZE},
		CheckInfo<T>{"quicksort", "", type, SEED, MEASURE_COUNT, SAMPLE_SIZE},
	};

	auto functions = {
		radix_sort<Iterator, 16>,
		quick_sort<Iterator>
	};

	std::cout << "Verifications des tris" << std::endl;
	std::cout << "======================" << std::endl << std::endl;
	for (size_t i = 0; i < functions.size(); ++i)
		check_algorithm<T>(&function_info[i], *(functions.begin() + i), false);
	{
		auto v = vector_generator<T>(SAMPLE_SIZE, SEED, type);
		std::vector<T> res(SAMPLE_SIZE);
		const size_t BASE = 8;
		counting_sort(v.begin(), v.end(), res.begin(), SomeBits<T>(8, 0), 1 << BASE);
		std::transform(res.begin(), res.end(), res.begin(), SomeBits<T>(BASE, 0));
		std::cout << "(counting sort base 8) "
					 << (std::is_sorted(res.begin(), res.end()) ? "VALIDE" : "INVALIDE")
					 << std::endl;
	}
	std::cout << std::endl << "Verifications de la partition" << std::endl;
	std::cout << "=============================" << std::endl << std::endl;
	std::cout << "Algorithme de partitionnement : ";
	std::cout << (check_partition(SAMPLE_SIZE, SEED) ? "VALIDE" : "INVALIDE")
				 << std::endl;
}

#endif // CHECK_SORT_HPP