#ifndef ASD_LABS_2021_AVLNODE_H
#define ASD_LABS_2021_AVLNODE_H

namespace avl {

	enum Side {
		LEFT = 0, RIGHT = 1
	};

	template <typename Key>
	struct Node {
		Key const key;
		std::array<Node*, 2> children;
		unsigned char height;

		inline Node*& left() noexcept { return children[LEFT]; }

		inline Node* const& left() const noexcept { return children[LEFT]; }

		inline Node*& right() noexcept { return children[RIGHT]; }

		inline Node* const& right() const noexcept { return children[RIGHT]; }

		static constexpr std::array<Node*, 2> NO_CHILD{nullptr, nullptr};
	};

	template<typename Key>
	unsigned char height(Node<Key>* r);

	template<typename Key>
	void calculate_height(Node<Key>* r);

	template<typename Key>
	char balance(Node<Key>* const& r);

	template<typename Key>
	void rotate_left(Node<Key>*& r);

	template<typename Key>
	void rotate_right(Node<Key>*& r);

	template<typename Key>
	void rebalance(Node<Key>*& r);

	template <typename Key>
	void insert_in_subtree(Node<Key>*& r, Key const& k);

	template <typename Key>
	bool contains_in_subtree(const Node<Key>*& r, const Key& k);

	template <typename Key>
	Key const& max_in_subtree(Node <Key>* const& r);

	template <typename Key>
	Key const& min_in_subtree(Node <Key>* const& r);

	template <typename Key>
	Node<Key>* extract_min(Node<Key>*& r);

	template <typename Key>
	void erase_min(Node<Key>*& r);

	template <typename Key>
	void erase_max(Node<Key>*& r);

	template <typename Key>
	void erase(Node<Key>*& r, Key const& k);

	template <typename Key>
	void copy_in_subtree(Node<Key>*& parent, Node<Key>* const& cp);

	template <typename Key>
	std::ostream& show_indented(Node<Key>* r,
										 std::ostream& out = std::cout,
										 std::string before = "",
										 bool isright = false);

	template <typename Key>
	std::ostream& operator<<(std::ostream& out, Node <Key>* r);

	template <typename Key>
	std::istream& operator>>(std::istream& in, Node <Key>* r);

	template <typename Key>
	void destroy_in_subtree(Node <Key>* const& r);

}

#include "avlNodeImplementation.h"

#endif //ASD_LABS_2021_AVLNODE_H
