#ifndef PARSER_HPP
#define PARSER_HPP

#include "Lexer.hpp"
#include <vector>
#include <deque>

#define  PARSER Parser::instance()

struct cmd;

class Parser {
private:
	static int fd;
	std::vector<std::vector<cmd> >	_cmdStack;
	std::deque<std::string>			_names;

	Parser();
	~Parser();

public:
	Parser	&operator=(Parser const &) = delete;
	Parser(Parser const &) = delete;

	static	Parser &instance();
	void	commandsParsing();

	void	fdEmplase(std::string &name) {
		Parser::fd++;
		_cmdStack.emplace_back(std::vector<cmd>(0));
		_names.push_back(name);
	}
	void	setCommand(cmd &command);
};

#endif //PARSER_HPP
