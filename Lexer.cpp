#include "Lexer.hpp"
#include "AvmExceptions.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <sstream> //

//TODO: https://solarianprogrammer.com/2011/10/12/cpp-11-regex-tutorial/
// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom/3279550#3279550
Lexer::Lexer()
	: rPush("(push( |\t)((int(8|16|32))|double|float)(.*))"),
	  rAssert("(assert( |\t)((int(8|16|32))|double|float)(.*))"),
	  rType("(int(8|16|32)|(double|float))"),
	  rDigit(R"(\(((\+|-)?[[:digit:]]+)(\.(([[:digit:]]+)?))?((e|E)((\+|-)?)[[:digit:]]+)?\))"),
	  rPop(R"(^[ \t\n]*(pop)[ \t\n]*)"),
	  rDump(R"(^[ \t\n]*(dump)[ \t\n]*)"),
	  rAdd(R"(^[ \t\n]*(add)[ \t\n]*)"),
	  rSub(R"(^[ \t\n]*(sub)[ \t\n]*)"),
	  rMul(R"(^[ \t\n]*(mul)[ \t\n]*)"),
	  rDiv(R"(^[ \t\n]*(div)[ \t\n]*)"),
	  rMod(R"(^[ \t\n]*(mod)[ \t\n]*)"),
	  rPrint(R"(^[ \t\n]*(print)[ \t\n]*)"),
	  rExit(R"(^[ \t\n]*(exit)[ \t\n]*)"),
	  cmdStack() {}
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

std::string	Lexer::findValue(const std::string &line) {
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
	auto		wBegin = std::sregex_iterator(line.begin(), line.end(), rDigit);
	auto		wEnd = std::sregex_iterator();
	std::string	val = (*wBegin).str();

	for (char c: "()") {
		val.erase(std::remove(val.begin(), val.end(), c), val.end());
	}
	if (std::distance(wBegin, wEnd) > 1)
		throw(AvmExceptions::SyntaxError(line));
	return val;
}

eOperandType Lexer::findType(const std::string &line) const
{
/*	std::smatch m;
	if (std::regex_search(line.begin(), line.end(), m, this->rType)) {
		std::vector<std::string> tab{"int8", "int16", "int32", "float", "double"};
		auto it = std::find(tab.begin(), tab.end(), m.str());
		if (it != tab.end()) {
			switch (std::distance(tab.begin(), it)) {
				case 0: return INT8;
				case 1: return INT16;
				case 2: return INT32;
				case 3: return FLOAT;
				case 4: return DOUBLE;
				default: throw (AvmExceptions::SyntaxError(line));
			}
		}
	}
	throw (AvmExceptions::SyntaxError(line));*/

	std::smatch m;
	static const std::map<std::string, eOperandType> typeMap = {
			{"int8",	INT8	},
			{"int16",	INT16	},
			{"int32",	INT32	},
			{"float",	FLOAT	},
			{"double",	DOUBLE	},
	};

	if (std::regex_search(line.begin(), line.end(), m, this->rType))
	{
		auto it = typeMap.find(m.str());
		if(it != typeMap.end())
			return it->second;
	}
	throw(AvmExceptions::SyntaxError(line));
}

cmd Lexer::tokenise(std::string &line) {
	static const std::map<std::string, cmd> typ = {
			{"dump",	{eInst::dump,		INT8, ""	} },
			{"add",		{eInst::add,		INT8, ""	} },
			{"sub",		{eInst::subtract,	INT8, ""	} },
			{"mul",		{eInst::multiply,	INT8, ""	} },
			{"div",		{eInst::divide,		INT8, ""	} },
			{"mod",		{eInst::modulo,		INT8, ""	} },
			{"print",	{eInst::print,		INT8, ""	} },
			{"exit",	{eInst::exit,		INT8, ""	} },
	};

	std::smatch m;
	const std::regex rTest(R"(^[ \t\n]*(pop|dump|add|sub|mul|div|mod|exit|print)[ \t\n]*)");

	if (std::regex_match(line, m, rTest))
	{
		std::string str = m.str();
		str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
/*		std::string str;
		std::stringstream tmp;
		tmp << m.str();
		tmp >> str;*/
//		std::cout << str << std::endl;
		auto it = typ.find(str);
		if(it != typ.end())
			return it->second;
	}
	if (std::regex_match(line.c_str(), rPush))
		return {eInst::pop, findType(line), findValue(line)};
	else if (std::regex_match(line.c_str(), rAssert))
		return {eInst::assert, findType(line), findValue(line)};
	throw(AvmExceptions::SyntaxError(line));


	//_----------------

/*	cmd command;
	if (std::regex_match(line.c_str(), rPush)) {
		command.inst = eInst::push;
		command.type = findType(line);
		command.value = findValue(line);
	}
	else if (std::regex_match(line.c_str(), rAssert)) {
		command.inst = eInst::assert;
		command.type = findType(line);
		command.value = findValue(line);
	}
	else if (std::regex_match(line.c_str(), rPop))
		command.inst = eInst::pop;
	else if (std::regex_match(line.c_str(), rDump))
		command.inst = eInst::dump;
	else if (std::regex_match(line.c_str(), rAssert))
		command.inst = eInst::assert;
	else if (std::regex_match(line.c_str(), rAdd))
		command.inst = eInst::add;
	else if (std::regex_match(line.c_str(), rSub))
		command.inst = eInst::subtract;
	else if (std::regex_match(line.c_str(), rMul))
		command.inst = eInst::multiply;
	else if (std::regex_match(line.c_str(), rDiv))
		command.inst = eInst::divide;
	else if (std::regex_match(line.c_str(), rMod))
		command.inst = eInst::modulo;
	else if (std::regex_match(line.c_str(), rPrint))
		command.inst = eInst::print;
	else if (std::regex_match(line.c_str(), rExit))
		command.inst = eInst::exit;
	else
		throw(AvmExceptions::SyntaxError(line));
	return command;*/
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
		if (instr.inst != eInst::comment) //
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
			instr = tokenise(line);
		}
		catch (std::exception &e) {
			std::cout << "ERROR: " << e.what() << std::endl;
			continue;
		}
		if (instr.inst != eInst::comment) //
			cmdStack.push_back(instr);
	}
}

void Lexer::input(int ac, char **av) {

	if (ac == 2)
		read(av[1]);
	else
		read();
}
