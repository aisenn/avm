#include "Operand.hpp"
#include "OperandsFactory.hpp"

//TODO: add, mull etc. underflow and overflow handling
// div, mod to 0 exception

template<> Operand<int8_t>::Operand(int8_t value) : _value(value) {
	std::stringstream ss;
	ss << static_cast<int16_t>(this->_value);
	_strValue = ss.str();
}
template<> Operand<int16_t >::Operand(int16_t value) : _value(value) {
	std::stringstream ss;
	ss << this->_value;
	_strValue = ss.str();
}
template<> Operand<int32_t >::Operand(int32_t value) : _value(value) {
	std::stringstream ss;
	ss << this->_value;
	_strValue = ss.str();
}
template<> Operand<float >::Operand(float value) : _value(value) {
	std::stringstream ss;
	ss << this->_value;
	_strValue = ss.str();
}
template<> Operand<double >::Operand(double value) : _value(value) {
	std::stringstream ss;
	ss << this->_value;
	_strValue = ss.str();
}

template<class T> Operand<T>::Operand(Operand const & cp) {
	*this = cp;
}

template<class T> Operand<T> & Operand<T>::operator=( Operand<T> const & rhs ) {
	if (this != &rhs) {
		this->_value = rhs._value;
		this->_strValue = rhs._strValue;
	}
	return *this;
}

template<> eOperandType	Operand<int8_t>::getType( void ) const  { return INT8;   }
template<> eOperandType	Operand<int16_t>::getType( void ) const { return INT16;  }
template<> eOperandType	Operand<int32_t>::getType( void ) const { return INT32;  }
template<> eOperandType	Operand<float>::getType( void ) const   { return FLOAT;  }
template<> eOperandType	Operand<double>::getType( void ) const  { return DOUBLE; }

template<class T>
IOperand const * Operand<T>::operator+( IOperand const & rhs ) const {
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs + *this);
	T lhsValue = static_cast<T>(this->_value);
	T rhsValue = static_cast<T>(std::stod(rhs.toString()));
//	flow_check<T>(lhsValue, rhsValue);

	std::string res = std::to_string(lhsValue + rhsValue);

	return (FACTORY.createOperand(this->getType(), res));
}

template<class T>
IOperand const * Operand<T>::operator-( IOperand const & rhs ) const {
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs - *this);
	T lhs_value = static_cast<T>(this->_value);
	T rhs_value = static_cast<T>(std::stod(rhs.toString()));
	std::string res = std::to_string(lhs_value + rhs_value);

	return (FACTORY.createOperand(this->getType(), res));
}

template<class T>
IOperand const * Operand<T>::operator*( IOperand const & rhs ) const {
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs * *this);
	T lhs_value = static_cast<T>(this->_value);
	T rhs_value = static_cast<T>(std::stod(rhs.toString()));
	std::string res = std::to_string(lhs_value + rhs_value);

	return (FACTORY.createOperand(this->getType(), res));
}

template<class T>
IOperand const * Operand<T>::operator/( IOperand const & rhs ) const {
	return 0;
}

template<class T>
IOperand const * Operand<T>::operator%( IOperand const & rhs ) const {
	return 0;
}
