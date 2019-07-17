#include "avExceptions.hpp"

char const * avExceptions::DivideByZero::what( void ) const _NOEXCEPT {
	return "Divide by zero exception";
}

char const * avExceptions::PopOnEmptyStack::what( void ) const _NOEXCEPT {
	return "Pop on empty stack";
}

char const * avExceptions::PrintOnEmptyStack::what( void ) const _NOEXCEPT {
	return "Print on empty stack";
}

char const * avExceptions::InvalidValue::what( void ) const _NOEXCEPT {
	return "Invalid value";
}

char const * avExceptions::Overflow::what( void ) const _NOEXCEPT {
	return "Overflow";
}

char const * avExceptions::Underflow::what( void ) const _NOEXCEPT {
	return "Underflow";
}

char const * avExceptions::BadFunction::what( void ) const _NOEXCEPT {
	return "Bad function call";
}