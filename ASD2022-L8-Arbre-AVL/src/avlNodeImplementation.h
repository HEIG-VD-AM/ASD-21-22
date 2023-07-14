#ifndef ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
#define ASD_LABS_2021_AVLNODEIMPLEMENTATION_H

#include "avlNode.h"
#include <cctype>
#include <sstream>

namespace avl {

   template<typename Key>
   unsigned char height(Node <Key> *r) {
      if (r)
         return r->height;
      return 0;
   }

   template<typename Key>
   void calculate_height(Node <Key> *r) {
      if (r)
         r->height = (1 + std::max(height(r->left()), height(r->right())));
   }

   template<typename Key>
   char balance(Node <Key> *const &r) {
      if (r)
         return (char) (height(r->left()) - height(r->right()));
      return 0;
   }

   template<typename Key>
   void rotate_left(Node <Key> *&r) {
      Node<Key> *temp = r->right();
      if (temp) {
         r->right() = temp->left();
         temp->left() = r;
         r = temp;
         calculate_height(r->left());
         calculate_height(r);
      }
   }


   template<typename Key>
   void rotate_right(Node <Key> *&r) {
      Node<Key> *temp = r->left();
      if (temp) {
         r->left() = temp->right();
         temp->right() = r;
         r = temp;
         calculate_height(r->right());
         calculate_height(r);
      }
   }

   template<typename Key>
   void rebalance(Node <Key> *&r) {
      if (!r) return;

      if (balance(r) < -1) {
         if (balance(r->right()) > 0)
            rotate_right(r->right());
         rotate_left(r);
      } else if (balance(r) > 1) {
         if (balance(r->left()) < 0)
            rotate_left(r->left());
         rotate_right(r);
      } else {
         calculate_height(r);
      }
   }

   template<typename Key>
   void insert_in_subtree(Node <Key> *&r, Key const &k) {
      if (r == nullptr) {
         r = new Node<Key>{k, Node<Key>::NO_CHILD, 1};
      } else if (k == r->key) {
         return;
      } else {
         Side s = k < r->key ? LEFT : RIGHT;
         insert_in_subtree(r->children[s], k);
         rebalance(r);
      }
   }

   template<typename Key>
   bool contains_in_subtree(Node <Key> *const &r, Key const &k) {
      if (r == nullptr)
         return false;
      else if (r->key == k)
         return true;
      else if (k < r->key)
         return contains_in_subtree(r->left(), k);
      else
         return contains_in_subtree(r->right(), k);
   }

   template<typename Key>
   Key const &min_in_subtree(Node <Key> *const &r) {
      if (r == nullptr)
         throw std::exception();
      if (r->left() != nullptr)
         return min_in_subtree(r->left());
      return r->key;
   }

   template<typename Key>
   Key const &max_in_subtree(Node <Key> *const &r) {
      if (r == nullptr)
         throw std::exception();
      if (r->right() != nullptr)
         return max_in_subtree(r->right());
      return r->key;
   }

   template<typename Key>
   Node <Key> *extract_min(Node <Key> *&r) {
      if (r->left() != nullptr)
         return extract_min(r->left());
      else {
         Node<Key> *tmp = r;
         r = r->right();
         return tmp;
      }
   }

   template<typename Key>
   void erase_min(Node <Key> *&r) {
      if (r == nullptr) {
         throw std::exception();
      } else if (r->left()) {
         erase_min(r->left());
      } else {
         Node<Key> *d = r->right();
         delete r;
         r = d;
      }
      rebalance(r);
   }

   template<typename Key>
   void erase_max(Node <Key> *&r) {
      if (r == nullptr) {
         throw std::exception();
      } else if (r->right()) {
         erase_max(r->right());
      } else {
         Node<Key> *d = r->left();
         delete r;
         r = d;
      }
      rebalance(r);
   }

   template<typename Key>
   void erase(Node <Key> *&r, Key const &k) {

      if (r == nullptr) {}
      else if (k < r->key) {
         erase(r->left(), k);
      } else if (k > r->key) {
         erase(r->right(), k);
      } else {
         Node<Key> *tmp = r;

         if (r->left() == nullptr) {
            r = r->right();
         } else if (r->right() == nullptr) {
            r = r->left();
         } else {
            Node<Key> *min = extract_min(r->right());
            min->right() = r->right();
            min->left() = r->left();
            r = min;
         }
         delete tmp;
      }
      rebalance(r);
   }

   template<typename Key>
   void copy_in_subtree(Node <Key> *&parent, Node <Key> *const &cp) {
      if (cp->left() != nullptr) {
         parent->left() = new avl::Node<Key>{cp->left()->key, nullptr, nullptr};
         copy_in_subtree(parent->left(), cp->left());
      }
      if (cp->right() != nullptr) {
         parent->right() = new avl::Node<Key>{cp->right()->key, nullptr, nullptr};
         copy_in_subtree(parent->right(), cp->right());
      }
   }

   template<typename Key>
   std::ostream &show_indented(Node <Key> *r,
                               std::ostream &out,
                               std::string before,
                               bool isright) {
      out << before;
      if (not r) {
         out << ".\n";
      } else {
         if (not before.empty()) {
            before[before.size() - 2] = ' ';
            if (isright) {
               before[before.size() - 3] = ' ';
            }
         }
         out << r->key << std::endl;
         if (r->children != Node<Key>::NO_CHILD) {
            for (Side s: {LEFT, RIGHT}) {
               show_indented(r->children[s], out, before + "|_ ", s);
            }
         }
      }
      return out;
   }

   template<typename Key>
   std::ostream &operator<<(std::ostream &out, Node <Key> *r) {
      if (r != nullptr)
         out << r->key << "(" << r->left() << "," << r->right() << ")";
      else
         out << ".";
      return out;
   }

   template<typename Key>
   std::istream &operator>>(std::istream &in, Node <Key> *r) {
      char c = (char) in.peek();

      if (c == '.') {
         in.get();
         r = nullptr;
         return in;
      }

      std::string k;

      while (c != '\n' && c != '(' && c != ',' && c != ')') {
         in.get();
         k += c;
         c = (char) in.peek();
      }
      if (c != '\n') in.get();

      insert_in_subtree(r, std::stoi(k));

      if (c == '(') {
         in >> r->left();
         in.get();
         in >> r->right();
         in.get();
      }

      return in;
   }

   template<typename Key>
   void destroy_in_subtree(Node <Key> *const &r) {
      if (r != nullptr) {
         destroy_in_subtree(r->left());
         destroy_in_subtree(r->right());
         delete r;
      }
   }
}

#endif //ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
