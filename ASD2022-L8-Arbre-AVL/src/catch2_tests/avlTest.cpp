#define CATCH_CONFIG_FAST_COMPILE

#include "catch.hpp"
#include "../avlTree.h"

#include <string>

using namespace std;

avlTree<int> make_easy_test_tree6() {
   avlTree<int> tree;
   for (int i: {8, 4 , 11, 1, 6, 10, 12, 2, 5, 7, 3}) {
      tree.insert(i);
   }
   return tree;
}

avlTree<int> make_easy_test_tree5() {
   avlTree<int> tree;
   for (int i: {3, 1, 6, 2, 5, 8, 4, 7, 9}) {
      tree.insert(i);
   }
   return tree;
}

avlTree<int> make_easy_test_tree4() {
   avlTree<int> tree;
   for (int i: {3, 2, 6, 1, 4, 7, 5}) {
      tree.insert(i);
   }
   return tree;
}

avlTree<int> make_easy_test_tree3() {
   avlTree<int> tree;
   for (int i: {5, 2, 10, 1, 4, 7, 11, 3, 6, 9, 12, 8}) {
      tree.insert(i);
   }
   return tree;
}

avlTree<int> make_easy_test_tree2() {
	avlTree<int> tree;
	for (int i: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
		tree.insert(i);
	return tree;
}

avlTree<int> make_easy_test_tree() { // order of insertion requires AVL no balancing
	avlTree<int> tree;
	for (int i: {6, 3, 9, 2, 4, 7, 10, 1, 5, 8})
		tree.insert(i);
	return tree;
}

TEST_CASE("erase", "[avlTree]") {

   SECTION("Erase on empty tree") {
      avlTree<int> tree;
      CHECK_NOTHROW(tree.erase(0));
   }

   SECTION("Erase key that doesn't exist") {
      avlTree<int> tree = make_easy_test_tree();
      CHECK_NOTHROW(tree.erase(1337));
   }

   SECTION("Erase balance with single rotation") {
      avlTree<int> tree = make_easy_test_tree4();
      tree.erase(2);
      ostringstream oss;
      oss << tree;
      REQUIRE(oss.str() == "4(3(1(.,.),.),6(5(.,.),7(.,.)))");
   }

   SECTION("Erase balance with double rotation") {
      avlTree<int> tree = make_easy_test_tree3();
      tree.erase(1);
      ostringstream oss;
      oss << tree;
      REQUIRE(oss.str() == "7(5(3(2(.,.),4(.,.)),6(.,.)),10(9(8(.,.),.),11(.,12(.,.))))");
   }
}

TEST_CASE("erase_min", "[avlTree]") {

   SECTION("Erase min on empty tree") {
      avlTree<int> tree;
      CHECK_THROWS(tree.erase_min());
   }

   SECTION("Erase min without rebalance") {
      avlTree<int> tree = make_easy_test_tree6();
      tree.erase_min();
      ostringstream oss;
      oss << tree;
      REQUIRE(oss.str() == "8(4(2(.,3(.,.)),6(5(.,.),7(.,.))),11(10(.,.),12(.,.)))");
   }

   SECTION("Erase min with rebalance") {
      avlTree<int> tree = make_easy_test_tree5();
      tree.erase_min();
      ostringstream oss;
      oss << tree;
      REQUIRE(oss.str() == "6(3(2(.,.),5(4(.,.),.)),8(7(.,.),9(.,.)))");
   }
}

TEST_CASE("erase_max", "[avlTree]") {

   SECTION("Erase max on empty tree") {
      avlTree<int> tree;
      CHECK_THROWS(tree.erase_max());
   }

   SECTION("Erase max without rebalance") {
      avlTree<int> tree = make_easy_test_tree2();
      tree.erase_max();
      ostringstream oss;
      oss << tree;
      REQUIRE(oss.str() == "4(2(1(.,.),3(.,.)),8(6(5(.,.),7(.,.)),9(.,.)))");
   }

   SECTION("Erase max with rebalance") {
      avlTree<int> tree = make_easy_test_tree4();
      tree.erase_max();
      ostringstream oss;
      oss << tree;
      REQUIRE(oss.str() == "3(2(1(.,.),.),5(4(.,.),6(.,.)))");
   }
}

TEST_CASE("insert", "[avlTree]") {

	SECTION("Insert into empty tree") {
		avlTree<int> tree;
		tree.insert(42);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "42\n");
	}

	SECTION("Insert smaller to the left") {
		avlTree<int> tree;
		tree.insert(3);
		tree.insert(2);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "3\n"
									"|_ 2\n"
									"|_ .\n");
	}

	SECTION("Insert larger to the right") {
		avlTree<int> tree;
		tree.insert(3);
		tree.insert(4);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "3\n"
									"|_ .\n"
									"|_ 4\n");
	}

	SECTION("Insert twice has no effect") {
		avlTree<int> tree;
		tree.insert(3);
		tree.insert(4);
		tree.insert(4);

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "3\n"
									"|_ .\n"
									"|_ 4\n");
	}

   SECTION("Insert balance") {
      avlTree<int> tree = make_easy_test_tree5();
      tree.insert(10);
      ostringstream oss;
      oss << tree;
      REQUIRE(oss.str() == "6(3(1(.,2(.,.)),5(4(.,.),.)),8(7(.,.),9(.,10(.,.))))");
   }

	SECTION("Easy tree") {
		avlTree<int> tree = make_easy_test_tree();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "6\n"
									"|_ 3\n"
									"|  |_ 2\n"
									"|  |  |_ 1\n"
									"|  |  |_ .\n"
									"|  |_ 4\n"
									"|     |_ .\n"
									"|     |_ 5\n"
									"|_ 9\n"
									"   |_ 7\n"
									"   |  |_ .\n"
									"   |  |_ 8\n"
									"   |_ 10\n");
	}
}

