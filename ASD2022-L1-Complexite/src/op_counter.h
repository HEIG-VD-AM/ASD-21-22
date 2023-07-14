/*
 ----------------------------------------------------------------------------------
 Nom du fichier : op_counter.h

 Auteur(s)      : Hugo Ducommun,
 						Rayane Annen,
                  Alexis Martins

 Date creation  : 23.02.2022

 Description    : -

 Remarque(s)    : -

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#ifndef OPCOUNTER_H
#define OPCOUNTER_H

#include <cstdlib>
#include <iostream>

template<typename T>
class OpCounter {
public:
	explicit OpCounter(T _n = 0) { n = _n; }

	static void reset_static_parameters() {
		OpCounter::count_affectations = 0;
		OpCounter::count_comparisons = 0;
	}

	OpCounter& operator=(const OpCounter& opCounter) {
		this->n = opCounter.n;
		OpCounter::count_affectations++;
		return *this;

	}

	OpCounter operator*(const OpCounter& opCounter) const {
		return OpCounter(this->n * opCounter.n);
	}

	OpCounter operator+(const OpCounter& opCounter) const {
		return OpCounter(this->n + opCounter.n);
	}

	OpCounter& operator++() {
		++count_affectations;
		++n;
		return *this;
	};

	static size_t get_affectation_count() {
		return count_affectations;
	};

	static size_t get_comparison_count() {
		return count_comparisons;
	};

	bool operator <(const OpCounter& opCounter) const {
		++count_comparisons;
		return n < opCounter.n;
	}
	bool operator >(const OpCounter& opCounter) const {
		++count_comparisons;
		return n > opCounter.n;
	}

private:
	T n;
	static size_t count_affectations;
	static size_t count_comparisons;
};

template<typename T>
size_t OpCounter<T>::count_affectations = 0;
template<typename T>
size_t OpCounter<T>::count_comparisons = 0;


#endif // OPCOUNTER_H
