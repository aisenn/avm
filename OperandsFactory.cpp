#include "OperandsFactory.hpp"
#include "Operand.hpp"
#include "iostream" //

//TODO: https://stackoverflow.com/questions/199333/how-do-i-detect-unsigned-integer-multiply-overflow?page=1&tab=votes#tab-top
// https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
// https://github.com/hseos/hseos-course/blob/master/2018/03-integers/README.md

OperandsFactory::fnPtr OperandsFactory::method[] = {
		&OperandsFactory::createInt8,
		&OperandsFactory::createInt16,
		&OperandsFactory::createInt32,
		&OperandsFactory::createFloat,
		&OperandsFactory::createDouble
};

OperandsFactory::OperandsFactory() {}

OperandsFactory::~OperandsFactory() {}

/*#include <iostream>
#include <string>

int main() {

	std::string s = "10";

	try
	{
		int i = std::stoi(s);
		std::cout << i << '\n';
	}
	catch (std::invalid_argument const &e)
	{
		std::cout << "Bad input: std::invalid_argument thrown" << '\n';
	}
	catch (std::out_of_range const &e)
	{
		std::cout << "Integer overflow: std::out_of_range thrown" << '\n';
	}

	return 0;
}*/

/*#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>

int main() {

	std::string s = "10";
	int i;

	try {
		i = boost::lexical_cast<int>(s);
		std::cout << i << '\n';
	}
	catch (boost::bad_lexical_cast const &e)	// bad input
	{
		std::cout << "error" << '\n';
	}

	return 0;
}*/

IOperand const *OperandsFactory::createInt8( std::string const & value ) const {
	/*int64_t i;

	try
	{
		i = std::stoi(value);
		std::cout << i << '\n';
	}
	catch (std::invalid_argument const &e)
	{
		std::cout << "Bad input: std::invalid_argument thrown" << '\n';
	}
	catch (std::out_of_range const &e)
	{
		std::cout << "Integer overflow: std::out_of_range thrown" << '\n';
	}

	return new Operand<int8_t>(i);*/
	return new Operand<int8_t>(std::stod(value));
}

IOperand const *OperandsFactory::createInt16( std::string const & value ) const {
	return new Operand<int16_t>(std::stod(value));
}

IOperand const *OperandsFactory::createInt32( std::string const & value ) const {
	return new Operand<int32_t>(std::stod(value));
}

IOperand const *OperandsFactory::createFloat( std::string const & value ) const {
	return new Operand<float>(std::stod(value));
}

IOperand const *OperandsFactory::createDouble( std::string const & value ) const {
	return new Operand<double>(std::stod(value));
}

IOperand const *OperandsFactory::createOperand( eOperandType type, std::string const & value ) const {
	return (this->*(method[type]))(value);
}