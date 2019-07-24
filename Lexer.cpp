#include "Lexer.hpp"
#include <iostream>
#include <fstream>


//https://solarianprogrammer.com/2011/10/12/cpp-11-regex-tutorial/

Lexer::Lexer() : cmdStack() {}
Lexer::~Lexer() {}

Lexer &Lexer::instance() {
	static Lexer instance;
	return instance;
}

void Lexer::read()
{

}

void tockenise(std::string token) {

}

void Lexer::read(char *fileName)
{
	std::ifstream someVarName(fileName);

	std::string line;
	cmd instr;
	while (!std::getline(someVarName, line).eof()) {

		if (line == ";;")
			break;
		size_t column = line.find(';');
		if (column != std::string::npos)
			line.erase(column);
		if (line.empty())
			continue;
		try {

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
