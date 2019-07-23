#ifndef OPERANDSFACTORY_HPP
# define OPERANDSFACTORY_HPP

# include "IOperand.hpp"

//TODO: pulymorth in factory method pattern?
// https://codereview.stackexchange.com/questions/197486/singleton-class-and-correct-way-to-access-it-in-c

# define  FACTORY OperandsFactory::instance()
//# define  FACTORY(type, val) OperandsFactory::instance().createOperand( type, value )


class OperandsFactory {
private:
	typedef IOperand const* (OperandsFactory::*fnPtr)(std::string const& value) const;
	static fnPtr method[];


//	typedef std::map<eOperandType, IOperand const* (OperandsFactory::*)(std::string const & value) const>	create;

	OperandsFactory();

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

	~OperandsFactory();

public:
	OperandsFactory(OperandsFactory const &) = delete;
	OperandsFactory &operator=(OperandsFactory const &) = delete;

	IOperand const *createOperand( eOperandType type, std::string const & value ) const;

	static OperandsFactory &instance();
};

#endif //OPERANDSFACTORY_HPP
