#ifndef ASD_2021_AVL_IMPL_H
#define ASD_2021_AVL_IMPL_H

#include <utility>
#include <algorithm>
#include "avlTree.h"


template<typename Key>
avlTree<Key>::avlTree() : root(nullptr) {
}

template<typename Key>
avlTree<Key>::avlTree(avlTree const &other) : root(nullptr) {
	if (other.root == nullptr) return;
	root = new avl::Node<Key>{other.root->key, nullptr, nullptr};
	avl::copy_in_subtree( root, other.root);
}

template<typename Key>
avlTree<Key>::~avlTree() {
	avl::destroy_in_subtree(root);
}

template<typename Key>
void avlTree<Key>::insert(Key const& k) {
	avl::insert_in_subtree(root, k);
}

template<typename Key>
std::ostream& avlTree<Key>::show_indented(std::ostream& out) const {
	return avl::show_indented(root, out);
}

template<typename Key>
Key const& avlTree<Key>::min() const {
	return avl::min_in_subtree<Key>(root);
}

template<typename Key>
Key const& avlTree<Key>::max() const {
	return avl::max_in_subtree<Key>(root);
}

template<typename Key>
bool avlTree<Key>::contains(const Key& k) const noexcept {
	return avl::contains_in_subtree(this->root, k);
}

template<typename Key>
unsigned char avlTree<Key>::height() const noexcept {
	if (root == nullptr)
		return 0;
	else
		return avl::height(root);
}

template <typename Key>
void avlTree<Key>::erase(const Key& k) noexcept {
	avl::erase(root, k);
}

template <typename Key>
void avlTree<Key>::erase_max() {
	avl::erase_max(root);
}

template <typename Key>
void avlTree<Key>::erase_min() {
	avl::erase_min(root);
}

template <typename Key>
avlTree<Key>& avlTree<Key>::operator=(const avlTree& other) {
	if(this == &other) return *this;
	avlTree<Key> tmp{other};
	std::swap(root, tmp.root);
	return *this;
}

template<typename Key>
std::ostream& operator<<(std::ostream& out, avlTree<Key> const& tree) {
	out << tree.root;
	return out;
}

template<typename Key>
std::istream& operator>>(std::istream& in, avlTree<Key>& tree) {
	in >> tree.root;
	return in;
}

#endif //ASD_2021_AVL_IMPL_H
