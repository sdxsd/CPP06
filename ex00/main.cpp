#include <iostream>
#include "ScalarConverter.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	ScalarConverter converter;

	if (argc != 2)
		return (0);
	std::string x = argv[1];
	converter.convert(x);
}
