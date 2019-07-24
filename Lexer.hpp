#ifndef LEXER_HPP
#define LEXER_HPP

#include "IOperand.hpp"
#include "string"//
#include <vector>

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
	average,
	comment
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
	std::vector<cmd> cmdStack;//or just send a token

	Lexer(Lexer const &) = delete;
	Lexer &operator=(Lexer const &) = delete;

	static Lexer &instance();

	void input(int ac, char **av);
	void read();
	void read(char *);
};


#endif //LEXER_HPP
