#include "AvmExceptions.hpp"

//AvmExceptions::AvmExceptions(const char* msg) : _msg(msg) {}

char const * AvmExceptions::DivideByZero::what( void ) const _NOEXCEPT {
	return "Divide by zero exception";
}

char const * AvmExceptions::PopOnEmptyStack::what( void ) const _NOEXCEPT {
	return "Pop on empty stack";
}

char const * AvmExceptions::PrintOnEmptyStack::what( void ) const _NOEXCEPT {
	return "Print on empty stack";
}

char const * AvmExceptions::InvalidValue::what( void ) const _NOEXCEPT {
	return "Invalid value";
}

AvmExceptions::Overflow::Overflow(const std::string &msg) : overflow_error(msg) {}
char const * AvmExceptions::Overflow::what( void ) const _NOEXCEPT {
	return "Overflow";
}

AvmExceptions::Underflow::Underflow(const std::string &s) : underflow_error(s) {}
char const * AvmExceptions::Underflow::what( void ) const _NOEXCEPT {
	return "Underflow";
}


char const * AvmExceptions::BadFunction::what( void ) const _NOEXCEPT {
	return "Bad function call";
}

AvmExceptions::OutOfRange::OutOfRange(const std::string &s) : out_of_range(s) {}

AvmExceptions::SyntaxError::SyntaxError(const std::string &s) : logic_error("Syntax error at: " + s) {}