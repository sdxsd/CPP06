#ifndef SCALARCONVERTER_H
#define SCALARCONVERTER_H

#include <string>

enum literals {
	CHARACTER,
	INTEGER,
	FLOAT,
	DOUBLE,
	INVALID,
};

class ScalarConverter {
	private:
		void printTypes(int integer, char character, float floatingPoint, double doublePrecision);
		static literals typeDetermination(std::string &data);
	public:
		ScalarConverter(void);
		ScalarConverter(const ScalarConverter& copy);
		~ScalarConverter(void);
		static void	convert(std::string &data);
};

#endif // SCALARCONVERTER_H
