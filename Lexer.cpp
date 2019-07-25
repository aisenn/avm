#include "Lexer.hpp"
#include "AvmExceptions.hpp"
#include <iostream>
#include <fstream>
#include <regex>

//TODO: https://solarianprogrammer.com/2011/10/12/cpp-11-regex-tutorial/

Lexer::Lexer() : cmdStack() {}
Lexer::~Lexer() {}

Lexer &Lexer::instance() {
	static Lexer instance;
	return instance;
}

/*std::map<std::string, TokenType> Lexer::_patternMap =
{
		{"(int(8|16|32)\\(([-]?[0-9]+)\\))|(((double|float)\\(([-]?[0-9]+\\.[0-9]+)\\)))", TokenType::VALUE},
		{"and|or|pop|dump|add|sub|mul|div|mod|exit|print", TokenType::ACTION},
		{"push|assert", TokenType::INSTR}
};*/

// TODO: throw ex when more the one match?

std::string findValue(const std::string &line) {
/*
	std::regex words_regex("\\((\\d+)\\)");
	std::regex r("(\\+|-)?[[:digit:]]+");

	for(std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), r);
		i != std::sregex_iterator();
		++i)
	{
		std::smatch m = *i;
		std::cout << m[1].str();
//		return m[1].str();
	}*/
	std::regex	r("\\((\\+|-)?[[:digit:]]+\\)");
	auto		wBegin = std::sregex_iterator(line.begin(), line.end(), r);
	auto		wEnd = std::sregex_iterator();

	if (std::distance(wBegin, wEnd) > 1)
		throw(AvmExceptions::SyntaxError(line));
//	std::smatch match = (*wBegin).str();
	return (*wBegin).str();
}

cmd tokenise(std::string &line) {
	std::regex r("(push|assert)( |\t)(int(8|16|32)\\(([-]?[0-9]+)\\))|(((double|float)\\(([-]?[0-9]+\\.[0-9]+)\\)))");
	std::regex action("and|or|pop|dump|add|sub|mul|div|mod|exit|print");
	std::regex inst("push|assert");

	std::cmatch m;
	if (std::regex_match(line.c_str(), r)) {
		std::cout << "ERROR: " << std::endl;
	}
	else if (std::regex_match(line.c_str(), action)) {
		std::cout << "ERROR: " << std::endl;
	}
	else if (std::regex_match(line.c_str(), inst)) {
		std::cout << "ERROR: " << std::endl;
	}
	else {
		throw(AvmExceptions::SyntaxError(line));
	}
	return (cmd){}; //
}


void Lexer::read()
{
	std::string line;
	cmd instr;
	while (!std::getline(std::cin, line).eof()) {

		if (line == ";;")
			break;
		size_t column = line.find(';');
		if (column != std::string::npos)
			line.erase(column);
		if (line.empty())
			continue;
		try {

			findValue(line);
		}
		catch (std::exception &e) {
			std::cout << "ERROR: " << e.what() << std::endl;
			continue;
		}
		if (instr.inst != comment)
			cmdStack.push_back(instr);
	}
}

void Lexer::read(char *fileName)
{
	std::ifstream someVarName(fileName);

	std::string line;
	cmd instr;
	while (std::getline(someVarName, line)) {
		size_t column = line.find(';');
		if (column != std::string::npos)
			line.erase(column);
		if (line.empty())
			continue;
		try {
			tokenise(line);
//			findValue(line);
		}
		catch (std::exception &e) {
			std::cout << "ERROR: " << e.what() << std::endl;
			continue;
		}
		if (instr.inst != comment)
			cmdStack.push_back(instr);
	}
}

void Lexer::input(int ac, char **av) {

	if (ac == 2)
		read(av[1]);
	else
		read();
}
