#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base(void) { ; }

void (*tryCast[3])(Base& p) = {
	[](Base& p) {
		A& x = dynamic_cast<A&>(p);
		(void)x;
	},
	[](Base& p) {
		B& x = dynamic_cast<B&>(p);
		(void)x;
	},
	[](Base& p) {
		C& x = dynamic_cast<C&>(p);
		(void)x;
	}
};

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
	std::cout << "Identify by pointer" << std::endl;
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << "(ptr) Type == A" << std::endl;
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << "(ptr) Type == B" << std::endl;
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << "(ptr) Type == C" << std::endl;
	else
		std::cout << "(ptr) Invalid" << std::endl;
}

void identify(Base& p) {
	std::cout << "Identify by reference" << std::endl;
	for (int i = 0; i < 3; i++) {
		try {
			tryCast[i](p);
			switch (i) {
				case 0: std::cout << "(ref) Type == A" << std::endl; return;
				case 1: std::cout << "(ref) Type == B" << std::endl; return;
				case 2: std::cout << "(ref) Type == C" << std::endl; return;
			}
		}
		catch(std::bad_cast& error) {
			if (i == 2)
				std::cout << "(ref) Invalid: " << error.what() << std::endl;
			continue;
		}
	}
}
