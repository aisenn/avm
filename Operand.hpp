#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include "AvmExceptions.hpp"

template <class T>
class Operand : public IOperand {
private:
	T			_value;
	std::string	_strValue;

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

	virtual ~Operand() override {}

};

template <> eOperandType Operand<int8_t >::getType() const;
template <> eOperandType Operand<int16_t >::getType() const;
template <> eOperandType Operand<int32_t >::getType() const;
template <> eOperandType Operand<float >::getType() const;
template <> eOperandType Operand<double >::getType() const;

#endif //OPERAND_HPP
