#include <iostream>
#include "Serialization.hpp"

int main(void) {
	uintptr_t	raw;
	Data		test;
	Data		*test_ptr;

	test.num = 10;
	raw = serialize(&test);
	std::cout << raw << std::endl;
	test_ptr = deserialize(raw);
	if (test_ptr == &test) {
		std::cout << "Success" << std::endl;
		std::cout << test_ptr->num << std::endl;
	}
	else
		std::cout << "Failure" << std::endl;
}
