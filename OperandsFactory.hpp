#ifndef OPERANDSFACTORY_HPP
#define OPERANDSFACTORY_HPP

# include "IOperand.hpp"
# include <vector>
#include <functional>

//TODO: pulymorth in factory method pattern?
// https://codereview.stackexchange.com/questions/197486/singleton-class-and-correct-way-to-access-it-in-c

# define  FACTORY OperandsFactory::instance()

class OperandsFactory {
private:
	typedef IOperand const* (OperandsFactory::*fnPtr)(std::string const& value) const;
	static fnPtr method[];

/*	static IOperand const *(OperandsFactory::*functionPointer[])(std::string const& value) const;

	typedef std::vector<std::function<IOperand const *(OperandsFactory::*)(std::string const& value) const>> arr;
	static arr m[];

	typedef IOperand const* (OperandsFactory::*pmemfunc_t)(std::string const& value) const;
	typedef std::vector<pmemfunc_t> mem_t;
	static mem_t mm[];*/

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

	static OperandsFactory &instance() {

		static OperandsFactory instance;

		return instance;
//		static OperandsFactory *instance = new OperandsFactory();

//		return *instance;
	}


};

#endif //OPERANDSFACTORY_HPP
