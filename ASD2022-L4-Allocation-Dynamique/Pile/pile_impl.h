#ifndef PILE_IMPL_H
#define PILE_IMPL_H

#include <stdexcept> // std::out_of_range
#include "pile.h"
#include <new>

// AJOUTEZ VOTRE CODE ICI ...
template<typename T>
Pile<T>::Pile(size_t n) {
	capacite = n;
	taille = 0;
	data = reinterpret_cast<T*>(::operator new(n * sizeof(T)));
}

template<typename T>
Pile<T>::Pile(const Pile& other) : Pile(other.capacite) {
	taille = other.taille;
	for (size_t i = 0; i < taille; ++i)
		new(data + i) T{*(other.data + i)};
}

template<typename T>
void Pile<T>::push(T e) {
	if (taille >= capacite)
		throw std::out_of_range(__func__);
	new(data + taille) T{std::move(e)};
	++taille;
}

template<typename T>
void Pile<T>::pop() {
	if (this->empty())
		throw std::out_of_range(__func__);
	(data + (taille - 1))->~T();
	--taille;
}

template<typename T>
const T& Pile<T>::top() const {
	if (this->empty())
		throw std::out_of_range(__func__);
	return *(data + (taille - 1));
}

template<typename T>
bool Pile<T>::empty() const noexcept {
	return taille == 0;
}

template<typename T>
bool Pile<T>::full() const noexcept {
	return taille == capacite;
}

template<typename T>
void Pile<T>::swap(Pile<T>& other) noexcept {
	using std::swap;
	swap(taille, other.taille);
	swap(capacite, other.capacite);
	swap(data, other.data);
}

template<typename T>
Pile<T>& Pile<T>::operator=(const Pile<T>& other) {
	if (this == &other) return *this;

	if (other.taille > capacite) {
		auto tmp = Pile<T>(other);
		swap(tmp);
	} else {
		for (size_t i = 0; i < std::min(taille, other.taille); ++i)
			*(data + i) = *(other.data + i);

		for (size_t i = std::min(taille, other.taille); i < other.taille; ++i)
			new(data + i) T{*(other.data + i)};

		for (size_t i = other.taille; i < taille; ++i)
			(data + i)->~T();

		taille = other.taille;
	}
	return *this;
}

template<typename T>
Pile<T>::~Pile<T>() {
	for (size_t i = 0; i < taille; ++i)
		(data + i)->~T();
	::operator delete(data);
}
// ... FIN DE VOTRE CODE

#endif
