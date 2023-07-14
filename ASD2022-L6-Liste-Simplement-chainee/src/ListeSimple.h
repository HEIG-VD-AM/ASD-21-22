#ifndef LISTE_H
#define LISTE_H

#include "LSIterator.h"
#include <utility> // std::swap;
#include <exception>

template<typename T>
class ListeSimple {
public:
	using value_type = T;
	using reference = T&;
	using const_reference = T const&;

private:
	struct Maillon {
		value_type valeur;
		Maillon* suivant;
	};

	Maillon avant_premier;

public:
	using iterator = LSIterator<value_type>;
	friend iterator;

	using const_iterator = LSConstIterator<value_type>;
	friend const_iterator;

	const_iterator cbegin() const noexcept {
		return const_iterator(avant_premier.suivant);
	}

	iterator begin() noexcept {
		return iterator(avant_premier.suivant);
	}

	const_iterator begin() const noexcept {
		return cbegin();
	}

	ListeSimple() : avant_premier{value_type{}, nullptr} {

	}

	// A compléter pour fournir ...
	//
	// end, cend, before_begin, cbefore_begin, empty, front
	// insert_after, erase_after, splice_after, push_front, pop_front,
	// swap, sort, ainsi que constructeur, opérateur d'affectation et destructeur

	// Iterators related methods

	const_iterator cend() const noexcept {
		return const_iterator(nullptr);
	}

	iterator end() noexcept {
		return iterator(nullptr);
	}

	const_iterator end() const noexcept {
		return cend();
	}

	const_iterator cbefore_begin() const noexcept {
		return const_iterator{&avant_premier};
	}

	iterator before_begin() noexcept {
		return iterator{&avant_premier};
	}

	const_iterator before_begin() const noexcept {
		return cbefore_begin();
	}

	// Ctor

	ListeSimple(const ListeSimple<T>& other) : avant_premier{value_type{}, nullptr} {
		if (!other.empty() && this != &other) {
			auto last_index = iterator(&avant_premier);
			auto i = other.begin();
			while (i != other.end()) {
				insert_after(last_index, *i);
				last_index = last_index.m->suivant;
				++i;
			}
		}
	}

	// Dtor

	~ListeSimple() {
		Maillon* i = avant_premier.suivant;
		Maillon* tmp = nullptr;
		while (i != nullptr) {
			tmp = i->suivant;
			delete i;
			i = tmp;
		}
	}

	// Operators

	ListeSimple& operator=(const ListeSimple<T>& other) {
		if (this == &other) { return *this; }
		ListeSimple tmp(other);
		this->swap(tmp);
		return *this;
	}

	// Utils methods

	bool empty() const {
		return begin() == end();
	}

	reference front() {
		return *(begin());
	}

	const_reference front() const {
		return *(cbegin());
	}

	void insert_after(iterator it, const_reference val) {
		if (it != end())
			it.m->suivant = new Maillon{val, it.m->suivant};
	}

	void erase_after(iterator& it) {
		if (it != begin() && it != end()) {
			Maillon* tmp = it.m->suivant;
			it.m->suivant = it.m->suivant->suivant;
			delete tmp;
		}
	}

	void splice_after(iterator it, iterator begin, iterator end) {
		using std::swap;
		if (begin != end) {
			swap(end.m->suivant, it.m->suivant);
			swap(it.m->suivant, begin.m->suivant);
		}
	}

	void push_front(const_reference v) {
		insert_after(before_begin(), v);
	}

	void pop_front() {
		erase_after(before_begin());
	}

	void swap(ListeSimple<T>& other) {
		using std::swap;
		swap(avant_premier, other.avant_premier);
	}

	void sort() {
		iterator current = before_begin();
		iterator j = current;
		while (std::next(current) != end()) {
			while (std::next(j, 2) != end()) {
				if (*std::next(j) > *std::next(j, 2)) {
					splice_after(j, std::next(j), std::next(j, 2));
				}
				++j;
			}
			++current;
			j = before_begin();
		}
	}

};

#endif //LISTE_H
