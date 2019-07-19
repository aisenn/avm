#ifndef AVEXCEPTIONS_HPP
#define AVEXCEPTIONS_HPP

#include <string>
#include <exception>
#include <stdexcept>
#include <functional>
//TODO: try to inherit just form <exception>
// https://en.cppreference.com/w/cpp/error/exception

class AvmExceptions {
public:
	class DivideByZero : public std::overflow_error { char const * what( void ) const _NOEXCEPT; };
	class PopOnEmptyStack : public std::exception { char const * what( void ) const _NOEXCEPT; };
	class PrintOnEmptyStack : public std::exception { char const * what( void ) const _NOEXCEPT; };

	class InvalidValue : public std::exception { char const * what( void ) const _NOEXCEPT; };




	class BadFunction : public std::bad_function_call { char const * what( void ) const _NOEXCEPT; };

	class Overflow : public std::overflow_error {
	public:
		Overflow(const std::string &msg);
		char const * what( void ) const _NOEXCEPT;
	};
	class Underflow : public std::underflow_error {
	public:
		Underflow(const std::string &s);

	private:
		char const * what( void ) const _NOEXCEPT;
	};

	class OperandSizeException : public std::out_of_range {
	public:
		OperandSizeException(const std::string &s);
	};
};

#endif //AVEXCEPTIONS_HPP
