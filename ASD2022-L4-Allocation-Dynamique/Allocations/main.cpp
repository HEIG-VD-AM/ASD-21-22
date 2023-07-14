//FORBIDDEN cout
//FORBIDDEN cerr
//FORBIDDEN printf
//FORBIDDEN puts
//FORBIDDEN putchar
//FORBIDDEN putc
#include "util.h"
#include "c.h"

int cnt = 0; // utilisez cette variable globale

void f0() noexcept {
	enter("f0");
	static C c2(++cnt);
	C c3(++cnt);
	leave("f0");
}

C* f1() {
	enter("f1");
	C* p;
	p = new C(++cnt);
	leave("f1");
	return p;
}

C* f2() {
	enter("f2");
	C* p;
	p = new C[2]{C(++cnt), C(++cnt)};
	leave("f2");
	return p;
}

void f3(C* p) noexcept {
	enter("f3");
	new(p) C{++cnt};
	leave("f3");
}

void f4(C* p, size_t n) noexcept {
	enter("f4");
	for (size_t i = 0; i < n; ++i)
		new(p + i) C{C(++cnt)};
	leave("f4");
}

	int main() {
		enter("main");
		C c1(++cnt);
		f0();
		f0();
		C* q = f1();
		C* k = f2();
		C* r = (C*) (::operator new(sizeof(C)));
		f3(r);
		delete[] k;
		delete q;
		C* u = (C*) (::operator new(2 * sizeof(C)));
		f4(u, 2);
		delete r;
		C* j = (C*) (::operator new(1 * sizeof(C)));
		f4(j, 1);
		u->~C();
		(u + 1)->~C();
		::operator delete(u);
		delete j;
		leave("main");
	}
