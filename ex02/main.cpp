#include <iostream>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int main(void) {
	Base	*x = generate();
	identify(x);
	delete x;
	return 0;
}
