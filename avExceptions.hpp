#ifndef AVEXCEPTIONS_HPP
#define AVEXCEPTIONS_HPP

#include <exception>
#include <stdexcept>
#include <functional>
//TODO: try to inherit just form <exception>

class avExceptions {

	class DivideByZero : public std::overflow_error { char const * what( void ) const _NOEXCEPT; };
	class PopOnEmptyStack : public std::exception { char const * what( void ) const _NOEXCEPT; };
	class PrintOnEmptyStack : public std::exception { char const * what( void ) const _NOEXCEPT; };

	class InvalidValue : public std::exception { char const * what( void ) const _NOEXCEPT; };

	class Overflow : public std::overflow_error { char const * what( void ) const _NOEXCEPT; };
	class Underflow : public std::underflow_error { char const * what( void ) const _NOEXCEPT; };

	class BadFunction : public std::bad_function_call { char const * what( void ) const _NOEXCEPT; };

};

#endif //AVEXCEPTIONS_HPP
