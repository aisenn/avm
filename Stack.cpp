#include "Stack.hpp"

//**********************************************
//*          CONSTRUCTOR / DESTRUCTOR          *
//**********************************************
Stack::Stack( void ) {}
Stack::~Stack( void ) {
	auto rend = this->rend();
	for (auto rit = this->rbegin(); rit != rend; rit++)
		delete *rit;
}

//**********************************************
//*                 ITERATORS                  *
//**********************************************
Stack::iterator Stack::begin( void ) {
	return this->c.begin();
}

Stack::iterator Stack::end( void ) {
	return this->c.end();
}

Stack::riterator Stack::rbegin( void ) {
	return this->c.rbegin();
}

Stack::riterator Stack::rend( void ) {
	return this->c.rend();
}

//**********************************************
//*              INSTANCE GETTER               *
//**********************************************
Stack &Stack::instance() {
	static Stack instance;
	return instance;
}

//**********************************************
//*          PUBLIC MEMBER FUNCTIONS           *
//**********************************************
void Stack::mpop() {
	if (this->c.empty())
		throw AvmExceptions::PopOnEmptyStack();
	std::unique_ptr<const IOperand> lhs(this->top());
	this->pop();
}

void Stack::mpush(eOperandType &type, std::string &strValue) {
	STACK.push(FACTORY.createOperand(type, strValue));
}

void Stack::massert(eOperandType &type, std::string &strValue) {
	if (this->top()->getType() != type || this->top()->toString() != strValue)
		throw (AvmExceptions::AssertError());
}

void Stack::dump() {
	auto rend = this->rend();
	for (auto rit = this->rbegin(); rit != rend; rit++)
		std::cout << (*rit)->toString() << std::endl;
}

void Stack::add() {
	if (this->size() < 2)
		throw (AvmExceptions::ExpressionError("addition"));
	std::unique_ptr<const IOperand> lhs(this->top());
	this->pop();
	std::unique_ptr<const IOperand> rhs(this->top());
	this->pop();

	this->push(*lhs + *rhs);
}

void Stack::sub() {
	if (this->size() < 2)
		throw (AvmExceptions::ExpressionError("subtract"));
	std::unique_ptr<const IOperand> lhs(this->top());
	this->pop();
	std::unique_ptr<const IOperand> rhs(this->top());
	this->pop();

	this->push(*rhs - *lhs);
}

void Stack::mul() {
	if (this->size() < 2)
		throw (AvmExceptions::ExpressionError("multiply"));
	std::unique_ptr<const IOperand> lhs(this->top());
	this->pop();
	std::unique_ptr<const IOperand> rhs(this->top());
	this->pop();

	this->push(*lhs * *rhs);
}

void Stack::div() {
	if (this->size() < 2)
		throw (AvmExceptions::ExpressionError("divide"));
	std::unique_ptr<const IOperand> lhs(this->top());
	this->pop();
	std::unique_ptr<const IOperand> rhs(this->top());
	this->pop();

	this->push(*rhs / *lhs);
}

void Stack::mod() {
	if (this->size() < 2)
		throw (AvmExceptions::ExpressionError("addition"));
	std::unique_ptr<const IOperand> lhs(this->top());
	this->pop();
	std::unique_ptr<const IOperand> rhs(this->top());
	this->pop();

	this->push(*rhs % *lhs);
}

void Stack::print() {
	if (this->empty())
		throw (AvmExceptions::PrintOnEmptyStack());
	if (this->top()->getType() != INT8)
		throw (AvmExceptions::ExceptionString("Printing invalid value"));
	char c = static_cast<char>(std::stoi(top()->toString()));
	if (std::isspace(c) || !std::isprint(c))
		std::cout << "'" << c << "' unprintable char " << top()->toString() << std::endl;
	else
		std::cout << c << std::endl;
}

void Stack::exit() {
	this->dump();
	system("leaks avm"); //TODO: delete
	std::exit(0);
}

void Stack::clear() {
	Stack().swap(STACK);
}