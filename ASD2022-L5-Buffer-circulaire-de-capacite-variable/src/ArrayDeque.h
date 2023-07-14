#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <ostream>
#include <stdexcept>
#include <algorithm>
#include <new>

template<class T>
class ArrayDeque {
public:
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using size_type = std::size_t;

private:
	pointer buffer;
	size_type capacite;
	size_type debut;
	size_type taille;

	size_type get_new_capacity() {
		if (capacite == 0)
			return 1;
		else
			return 2 * capacite;
	}

	size_type get_new_index(size_type i, size_type new_capacity, size_type begin) {
		size_type ip = (begin + i + new_capacity) % new_capacity;
		if (ip >= 0) return ip;
		else return ip + new_capacity;
	}

	size_type get_new_index(size_type i, size_type new_capacity) {
		return get_new_index(i, new_capacity, debut);
	}

public:
	ArrayDeque(size_type _capacite = 0) : buffer(nullptr), capacite(_capacite), debut(0), taille(0) {
		if (capacite)
			buffer = reinterpret_cast<pointer> (::operator new(capacite * sizeof(value_type)));
	}

	ArrayDeque(const ArrayDeque& other) : ArrayDeque(other.capacite) {
		size_type j = 0;
		// xxx: on peut éviter les try-catch?
		try {
			for (size_type i = 0; i < other.taille; ++i, ++j)
				new(buffer + get_new_index(i, other.capacite, other.debut))
						value_type{*(other.buffer + other.get_index(i))};
		} catch (...) {
			for (size_type i = 0; i < j; ++i)
				(buffer + get_new_index(i, other.capacite, other.debut))->~value_type();
			throw;
		}
		debut = other.debut;
		taille = other.taille;
	}

	size_type get_index(size_type i) const {
		size_type ip = (debut + i + capacite) % capacite;
		if (ip >= 0) return ip;
		else return ip + capacite;
	}

	value_type& operator[](size_type i) const {
		return at(i);
	}

	value_type& at(size_type i) const {
		if (i < 0 || i >= size()) throw std::out_of_range(__func__);
		return *(buffer + get_index(i));
	}

	bool empty() const {
		return taille == 0;
	}

	size_type size() const {
		return taille;
	}

	size_type capacity() const {
		return capacite;
	}

	value_type& front() const {
		return at(0);
	}

	value_type& back() const {
		return at(taille - 1);
	}

	void swap(ArrayDeque<value_type>& other) noexcept {
		using std::swap;
		swap(capacite, other.capacite);
		swap(debut, other.debut);
		swap(taille, other.taille);
		swap(buffer, other.buffer);
	}

	void pop_front() {
		if (empty()) throw std::out_of_range(__func__);
		(buffer + get_index(0))->~value_type();
		debut = get_index(1);
		--taille;
	}

	void push_front(const value_type& val) {
		if (size() >= capacity()) {
			size_type new_capacity = get_new_capacity();

			auto tmp = reinterpret_cast<pointer> (::operator new(new_capacity * sizeof(value_type)));
			size_type j = 0;
			try {
				for (size_type i = 0; i < size(); ++i, ++j)
					new(tmp + get_new_index(i, new_capacity)) value_type{*(buffer + get_index(i))};
			} catch (...) {
				for (size_type i = 0; i < j; ++i)
					(tmp + get_new_index(i, new_capacity))->~value_type();
				throw;
			}

			for (size_type i = 0; i < size(); ++i)
				(buffer + get_index(i))->~value_type();

			::operator delete(buffer);
			buffer = tmp;
			capacite = new_capacity;
		}
		size_type new_begin = get_index(capacity() - 1);
		new(buffer + new_begin) value_type{val};
		// no exception past this line (strong guarantee)
		debut = new_begin;
		++taille;
	}

	void pop_back() {
		if (empty()) throw std::out_of_range(__func__);
		(buffer + get_index(size() - 1))->~value_type();
		--taille;
	}

	void push_back(const value_type& val) {
		if (size() >= capacity()) {
			size_type new_capacity = get_new_capacity();

			auto tmp = reinterpret_cast<pointer> (::operator new(new_capacity * sizeof(value_type)));
			size_type j = 0;
			try {
				for (size_type i = 0; i < size(); ++i, ++j) {
					new(tmp + get_new_index(i, new_capacity)) value_type{*(buffer + get_index(i))};
				}
			} catch (...) {
				for (size_type i = 0; i < j; ++i)
					(tmp + get_new_index(i, new_capacity))->~value_type();
				throw;
			}
			for (size_type i = 0; i < taille; ++i)
				(buffer + get_index(i))->~value_type();

			::operator delete(buffer);
			buffer = tmp;
			capacite = new_capacity;
		}
		new(buffer + get_index(size())) value_type{val};
		++taille;
	}

	void shrink_to_fit() {
		if (size() < capacity()) {
			auto tmp = reinterpret_cast<pointer> (::operator new(size() * sizeof(value_type)));
			for (size_type i = 0; i < taille; ++i)
				new(tmp + get_new_index(i, size())) T{*(buffer + get_index(i))};

			for (size_type i = 0; i < taille; ++i)
				(buffer + get_index(i))->~value_type();
			::operator delete(buffer);
			buffer = tmp;
			capacite = size();
		}
	}

	ArrayDeque& operator=(const ArrayDeque& other) {
		if (this == &other) return *this;
		if (other.taille > capacity()) {
			auto tmp = ArrayDeque(other);
			swap(tmp);
		} else {
			auto tmp = reinterpret_cast<pointer> (::operator new(capacity() * sizeof(value_type)));
			size_type j = 0;
			try {
				for (size_type i = 0; i < other.size(); ++i, ++j)
					new(tmp + get_index(i)) value_type{*(other.buffer + other.get_index(i))};
			} catch (...) {
				for (size_type i = 0; i < j; ++i)
					(tmp + get_index(i))->~value_type();
				throw;
			}

			for (size_type i = other.taille; i < size(); ++i)
				(buffer + get_index(i))->~value_type();
			buffer = tmp;
			taille = other.taille;
		}
		return *this;
	}

	~ArrayDeque() {
		for (size_type i = 0; i < size(); ++i) {
			(buffer + get_index(i))->~value_type();
		}
		::operator delete(buffer);
	}
};

template<typename T>
inline
std::ostream& operator<<(std::ostream& s,
						 const ArrayDeque<T>& v) {
	s << "(" << v.size() << "/" << v.capacity() << ") : ";
	if (not v.empty())
		s << v.front() << " -> " << v.back() << " : ";
	s << "[";
	for (size_t i = 0; i < v.size(); ++i) {
		s << v[i];
		if (i != v.size() - 1)
			s << ", ";
	}
	s << "]";
	return s;
}

#endif /* ArrayDeque_hpp */
