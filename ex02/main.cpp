#include <iostream>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int main(void) {
	Base	*x = generate();
	identify(x);
	delete x;

	A		y;
	B		z;
	C		a;
	Base	g;
	identify(y);
	identify(z);
	identify(a);
	identify(g);
	return 0;
}
