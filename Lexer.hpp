#ifndef LEXER_HPP
#define LEXER_HPP

#include "IOperand.hpp"
#include "string"//

enum eInstructions {
	push,
	pop,
	dump,
	assert,
	add,
	subtract,
	multiply,
	divide,
	modulo,
	print,
//	exit,
	top,
	swap,
	peek,
	average
};

struct cmd {
	eInstructions	inst;
	eOperandType	type;
	std::string		value;
};

class Lexer
{
private:
	Lexer();
	~Lexer();

public:
	Lexer(Lexer const &) = delete;
	Lexer &operator=(Lexer const &) = delete;

	static Lexer &instance();
};


#endif //LEXER_HPP
