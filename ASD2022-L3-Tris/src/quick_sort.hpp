/*
 ----------------------------------------------------------------------------------
 Nom du fichier : quick_sort.hpp

 Auteur(s)      : Rayane Annen, Hugo Ducommun, Alexis Martins

 Date creation  : 20.03.2022

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <algorithm>
#include <numeric>
#include <iterator>
#include <random>

/**
 * Partitionne un tableau dans le sens d'un tri rapide. Suppose que le pivot est
 * le dernier élément du tableau.
 * @tparam Iterator
 * @param first
 * @param last
 * @return Un itérateur qui pointe la position du pivot après partition.
 */
template<typename Iterator>
Iterator partition(Iterator first, Iterator last) {
	Iterator i = first - 1;
	Iterator j = last;

	while (true) {
		do {
			++i;
		} while (i < last && *i < *last);

		do {
			--j;
		} while (first < j && *last < *j);

		if (i >= j)
			break;
		std::iter_swap(i, j);
	}

	std::iter_swap(i, last);
	return i;
}

/**
 * Effectue le tri rapide d'un tableau.
 * @tparam Iterator
 * @param first
 * @param last
 */
template<typename Iterator>
void quick_sort(Iterator first, Iterator last) {
	while (first < last) {
		srand(unsigned(time(NULL)));
		Iterator pivot = first + (rand() % (std::distance(first, last)));
		std::iter_swap(last, pivot);
		Iterator i = partition(first, last);

		if (i - first < last - i) {
			quick_sort(first, i - 1);
			first = i + 1;
		} else {
			quick_sort(i + 1, last);
			last = i - 1;
		}
	}
}

#endif // QUICK_SORT_HPP