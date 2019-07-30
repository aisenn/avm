#ifndef PARSER_HPP
#define PARSER_HPP

#include "Lexer.hpp"
#include "OperandsFactory.hpp"
#include <vector>

#define  PARSER Parser::instance()

struct cmd;//

class Parser {
private:
	Parser();
	~Parser();

public:
	std::vector<cmd> cmdStack; // move to private

	Parser &operator=(Parser const &) = delete;
	Parser(Parser const &) = delete;

	static Parser &instance();

	void	commandsParsing();
};


#endif //PARSER_HPP
