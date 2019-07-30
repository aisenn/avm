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
public:
	Stack();
	Stack(Stack const &cp);
	~Stack();

	Stack &operator=(Stack const &rhs);

	typedef typename std::deque<IOperand const *>::iterator iterator;
	iterator begin( void );
	iterator end( void );

	static Stack &instance();

	/*template <typename T>
	void push(cmd &it) {

//		push(FACTORY.createOperand(it.type, it.value));
	}*/

	void dump() {
		for (Stack dump = STACK; !dump.empty(); dump.pop())
			std::cout << dump.top()->toString() << std::endl;

/*		auto end = this->end();
		for (auto i = this->begin(); i !=  end; i++)
			std::cout << (*i)->toString() << std::endl; */
	}

	void add() {
		if (this->size() < 2)
			throw (AvmExceptions::ExpressionError("addition"));
		const IOperand *lhs = this->top();
		this->pop();
		const IOperand *rhs = this->top();
		this->pop();

		this->push(*lhs + *rhs);
	}

	void sub() {
		if (this->size() < 2)
			throw (AvmExceptions::ExpressionError("subtract"));
		const IOperand *lhs = this->top();
		this->pop();
		const IOperand *rhs = this->top();
		this->pop();

		this->push(*lhs - *rhs);
	}

	void mul() {
		if (this->size() < 2)
			throw (AvmExceptions::ExpressionError("multiply"));
		const IOperand *lhs = this->top();
		this->pop();
		const IOperand *rhs = this->top();
		this->pop();

		this->push(*lhs * *rhs);
	}

	void div() {
		if (this->size() < 2)
			throw (AvmExceptions::ExpressionError("divide"));
		const IOperand *lhs = this->top();
		this->pop();
		const IOperand *rhs = this->top();
		this->pop();

		this->push(*lhs / *rhs);
	}

	void mod() {
		if (this->size() < 2)
			throw (AvmExceptions::ExpressionError("addition"));
		const IOperand *lhs = this->top();
		this->pop();
		const IOperand *rhs = this->top();
		this->pop();

		this->push(*lhs % *rhs);
	}

	void print() {
		if (this->empty())
			throw (AvmExceptions::PrintOnEmptyStack());
		if (this->top()->getType() != INT8)
			throw (AvmExceptions::InvalidValue());
		char c = static_cast<char>(std::stoi(top()->toString()));
		if (std::isspace(c) || !std::isprint(c))
			std::cout << "'" << c << "' unprintable char " << top()->toString() << std::endl;
		else
			std::cout << c << std::endl;
	}


};


/*Stack::Stack( void ) {}
Stack::Stack( Stack const & obj ) { *this = obj; }
Stack::~Stack( void ) {}

Stack &Stack::operator=( Stack const & rhs ) {
	if (this != &rhs)
		this->std::stack<IOperand const *>::operator=(rhs);
//		this->c = rhs.c;
	return *this;
}

Stack::iterator Stack::begin( void ) {
	return this->c.begin();
}
Stack::iterator Stack::end( void ) {
	return this->c.end();
}

Stack &Stack::instance() {
	static Stack instance;
	return instance;
}*/
//************************************************************************
//************************************************************************
//************************************************************************

// template <class T> class MutantStack : public std::stack< T, std::deque<T> > {
template <class T>
class iterStack : public std::stack<T> {
public:
	iterStack( void );
	iterStack( iterStack const & obj );
	~iterStack( void );
	iterStack & operator=( iterStack const & rhs );

	typedef typename std::deque<T>::iterator iterator;
	iterStack<T>::iterator begin( void );
	iterStack<T>::iterator end( void );
protected:

private:

};


template <class T> iterStack<T>::iterStack( void ) {}
template <class T> iterStack<T>::iterStack( iterStack<T> const & obj ) { *this = obj; }
template <class T> iterStack<T>::~iterStack( void ) {}
template <class T> iterStack<T> & iterStack<T>::operator=( iterStack<T> const & rhs ) {
	this->std::stack<T>::operator=(rhs);
	return *this;
}
template <class T> typename iterStack<T>::iterator iterStack<T>::begin( void ) {
	return this->c.begin();
}
template <class T> typename iterStack<T>::iterator iterStack<T>::end( void ) {
	return this->c.end();
}

/*template <class T>
class Stack : public std::stack<T>
{
public:
	Stack();
	Stack(Stack const &cp);
	~Stack();

	Stack &operator=(Stack const &rhs);

	typedef typename std::deque<T>::iterator iterator;
	Stack<T>::iterator begin( void );
	Stack<T>::iterator end( void );

	static Stack &instance();
};

template <class T> Stack<T>::Stack( void ) {}
template <class T> Stack<T>::Stack( Stack<T> const & obj ) { *this = obj; }
template <class T> Stack<T>::~Stack( void ) {}

template <class T>
Stack<T> &Stack<T>::operator=( Stack<T> const & rhs ) {
	if (this != &rhs)
		this->std::stack<T>::operator=(rhs);
//		this->c = rhs.c;
	return *this;
}

template <class T> typename Stack<T>::iterator Stack<T>::begin( void ) {
	return this->c.begin();
}
template <class T> typename Stack<T>::iterator Stack<T>::end( void ) {
	return this->c.end();
}

template <class T> Stack<T> &Stack<T>::instance() {
	static Stack<IOperand const *> instance;
	return instance;
}*/

#endif //STACK_HPP
