#ifndef LEXER_HPP
#define LEXER_HPP

#include "IOperand.hpp"
#include "Parser.hpp"
#include <string>
#include <regex>
#include <iostream>

#define  LEXER Lexer::instance()

enum class eInst {
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
	exit,
	swap,
	average,
	comment
};

struct cmd {
	eInst			inst;
	eOperandType	type;
	std::string		value;
};

class Lexer
{
private:
	const std::regex rPush;
	const std::regex rAssert;
	const std::regex rType;
	const std::regex rDigit;
	const std::regex rPop;
	const std::regex rDump;
	const std::regex rAdd;
	const std::regex rSub;
	const std::regex rMul;
	const std::regex rDiv;
	const std::regex rMod;
	const std::regex rPrint;
	const std::regex rExit;
	const std::regex rInst;
	const std::regex rEndOfProg;

	Lexer();
	~Lexer();

public:
	Lexer(Lexer const &) = delete;
	Lexer &operator=(Lexer const &) = delete;

	static Lexer	&instance();

	void			input(int ac, char **av);
	void			read();
	void			read(std::string &);

	void			tokenise(std::string &line, cmd &inst) const;
	std::string		findValue(const std::string &line) const;
	eOperandType	findType(const std::string &line) const;
};


#endif //LEXER_HPP
