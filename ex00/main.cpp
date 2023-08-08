#include "ScalarConverter.hpp"

int main(int argc, char *argv[]) {
	ScalarConverter converter;

	if (argc != 2)
		return (0);
	std::string x = argv[1];
	converter.convert(x);
}
