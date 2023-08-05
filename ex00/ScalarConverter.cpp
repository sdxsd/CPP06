#include "ScalarConverter.hpp"
#include <cctype>
#include <iostream>

void (*printFunctions[4])(literals type, const std::string& data) = {
	[](literals type, const std::string& data) { // INTEGER.
		int	convertedInt;

		try { convertedInt = std::stoi(data); }
		catch (std::invalid_argument &invalid_arg) {
			std::cout << invalid_arg.what() << std::endl;
			return ;
		}
		char character = static_cast<char>(convertedInt);
		float floatingPoint = static_cast<float>(convertedInt);
		double doublePrecision = static_cast<double>(convertedInt);
		std::printTypes()
	}
};

// Array of lambda functions for usage in type determination.
// Why? Lambda function arrays seemed cool.
literals (*determinerFunctions[3])(std::string &lit) = {
	[](std::string &lit) -> literals { // Integer determination.
		int	digitEncountered;
		for (long unsigned int i = 0; i < lit.length(); i++) {
			if (!std::isdigit(lit[i])) {
				if ((lit[i] == '+' || lit[i] == '-') && i == 0)
					continue;
				else return (INVALID);
			}
			if (std::isdigit(lit[i]))
				digitEncountered = true;
		}
		if (digitEncountered)
			return (INTEGER);
		else
			return (INVALID);
	},
	[](std::string &lit) -> literals { // Double & float determination.
		bool	digitEncountered;
		bool	decimalEncountered;

		digitEncountered = false;
		decimalEncountered = false;
		if (lit == ".")
			return (INVALID);
		else if (lit == "nan" || lit == "+inf" || lit == "-inf")
			return (DOUBLE);
		else if (lit == "+inff" || lit == "-inff" || lit == "nanf")
			return (FLOAT);
		for (long unsigned int i = 0; i < lit.length(); i++) {
			if (std::isdigit(lit[i]))
				digitEncountered = true;
			else if (lit[i] == '.') {
				if (decimalEncountered == true)
					return (INVALID);
				else
					decimalEncountered = true;
			}
			else if (!std::isdigit(lit[i]) && lit[i] != '.') {
				if (i < 1 && (lit[i] == '+' || lit[i] == '-'))
					continue;
				else if (i == lit.length() - 1 && lit[i] == 'f')
					continue;
				else return (INVALID);
			}
		}
		if (digitEncountered == true && lit[lit.length() - 1] == 'f')
			return (FLOAT);
		else if (digitEncountered == true)
			return (DOUBLE);
		else
			return (INVALID);
	},
	[](std::string &lit) -> literals { // Character determination.
		if (lit.length() == 1)
			return (CHARACTER);
		else return (INVALID);
	}
};

ScalarConverter::ScalarConverter(void) {
	;
}

// ScalarConverter::ScalarConverter(const ScalarConverter& copy) {
// 	;
// }

ScalarConverter::~ScalarConverter(void) {
	;
}

literals ScalarConverter::typeDetermination(std::string& literal) {
	literals	t;

	for (int i = 0; i < 3; i++) {
		t = determinerFunctions[i](literal);
		if (t != INVALID)
			return (t);
	 }
	return (INVALID);
}

void ScalarConverter::convert(std::string& data) {

	literals type = typeDetermination(data);

	// switch (type) {
	// 	case INTEGER:
	// 		break;
	// 	case CHARACTER:
	// 		break;
	// 	case FLOAT:
	// 		break;
	// 	case DOUBLE:
	// 		break;
	// 	case INVALID:
	// }
}
