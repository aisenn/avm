#ifndef PARSER_HPP
#define PARSER_HPP

#include "Lexer.hpp"
#include "OperandsFactory.hpp"
#include <vector>

#define  PARSER Parser::instance()

struct cmd;//

class Parser {
private:
	std::vector<cmd> _cmdStack;

	Parser();
	~Parser();

public:
	Parser	&operator=(Parser const &) = delete;
	Parser(Parser const &) = delete;

	static	Parser &instance();
	void	commandsParsing();

	void	setCommand(cmd &command);
};

#endif //PARSER_HPP
