#include <time.h>
#include <stdlib.h>

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
	srand(time(NULL));
	return (generateInstance[rand() % 2]());
}

void identify(Base* p) {
	;
}

void identify(Base& p) {
	;
}
