/*
 ----------------------------------------------------------------------------------
 Nom du fichier : main.cpp

 Auteur(s)      : Rayane Annen, Hugo Ducommun, Alexis Martins

 Date creation  : 24.02.2022

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/

#include "benchmark_time.hpp"
#include "check_sort.hpp"

using namespace std;

int main() {
	check_sort_algorithms();
	check_exec_time();
	benchmark_time();
}