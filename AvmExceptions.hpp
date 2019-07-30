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
	class DivideByZero : public std::exception { char const * what( void ) const _NOEXCEPT; };
	class ModuloByZero : public std::exception { char const * what( void ) const _NOEXCEPT; };
	class PopOnEmptyStack : public std::exception { char const * what( void ) const _NOEXCEPT; };
	class PrintOnEmptyStack : public std::exception { char const * what( void ) const _NOEXCEPT; };

	class UndefinedInstruction : public std::bad_function_call { char const * what( void ) const _NOEXCEPT; };

	class InvalidValue : public std::exception { char const * what( void ) const _NOEXCEPT; };


	class BadFunction : public std::bad_function_call { char const * what( void ) const _NOEXCEPT; };

	class Overflow : public std::overflow_error {
	public:
		Overflow(const std::string &msg);
		char const * what( void ) const _NOEXCEPT;
	};
	class Underflow : public std::underflow_error {
	public: Underflow(const std::string &s);

	private:
		char const * what( void ) const _NOEXCEPT;
	};

	class OutOfRange : public std::out_of_range {
		public: OutOfRange(const std::string &s);
	};

	class SyntaxError : public std::logic_error  {
		public: SyntaxError(const std::string &s);
	};

	class ExpressionError : public std::logic_error {
		public: ExpressionError(const std::string &s);
	};
};

#endif //AVEXCEPTIONS_HPP
