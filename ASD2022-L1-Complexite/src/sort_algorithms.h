/*
 ----------------------------------------------------------------------------------
 Nom du fichier : sort_algorithms.h

 Auteur(s)      : Hugo Ducommun,
                  Rayane Annen,
                  Alexis Martins

 Date creation  : 23.02.2022

 Description    : -

 Remarque(s)    :

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/

#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <iterator>
#include <algorithm>
#include <vector>
#include <utility>

template<typename Iterator>
void bubble_sort(Iterator first, Iterator last) {
	if (std::distance(first, last) > 0) {
		bool sorted = false;
		while (!sorted) {
			sorted = true;
			for (auto i = first; i != (last - 1); ++i) {
				if (*i > *(i + 1)) {
					std::iter_swap(i, i + 1);
					sorted = false;
				}
			}
			--last;
		}
	}
}

template<typename T>
void bubble_sort(std::vector<T> &v) {
	bubble_sort(v.begin(), v.end());
}

template<typename Iterator>
void insert_sort(Iterator first, Iterator last) {
	if (std::distance(first, last) != 0) {
		typename std::iterator_traits<Iterator>::value_type tmp{};
		Iterator it2{};
		for (auto it = first + 1; it != last; ++it) {
			tmp = *it;
			it2 = it;
			while (it2 >= first + 1 && *(it2 - 1) > tmp) {
				*it2 = *(it2 - 1);
				--it2;
			}
			*it2 = tmp;
		}
	}
}

template<typename T>
void insert_sort(std::vector<T> &v) {
	insert_sort(v.begin(), v.end());
}

template<typename Iterator>
void selection_sort(Iterator first, Iterator last) {
	if (std::distance(first, last) != 0) {
		Iterator it_min;
		for (auto it = first; it != last -1; ++it) {
			it_min = it;
			for (auto it2 = it + 1; it2 != last; ++it2) {
				if (*it2 < *it_min) {
					it_min = it2;

				}
			}
			std::iter_swap(it, it_min);
		}
	}
}

template<typename T>
void selection_sort(std::vector<T> &v) {
	selection_sort(v.begin(), v.end());
}

#endif // SORT_ALGORITHMS_H