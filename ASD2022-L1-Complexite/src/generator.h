/*
 ----------------------------------------------------------------------------------
 Nom du fichier : generator.h

 Auteur(s)      : Hugo Ducommun,
                  Rayane Annen,
                  Alexis Martins

 Date creation  : 24.02.2022

 Description    : -

 Remarque(s)    : -

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <random>
#include <numeric>
#include "op_counter.h"

enum class InputType {
	ASCENDING,
	DESCENDING,
	SHUFFLE,
	PARTIAL_SORT
};

template<typename T>
std::vector<T> vector_generator(size_t N, unsigned seed,
										  InputType input = InputType::ASCENDING) {
	std::vector<T> result(N);
	std::iota(result.begin(), result.end(), T(0));
	switch (input) {
		case InputType::DESCENDING:
			std::reverse(result.begin(), result.end());
			break;
		case InputType::SHUFFLE:
			std::shuffle(result.begin(), result.end(),
							 std::default_random_engine(seed));
			break;
		case InputType::PARTIAL_SORT:
			for (size_t i = 0; i < N; ++i)
				result[i] = T(.1 * (rand() % 100)) + T(.9) * result[i];
			break;
		default:
		case InputType::ASCENDING:
			break;
	}
	return result;
}

#endif // GENERATOR_H
