#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include <sstream> //
#include "AvmExceptions.hpp"

//TODO: https://en.wikibooks.org/wiki/C_Programming/stdint.h

template <class T>
class Operand : public IOperand {
private:
	T _value;
	std::string _strValue;
	Operand() {
		throw(AvmExceptions::InvalidValue());
	}

public:
	Operand(T value) {
		throw(AvmExceptions::InvalidValue());
	}
	Operand(Operand const & cp);

	Operand & operator=( Operand const & rhs );

	int getPrecision( void ) const override {
		return getType();
	}

	eOperandType getType() const override {
		throw(AvmExceptions::InvalidValue());
	}

	virtual IOperand const * operator+( IOperand const & rhs ) const override;
	virtual IOperand const * operator-( IOperand const & rhs ) const override;
	virtual IOperand const * operator*( IOperand const & rhs ) const override;
	virtual IOperand const * operator/( IOperand const & rhs ) const override;
	virtual IOperand const * operator%( IOperand const & rhs ) const override;

	virtual std::string const & toString( void ) const override {
		return this->_strValue;
	}

	~Operand() override {}
};

template <> eOperandType Operand<int8_t >::getType() const;
template <> eOperandType Operand<int16_t >::getType() const;
template <> eOperandType Operand<int32_t >::getType() const;
template <> eOperandType Operand<float >::getType() const;
template <> eOperandType Operand<double >::getType() const;


/*template<> Operand<int8_t>::Operand(int8_t value);
template<> Operand<int16_t>::Operand(int16_t value);
template<> Operand<int32_t>::Operand(int32_t value);
template<> Operand<float>::Operand(float value);
template<> Operand<double>::Operand(double value);*/

/*template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;*/
#endif //OPERAND_HPP
