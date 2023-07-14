/*
 ----------------------------------------------------------------------------------
 Nom du fichier : check_info.hpp

 Auteur(s)      : Rayane Annen, Hugo Ducommun, Alexis Martins

 Date creation  : 23.02.2022

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#ifndef CHECK_INFO_HPP
#define CHECK_INFO_HPP

#include <string>
#include "generator.hpp"

/**
 *
 * @tparam T
 */
template<typename T>
struct CheckInfo {
	std::string function_name;
	std::string info;
	InputType input_type;
	unsigned int seed;
	unsigned int measure_count;
	unsigned int sample_size;
};

#endif // CHECK_INFO_HPP
