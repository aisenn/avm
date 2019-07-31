#include "Operand.hpp"
#include "OperandsFactory.hpp"
#include <sstream>
#include <cmath>

// TODO: https://www.codeproject.com/Questions/895846/Cplusplus-template-specialization-for-several-type

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

//template<class T> eOperandType	getType( void )  { return Operand<T>::getType(); }

template<class T>
IOperand const * Operand<T>::operator+( IOperand const & rhs ) const {
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs + *this);
	T lhsValue = static_cast<T>(this->_value);
	T rhsValue = static_cast<T>(std::stod(rhs.toString()));
	std::string res = std::to_string(lhsValue + rhsValue);

	return (FACTORY.createOperand(this->getType(), res));
}

template<class T>
IOperand const * Operand<T>::operator-( IOperand const & rhs ) const {
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs - *this);
	T lhs_value = static_cast<T>(this->_value);
	T rhs_value = static_cast<T>(std::stod(rhs.toString()));
	std::string res = std::to_string(lhs_value - rhs_value);

	return (FACTORY.createOperand(this->getType(), res));
}

template<class T>
IOperand const * Operand<T>::operator*( IOperand const & rhs ) const {
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs * *this);
	T lhs_value = static_cast<T>(this->_value);
	T rhs_value = static_cast<T>(std::stod(rhs.toString()));
	std::string res = std::to_string(lhs_value * rhs_value);

	return (FACTORY.createOperand(this->getType(), res));
}

template<class T>
IOperand const * Operand<T>::operator/( IOperand const & rhs ) const {
	if (rhs.toString() == "0") //TODO: overload comparison operator ???
		throw (AvmExceptions::DivideByZero());
	if (this->getPrecision() < rhs.getPrecision())
		return *FACTORY.createOperand(rhs.getType(), this->_strValue) / rhs;
	T lhs_value = static_cast<T>(this->_value);
	T rhs_value = static_cast<T>(std::stod(rhs.toString()));
	std::string res = std::to_string(lhs_value / rhs_value);

	return (FACTORY.createOperand(this->getType(), res));
}

/*template <class T>
IOperand const * operator/(T lhs, IOperand const & rhs) {
	T rhs_value = static_cast<T>(std::stod(rhs.toString()));
	std::string res = std::to_string(lhs / rhs_value);


	return (FACTORY.createOperand(getType(), res));
}*/

template<class T>
IOperand const * Operand<T>::operator%( IOperand const & rhs ) const {
	if (rhs.toString() == "0") //TODO: overload comparison operator ???
		throw (AvmExceptions::ModuloByZero());
	if (this->getPrecision() < rhs.getPrecision())
		return *FACTORY.createOperand(rhs.getType(), this->_strValue) % rhs;
	T lhs_value = static_cast<T>(this->_value);
	T rhs_value = static_cast<T>(std::stod(rhs.toString()));
	std::string res = std::to_string(std::fmod(lhs_value, rhs_value));

	return (FACTORY.createOperand(this->getType(), res));
}
