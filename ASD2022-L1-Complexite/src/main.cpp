/*
 ----------------------------------------------------------------------------------
 Nom du fichier : main.cpp

 Auteur(s)      : Hugo Ducommun,
                  Rayane Annen,
                  Alexis Martins

 Date creation  : 23.02.2022

 Description    : -

 Remarque(s)    : -

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#include <cstdlib>
#include "check_sort.h"
#include "benchmark_time.h"
#include "benchmark_counter.h"

using namespace std;

int main() {
	check_sort_algorithms();
	benchmark_time();
	benchmark_counter();
	return EXIT_SUCCESS;
}

