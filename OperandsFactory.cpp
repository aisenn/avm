#include "OperandsFactory.hpp"
#include "Operand.hpp"


OperandsFactory::fnPtr OperandsFactory::method[] = {
		&OperandsFactory::createInt8,
		&OperandsFactory::createInt16,
		&OperandsFactory::createInt32,
		&OperandsFactory::createFloat,
		&OperandsFactory::createDouble
};

/*OperandsFactory::mem_t OperandsFactory::mm[] = {
		&OperandsFactory::createInt8,
		&OperandsFactory::createInt16,
		&OperandsFactory::createInt32,
		&OperandsFactory::createFloat,
		&OperandsFactory::createDouble
};

OperandsFactory::arr OperandsFactory::m[] = {
		&OperandsFactory::createInt8,
		&OperandsFactory::createInt16,
		&OperandsFactory::createInt32,
		&OperandsFactory::createFloat,
		&OperandsFactory::createDouble
		//'const IOperand *(OperandsFactory::*)(const std::string &) const'
		//'OperandsFactory::arr' (aka 'vector<std::function<const IOperand *(OperandsFactory::*)(const std::string &) const> >')
};

const IOperand *(OperandsFactory::*fnPtr[])(const std::string &) const = {
		&OperandsFactory::createInt8,
		&OperandsFactory::createInt16,
		&OperandsFactory::createInt32,
		&OperandsFactory::createFloat,
		&OperandsFactory::createDouble
};*/

OperandsFactory::OperandsFactory() {}

OperandsFactory::~OperandsFactory() {}

IOperand const *OperandsFactory::createInt8( std::string const & value ) const {
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