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
};

#endif //STACK_HPP
