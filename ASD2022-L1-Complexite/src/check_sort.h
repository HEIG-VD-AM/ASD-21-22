/*
 ----------------------------------------------------------------------------------
 Nom du fichier : check_sort.h

 Auteur(s)      : Hugo Ducommun,
 						Rayane Annen,
                  Alexis Martins

 Date creation  : 23.02.2022

 Description    : -

 Remarque(s)    : -

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#ifndef CHECK_SORT_H
#define CHECK_SORT_H

#include <iostream>
#include <vector>
#include "generator.h"
#include "sort_algorithms.h"

template<typename T>
bool check_sort(const std::vector<T> &v) {
	for (auto it = v.cbegin(); it != v.cend() - 1; ++it) {
		if (*(it + 1) < *it)
			return false;
	}
	return true;
}

void check_sort_algorithms() {

	auto v = vector_generator<int>(100, 1337, InputType::SHUFFLE);
	selection_sort(v);
	std::cout << "Tri par selection par vecteur : "
				 << (check_sort(v) ? "OK" : "NOK") << std::endl;

	v = vector_generator<int>(100, 1337, InputType::SHUFFLE);
	selection_sort(v.begin(), v.end());
	std::cout << "Tri par selection par iterateurs : "
				 << (check_sort(v) ? "OK" : "NOK") << std::endl;

	v = vector_generator<int>(100, 1337, InputType::SHUFFLE);
	insert_sort(v);
	std::cout << "Tri par insertion par vecteur : "
				 << (check_sort(v) ? "OK" : "NOK") << std::endl;

	v = vector_generator<int>(100, 1337, InputType::SHUFFLE);
	insert_sort(v.begin(), v.end());
	std::cout << "Tri par insertion par iterateurs : "
				 << (check_sort(v) ? "OK" : "NOK") << std::endl;

	v = vector_generator<int>(100, 1337, InputType::SHUFFLE);
	bubble_sort(v);
	std::cout << "Tri a bulle par vecteur : "
				 << (check_sort(v) ? "OK" : "NOK") << std::endl;

	v = vector_generator<int>(100, 1337, InputType::SHUFFLE);
	bubble_sort(v.begin(), v.end());
	std::cout << "Tri a bulle par iterateurs : "
				 << (check_sort(v) ? "OK" : "NOK") << std::endl;
}

#endif // CHECK_SORT_H
