#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <stack>
# include <iterator>
# include <deque>
# include <cctype> //

#include "IOperand.hpp"
#include "OperandsFactory.hpp"
#include "OperandsFactory.hpp"
#include "AvmExceptions.hpp"
#include "Lexer.hpp"

#define  STACK Stack::instance()

class Stack : public std::stack<IOperand const *>
{
private:
	Stack();
	~Stack();

public:
	Stack(Stack const &cp) = delete;
	Stack &operator=(Stack const &rhs) = delete;

	typedef typename std::deque<IOperand const *>::iterator iterator;
	typedef typename std::deque<IOperand const *>::reverse_iterator riterator;
	iterator		begin( void );
	iterator		end( void );
	riterator		rbegin( void );
	riterator		rend( void );

	static Stack	&instance();

	void			mpush(eOperandType &type, std::string &strValue);
	void			massert(eOperandType &type, std::string &strValue);
	void			mpop();
	void			dump();
	void			add();
	void			sub();
	void			mul();
	void			div();
	void			mod();
	void			print();
	void			exit();
	void			clear();
	void			average() {
		unsigned long i = this->size();

		if ( i > 1)
		{
			while (this->size() > 1)
				this->add();
			this->push(FACTORY.createOperand(DOUBLE, std::to_string(i)));
			this->div();
		}
	}
};

#endif //STACK_HPP
