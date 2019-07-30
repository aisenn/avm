#include "Stack.hpp"

Stack::Stack( void ) {}
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
}
