/*
 ----------------------------------------------------------------------------------
 Nom du fichier : radix_sort.hpp

 Auteur(s)      : Rayane Annen, Hugo Ducommun, Alexis Martins

 Date creation  : 20.03.2022

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#ifndef RADIX_SORT_HPP
#define RADIX_SORT_HPP

#include <cstdlib>
#include <iterator>
#include <type_traits>
#include <vector>
#include <limits>
#include <numeric>
#include "some_bits.hpp"

/**
 * Trie un tableau par comptage
 * @tparam Iterator
 * @tparam Function
 * @param first
 * @param last
 * @param output_first Tableau trié
 * @param index_fn Fonction "clé" pour déterminer la valeur de l'élément
 * @param N Nombre de valeurs possible
 */
template<typename Iterator, typename Function>
void counting_sort(Iterator first, Iterator last, Iterator output_first, Function
index_fn, std::size_t N) {
	std::vector<std::size_t> counters(N, 0);
	for (Iterator it = first; it != last; ++it) {
		auto key = static_cast<std::size_t>(index_fn(*it));
		counters[key] += 1;
	}
	std::size_t index = 0;

	for (std::size_t i = 0; i < N; ++i) {
		auto tmp = static_cast<std::size_t>(counters[i]);
		counters[i] = index;
		index += tmp;
	}

	for (Iterator it = first; it != last; ++it) {
		using T = typename Iterator::difference_type;
		auto key = static_cast<std::size_t>(index_fn(*it));
		auto counter_key = static_cast<std::size_t>(counters[key]);
		*(output_first + static_cast<T>(counter_key)) = *it;
		counters[key] += 1;
	}
}

/**
 * Trie un tableau par base NBITS
 * @tparam Iterator
 * @tparam NBITS
 * @param first
 * @param last
 */
template<typename Iterator, size_t NBITS>
void radix_sort(Iterator first, Iterator last) {
	using T = typename Iterator::value_type;
	static_assert(std::is_unsigned<T>::value);

	std::vector<T> output(first, last);
	for (size_t i = 0; i < std::numeric_limits<T>::digits / NBITS; ++i) {
		counting_sort(first, last, output.begin(), SomeBits<T>(NBITS, i),
					  (1 << NBITS));
		std::copy(output.begin(), output.end(), first);
	}
}

#endif // RADIX_SORT_HPP