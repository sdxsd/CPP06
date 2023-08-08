#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base(void) {
	;
}

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
	srand(time(NULL));
	return (generateInstance[rand() % 3]());
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << "Type == A" << std::endl;
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << "Type == B" << std::endl;
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << "Type == C" << std::endl;
	else
		std::cout << "Invalid" << std::endl;
}

void identify(Base& p) {
	(void)p;
}
