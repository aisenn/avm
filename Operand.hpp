#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include <sstream> //

//TODO: https://en.wikibooks.org/wiki/C_Programming/stdint.h

template <typename T>
class Operand : public IOperand {
private:
	T _value;
	std::string _strValue;

public:
	Operand();
	Operand<T>(T value);
	Operand<T>(Operand const & cp);

	Operand & operator=( Operand const & rhs );

	virtual int getPrecision( void ) const override;

/*	template<typename Type> struct type_name
	{ static eOperandType type() { throw std::invalid_argument("Unhandled type");} };

	template<> struct type_name<int8_t>  { static eOperandType type() { return INT8;	} };
	template<> struct type_name<int16_t> { static eOperandType type() { return INT16;	} };
	template<> struct type_name<int32_t> { static eOperandType type() { return INT32;	} };
	template<> struct type_name<float>   { static eOperandType type() { return FLOAT;	} };
	template<> struct type_name<double>  { static eOperandType type() { return DOUBLE;	} };*/

	eOperandType getType() const override;

	virtual IOperand const * operator+( IOperand const & rhs ) const override;
	virtual IOperand const * operator-( IOperand const & rhs ) const override;
	virtual IOperand const * operator*( IOperand const & rhs ) const override;
	virtual IOperand const * operator/( IOperand const & rhs ) const override;
	virtual IOperand const * operator%( IOperand const & rhs ) const override;

	virtual std::string const & toString( void ) const override;

	~Operand() override;
};

#endif //OPERAND_HPP
