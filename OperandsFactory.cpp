#include "OperandsFactory.hpp"
#include "Operand.hpp"
#include "iostream" //
#include <cmath>//

#include "AvmExceptions.hpp"

//TODO: https://stackoverflow.com/questions/199333/how-do-i-detect-unsigned-integer-multiply-overflow?page=1&tab=votes#tab-top
// https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
// https://github.com/hseos/hseos-course/blob/master/2018/03-integers/README.md

OperandsFactory::OperandsFactory() {}

OperandsFactory::fnPtr OperandsFactory::method[] = {
		&OperandsFactory::createInt8,
		&OperandsFactory::createInt16,
		&OperandsFactory::createInt32,
		&OperandsFactory::createFloat,
		&OperandsFactory::createDouble
};

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

// TODO: something better
template <typename T> std::string type()	{ return "Undefined"; }
template <> std::string type<int8_t >()		{ return "int8_t";	}
template <> std::string type<int16_t >()	{ return "int16_t";	}
template <> std::string type<int32_t >()	{ return "int32_t";	}
template <> std::string type<float >()		{ return "float";	}
template <> std::string type<double >()		{ return "double";	}

template <typename T>
T operandSizeCheck(std::string const & value) {
	try
	{
		long double val = std::stold(value);
		if (val > std::numeric_limits<T>::max())
			throw AvmExceptions::Overflow(type<T>());
		else if (val < std::numeric_limits<T>::min())
			throw AvmExceptions::Underflow(type<T>());
		else if (!std::isnormal(val))
			throw AvmExceptions::InvalidValue();
		return val;
	}
	catch(const std::exception& e)
	{
		std::string msg = value + " is out of " + type<T>() + " range";
		throw AvmExceptions::OutOfRange(msg);
	}
}
// TODO: END something better


IOperand const *OperandsFactory::createInt8( std::string const & value ) const {
	int64_t val = operandSizeCheck<int8_t>(value);
	return new Operand<int8_t>(static_cast<int8_t >(val));
}

IOperand const *OperandsFactory::createInt16( std::string const & value ) const {
	int64_t val = operandSizeCheck<int16_t>(value);
	return new Operand<int16_t>(static_cast<int16_t >(val));
}

IOperand const *OperandsFactory::createInt32( std::string const & value ) const {
	int64_t val = operandSizeCheck<int32_t>(value);
	return new Operand<int32_t>(static_cast<int32_t >(val));
}

// TODO: thow stof, stod exception

IOperand const *OperandsFactory::createFloat( std::string const & value ) const {
	float val = operandSizeCheck<float>(value);
	return new Operand<float>(val);
}

IOperand const *OperandsFactory::createDouble( std::string const & value ) const {
	double val = operandSizeCheck<double>(value);
	return new Operand<double>(val);
}

IOperand const *OperandsFactory::createOperand( eOperandType type, std::string const & value ) const {
	if (type < INT8 || type > DOUBLE)
		throw AvmExceptions::BadFunction();
	return (this->*(method[type]))(value);
}