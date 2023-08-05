#include "ScalarConverter.hpp"
#include <cctype>
#include <iostream>

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
	for (int i = 0; i < 3; i++) {
		t = determinerFunctions[i](literal);
		if (t != INVALID)
			return (t);
	}
	return (INVALID);
}

void ScalarConverter::convert(std::string& data) {
	literals type = typeDetermination(data);
	if (type == DOUBLE)
		std::cout << "DOUBLE" << std::endl;
	else if (type == FLOAT)
		std::cout << "FLOAT" << std::endl;
	else if (type == CHARACTER)
		std::cout << "CHAR" << std::endl;
	else if (type == INTEGER)
		std::cout << "INTEGER" << std::endl;
	else
		std::cout << "INVALID" << std::endl;
}
