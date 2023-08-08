#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base *(*generateInstance[3])(void) = {
	[](void) -> Base* {
		Base* x = new A;
		return (x);
	},
	[](void) -> Base* {
		Base* x = new B;
		return (x);
	},
	[](void) -> Base* {
		Base* x = new C;
		return (x);
	}
};

Base* generate(void) {
	return (generateInstance[rand() % 2]());
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << "Type == A" << std::endl;
	if (dynamic_cast<B*>(p) != NULL)
		std::cout << "Type == B" << std::endl;
	if (dynamic_cast<C*>(p) != NULL)
		std::cout << "Type == C" << std::endl;
	else
		std::cout << "Invalid" << std::endl;
}

void identify(Base& p) {
	(void)p;
}