TEST_CASE("display_indented", "[avlTree]") {

	SECTION("Empty tree") {
		avlTree<int> tree;

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == ".\n");
	}

	SECTION("Easy test tree") {
		avlTree<int> tree = make_easy_test_tree();

		ostringstream oss;
		tree.show_indented(oss);
		REQUIRE(oss.str() == "6\n"
									"|_ 3\n"
									"|  |_ 2\n"
									"|  |  |_ 1\n"
									"|  |  |_ .\n"
									"|  |_ 4\n"
									"|     |_ .\n"
									"|     |_ 5\n"
									"|_ 9\n"
									"   |_ 7\n"
									"   |  |_ .\n"
									"   |  |_ 8\n"
									"   |_ 10\n");
	}
}

TEST_CASE("contains_in_subtree", "[avlTree]") {

	SECTION("Contains") {
		avlTree<int> tree = make_easy_test_tree();
		REQUIRE(tree.contains(3) == true);
	}

	SECTION("Doesn't contain") {
		avlTree<int> tree = make_easy_test_tree();
		REQUIRE(tree.contains(20) == false);
	}
}

TEST_CASE("min", "[avlTree]") {
	SECTION("Empty tree") {
		avlTree<int> tree;
		CHECK_THROWS(tree.min());
	}

	SECTION("Easy tree test") {
		avlTree<int> tree = make_easy_test_tree();
		REQUIRE(tree.min() == 1);
	}
}

TEST_CASE("max", "[avlTree]") {
	SECTION("Empty tree") {
		avlTree<int> tree;
		CHECK_THROWS(tree.max());
	}

	SECTION("Easy tree test") {
		avlTree<int> tree = make_easy_test_tree();
		REQUIRE(tree.max() == 10);
	}
}

TEST_CASE("operator<<", "[avlTree]") {

	SECTION("Empty tree") {
		avlTree<int> tree;

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == ".");
	}

	SECTION("Easy test tree") {
		avlTree<int> tree = make_easy_test_tree();

		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
	}
}

TEST_CASE("operator>>", "[avlTree]") {
	SECTION("Empty Tree") {
		avlTree<int> tree;
		istringstream iss(".");
		iss >> tree;
		ostringstream oss;
		oss << tree;
		REQUIRE(oss.str() == ".");
	}
}

TEST_CASE("copy_in_subtree", "[avlTree]") {
	SECTION("Empty") {
		avlTree<int> tree;
		avlTree<int> cp{tree};
		ostringstream oss, cpOss;
		oss << tree;
		cpOss << cp;
		REQUIRE(oss.str() == cpOss.str());
	}

	SECTION("Copy easy tree") {
		avlTree<int> tree = make_easy_test_tree();
		avlTree<int> cp{tree};
		ostringstream oss, cpOss;
		oss << tree;
		cpOss << cp;
		REQUIRE(oss.str() == cpOss.str());
	}
}

TEST_CASE("assignment", "[avlTree]") {
	SECTION("Assign to empty tree") {
		avlTree<int> tree = make_easy_test_tree();
		avlTree<int> cp;
		cp = tree;
		ostringstream oss, cpOss;
		oss << tree;
		cpOss << cp;
		REQUIRE(oss.str() == cpOss.str());
	}

	SECTION("Assign to non empty tree") {
		avlTree<int> tree = make_easy_test_tree2();
		avlTree<int> cp = make_easy_test_tree();
		cp = tree;
		ostringstream oss, cpOss;
		oss << tree;
		cpOss << cp;
		REQUIRE(oss.str() == cpOss.str());
	}

}

TEST_CASE("contains", "[avlTree]") {
	SECTION("tree contains element") {
		avlTree<int> tree = make_easy_test_tree();
		REQUIRE(tree.contains(1) == true);
	}

	SECTION("tree doesn't contain element") {
		avlTree<int> tree = make_easy_test_tree();
		REQUIRE(tree.contains(11) == false);
	}
}

TEST_CASE("min max", "[avlTree]") {
	SECTION("min on non empty tree") {
		avlTree<int> tree = make_easy_test_tree();
		REQUIRE(tree.min() == 1);
	}

	SECTION("max on non empty tree") {
		avlTree<int> tree = make_easy_test_tree();
		REQUIRE(tree.max() == 10);
	}

	SECTION("min on empty tree") {
		avlTree<int> tree;
		CHECK_THROWS(tree.min());
	}


	SECTION("max on empty tree") {
		avlTree<int> tree;
		CHECK_THROWS(tree.max());
	}

	SECTION("max is the first element") {
		avlTree<int> tree;
		tree.insert(1);
		REQUIRE(tree.max() == 1);
	}
	SECTION("min is the first element") {
		avlTree<int> tree;
		tree.insert(1);
		REQUIRE(tree.min() == 1);
	}
}