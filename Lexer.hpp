#ifndef LEXER_HPP
#define LEXER_HPP

# include "IOperand.hpp"
# include "Parser.hpp"
# include <string>
# include <regex>
# include <iostream>

# define  LEXER Lexer::instance()

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
	average,
	log,
	sqrt,
	pow,
	clear,
	print,
	exit
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
	const std::regex rPow;
	const std::regex rEndOfProg;
	const std::regex rInst;

	Lexer();
	~Lexer();

	void			tokenise(std::string &line, cmd &inst) const;
	std::string		findValue(const std::string &line) const;
	eOperandType	findType(const std::string &line) const;
	void			read();
	void			read(std::string &);

public:
	Lexer(Lexer const &) = delete;
	Lexer &operator=(Lexer const &) = delete;

	static Lexer	&instance();

	void			input(int ac, char **av);
};

#endif //LEXER_HPP