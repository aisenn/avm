#ifndef PARSER_HPP
#define PARSER_HPP

#include "Lexer.hpp"
#include <vector>

#define  PARSER Parser::instance()

struct cmd;

class Parser {
private:
	static int it;
	std::vector<cmd> _cmdStack;
	std::vector<std::vector<cmd> > _cmd;

	Parser();
	~Parser();

public:
	Parser	&operator=(Parser const &) = delete;
	Parser(Parser const &) = delete;

	static	Parser &instance();
	void	commandsParsing();

	void	setCommand(cmd &command);

	void	fdEmplase() {
		Parser::it++;
		_cmd.emplace_back(std::vector<cmd>(0));

	}
	void setCom(cmd &command) {
		_cmd[Parser::it].push_back(command);
	}
};

#endif //PARSER_HPP
