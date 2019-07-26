#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <stack>
# include <iterator>

#include "IOperand.hpp"
#include "OperandsFactory.hpp"
#include "OperandsFactory.hpp"

#define  STACK Stack::instance()

template <class T>
class Stack : public std::stack<T>
{
public:
	Stack() {}
	Stack(Stack const &cp) {
		*this = cp;
	}
	~Stack() {}

	Stack &operator=(Stack const &rhs) {
		if (this != &rhs)
			this->c = rhs.c;
		return *this;
	}

	typedef typename std::stack<T>::container_type::const_iterator iterator;

	iterator begin() {
		return this->c.begin();
	}
	iterator end() {
		return this->c.end();
	}

	static Stack &instance() {
		static Stack<IOperand const *> instance;
		return instance;
	}
};

//************************************************************************
//************************************************************************
//************************************************************************

// template <class T> class MutantStack : public std::stack< T, std::deque<T> > {
template <class T>
class iterStack : public std::stack<T> {
public:
	typedef typename std::deque<T>::iterator iterator;
	iterStack( void );
	iterStack( iterStack const & obj );
	~iterStack( void );
	iterStack & operator=( iterStack const & rhs );

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
#endif //STACK_HPP
