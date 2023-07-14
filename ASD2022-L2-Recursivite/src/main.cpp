#include <iostream>
#include "pieces.h"
#include "solve.h"

using namespace std;

int main() {
	auto a = solve(PIECES);
	for (const auto& b : a) {
		cout << boardToString(b) << endl;
	}
}