#include "ScalarConverter.hpp"

void printTypes(int i, char c, float f, double d) {
	std::cout << "char:\t";
	if (std::isnan(d) || isnanf(f) || isinf(f) || isinf(d))
		std::cout << "impossible" << std::endl;
	else if (c >= ' ' && c <= '~')
		std::cout << c << std::endl;
	else
		std::cout << "Non displayable character" << std::endl;

	if (std::isnan(d) || isnanf(f) || isinf(f) || isinf(d))
		std::cout << "int:\timpossible" << std::endl;
	else
		std::cout << "int:\t" << i << std::endl;
	std::cout << std::setprecision(1) << std::fixed << "float:\t" << f << 'f' << std::endl;
	std::cout << std::setprecision(1) << std::fixed << "double:\t" << d << std::endl;
}

void (*printFunctions[4])(const std::string& data) = {
	[](const std::string& data) { // CHARACTER.
		char	c = data[0];
		int		i = static_cast<int>(c);
		float	f = static_cast<float>(c);
		double	d = static_cast<double>(c);
		printTypes(i, c, f, d);
	},
	[](const std::string& data) { // INTEGER.
		int	convertedInt;

		try { convertedInt = std::stoi(data); }
		catch (std::invalid_argument &invalid_arg) {
			std::cout << invalid_arg.what() << std::endl;
			exit(1);
		}
		char	character = static_cast<char>(convertedInt);
		float	floatingPoint = static_cast<float>(convertedInt);
		double	doublePrecision = static_cast<double>(convertedInt);
		printTypes(convertedInt, character, floatingPoint, doublePrecision);
	},
	[](const std::string& data) { // FLOAT.
		float	convertedFloat;
		try { convertedFloat = std::stof(data); }
		catch (std::invalid_argument &invalid_arg) {
			std::cout << invalid_arg.what() << std::endl;
			exit(1);
		}
		int		integer = static_cast<int>(convertedFloat);
		char	character = static_cast<char>(convertedFloat);
		double	doublePrecision = static_cast<double>(convertedFloat);
		printTypes(integer, character, convertedFloat, doublePrecision);
	},
	[](const std::string& data) { // DOUBLE.
		double	convertedDouble;
		try { convertedDouble = std::stod(data); }
		catch (std::invalid_argument &invalid_arg) {
			std::cout << invalid_arg.what() << std::endl;
			exit(1);
		}
		int		integer = static_cast<int>(convertedDouble);
		char	character = static_cast<char>(convertedDouble);
		float	floatingPoint = static_cast<float>(convertedDouble);
		printTypes(integer, character, floatingPoint, convertedDouble);
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

ScalarConverter::ScalarConverter(const ScalarConverter& copy) {
	*this = copy;
	return ;
}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &copy) {
	(void)copy;
	return (*this);
}

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
	printFunctions[typeDetermination(data)](data);
}
