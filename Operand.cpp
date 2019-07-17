#include "Operand.hpp"
#include "OperandsFactory.hpp"

template<class T> Operand<T>::Operand() {}

template<class T> Operand<T>::Operand(T value) : _value(value) {
	std::stringstream ss;
	ss << this->_value;
	_strValue = ss.str();
}

template<> Operand<int8_t>::Operand(int8_t value) : _value(value) {
	std::stringstream ss;
	ss << static_cast<int16_t>(this->_value);
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

template<class T>
int Operand<T>::getPrecision( void ) const {
	return getType();
}

//TODO: handel exeption to undefined type
//template<typename Type> eOperandType	Operand<Type>::getType( void ) const  { return INT8;   }
template<typename T> eOperandType	Operand<T>::getType( void ) const  { return DOUBLE;   }

template<> eOperandType	Operand<int8_t>::getType( void ) const  { return INT8;   }
template<> eOperandType	Operand<int16_t>::getType( void ) const { return INT16;  }
template<> eOperandType	Operand<int32_t>::getType( void ) const { return INT32;  }
template<> eOperandType	Operand<float>::getType( void ) const   { return FLOAT;  }
template<> eOperandType	Operand<double>::getType( void ) const  { return DOUBLE; }

//template<> int			Operand<int8_t>::getPrecision( void ) const		{ return INT8; }
//template<> int			Operand<int16_t>::getPrecision( void ) const	{ return INT16; }
//template<> int			Operand<int32_t>::getPrecision( void ) const	{ return INT32; }
//template<> int			Operand<float>::getPrecision( void ) const		{ return FLOAT; }
//template<> int			Operand<double>::getPrecision( void ) const		{ return DOUBLE; }

template<class T>
IOperand const * Operand<T>::operator+( IOperand const & rhs ) const {
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs + *this);
	T lhs_value = static_cast<T>(this->_value);
	T rhs_value = static_cast<T>(std::stod(rhs.toString()));
//	add_flow_check<T>(lhs_value, rhs_value);

//	IOperand const * ret_val = OperandsFactory::instance()
//			.createOperand(this->getType(), std::to_string(static_cast<T>(this->_value) + rhs_value));
	std::string res = std::to_string(lhs_value + rhs_value);

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

}

template<class T>
IOperand const * Operand<T>::operator%( IOperand const & rhs ) const {

}


template<class T>
std::string const &Operand<T>::toString( void ) const {
	return this->_strValue;
}

template<class T>
Operand<T>::~Operand() {}

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;

