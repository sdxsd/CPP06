#include "ScalarConverter.hpp"
#include <limits>

// Array of lambda functions for usage in type determination.
// Why? Lambda function arrays seemed cool.
literals (*determinerFunctions[3])(const std::string &lit) = {
	[](const std::string &lit) -> literals { // Integer determination.
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
	[](const std::string &lit) -> literals { // Double & float determination.
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
	[](const std::string &lit) -> literals { // Character determination.
		if (lit.length() == 1)
			return (CHARACTER);
		else return (INVALID);
	}
};

void printTypes(int i, char c, float f, double d, const std::string &data) {
	std::cout << "char:\t";
	if (std::isnan(d) || isnanf(f) || isinf(f) || isinf(d))
		std::cout << "impossible" << std::endl;
	else if (d >= ' ' && d <= '~')
		std::cout << '\'' << c << '\'' << std::endl;
	else
		std::cout << "Non displayable character" << std::endl;
	if (determinerFunctions[2](data) != CHARACTER && (std::stod(data) > std::numeric_limits<int>::max() || std::stod(data) < std::numeric_limits<int>::min()))
		std::cout << "int:\toverflow" << std::endl;
	else if (std::isnan(d) || isnanf(f) || isinf(f) || isinf(d))
		std::cout << "int:\timpossible" << std::endl;
	else
		std::cout << "int:\t" << i << std::endl;
	std::cout << std::setprecision(1) << std::fixed << "float:\t" << f << 'f' << std::endl;
	std::cout << std::setprecision(1) << std::fixed << "double:\t" << d << std::endl;
}

void (*printFunctions[5])(const std::string& data) = {
	[](const std::string& data) { // CHARACTER.
		char	c = data[0];
		int		i = static_cast<int>(c);
		float	f = static_cast<float>(c);
		double	d = static_cast<double>(c);
		printTypes(i, c, f, d, data);
	},
	[](const std::string& data) { // INTEGER.
		int	convertedInt;
		try { convertedInt = std::stoi(data); }
		catch (std::out_of_range &oor) {
			std::cout << "Failed to convert argument to integer: (out of range)" << std::endl;
			exit(1);
		}
		char	character = static_cast<char>(convertedInt);
		float	floatingPoint = static_cast<float>(convertedInt);
		double	doublePrecision = static_cast<double>(convertedInt);
		printTypes(convertedInt, character, floatingPoint, doublePrecision, data);
	},
	[](const std::string& data) { // FLOAT.
		float	convertedFloat;
		try { convertedFloat = std::stof(data); }
		catch (std::out_of_range &oor) {
			std::cout << "Failed to convert argument to float: (out of range)" << std::endl;
			exit(1);
		}
		int		integer = static_cast<int>(convertedFloat);
		char	character = static_cast<char>(convertedFloat);
		double	doublePrecision = static_cast<double>(convertedFloat);
		printTypes(integer, character, convertedFloat, doublePrecision, data);
	},
	[](const std::string& data) { // DOUBLE.
		double	convertedDouble;
		try { convertedDouble = std::stod(data); }
		catch (std::out_of_range &oor) {
			std::cout << "Failed to convert argument to double: (out of range)" << std::endl;
			exit(1);
		}
		int		integer = static_cast<int>(convertedDouble);
		char	character = static_cast<char>(convertedDouble);
		float	floatingPoint = static_cast<float>(convertedDouble);
		printTypes(integer, character, floatingPoint, convertedDouble, data);
	},
	[](const std::string& data) {
		std::cout << "Invalid argument: " << data << std::endl;
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
