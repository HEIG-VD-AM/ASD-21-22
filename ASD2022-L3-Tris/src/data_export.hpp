/*
 ----------------------------------------------------------------------------------
 Nom du fichier : data_export.hpp

 Auteur(s)      : Rayane Annen, Hugo Ducommun, Alexis Martins

 Date creation  : 23.02.2022

 Compilateur    : Mingw-w64 g++ 11.2.0
 ----------------------------------------------------------------------------------
*/
#ifndef DATA_EXPORT_HPP
#define DATA_EXPORT_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <numeric>
#include <cstdlib>

/**
 *
 * @tparam T
 * @tparam U
 * @param filename
 * @param header
 * @param data
 */
template<typename T, typename U>
void export_csv(const std::string &filename, const std::vector<T> &header,
					 const std::vector<std::vector<U>> &data) {
	std::ofstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Echec d'ouverture du fichier : " << filename << " en ecriture."
					 << std::endl;
	}
	file << "nombre entree, ";
	for (size_t i = 0; i < header.size(); ++i) {
		file << header[i];
		if (i != header.size() - 1)
			file << ',';
	}
	file << std::endl;

	for (size_t i = 0; i < data.size(); ++i) {
		file << "mesure, ";
		for (size_t j = 0; j < data[i].size(); ++j) {
			file << data[i][j];
			if (j != data[i].size() - 1)
				file << ',';
		}
		file << std::endl;
	}
}

#endif // DATA_EXPORT_HPP