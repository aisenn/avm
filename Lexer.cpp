#include "Lexer.hpp"
#include "AvmExceptions.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <sstream> //

//TODO: https://solarianprogrammer.com/2011/10/12/cpp-11-regex-tutorial/
// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom/3279550#3279550
// http://pygments.org/docs/lexerdevelopment/
// https://nitschinger.at/Writing-a-simple-lexer-in-PHP/
// https://web-answers.ru/c/probel-shkipera-pri-ispolzovanii-boost-spirit-qi-i.html
// http://kiri11.ru/boost_spirit_qi_part5/
Lexer::Lexer()
	: rPush("(^[ \\t\\n]*(push)( |\t)((int(8|16|32))|double|float)(.*))"),
	  rAssert("(^[ \\t\\n]*(assert)( |\t)((int(8|16|32))|double|float)(.*))"),
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
	  rInst(R"(^[ \t\n]*(pop|dump|add|sub|mul|div|mod|exit|print)[ \t\n]*)"),
	  cmdStack() {}
Lexer::~Lexer() {}

Lexer &Lexer::instance() {
	static Lexer instance;
	return instance;
}

// TODO: throw ex when more the one match?

std::string	Lexer::findValue(const std::string &line) {
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
/*	static const std::map<std::string, cmd> typ = {
			{"dump",	{eInst::dump,		eNULL, ""	} },
			{"add",		{eInst::add,		eNULL, ""	} },
			{"sub",		{eInst::subtract,	eNULL, ""	} },
			{"mul",		{eInst::multiply,	eNULL, ""	} },
			{"div",		{eInst::divide,		eNULL, ""	} },
			{"mod",		{eInst::modulo,		eNULL, ""	} },
			{"print",	{eInst::print,		eNULL, ""	} },
			{"exit",	{eInst::exit,		eNULL, ""	} },
	};

	std::smatch m;
	if (std::regex_match(line, m, rInst))
	{
		auto it = typ.lower_bound(m.str());
		if(it != typ.end())
			return it->second;
	}
	if (std::regex_match(line.c_str(), rPush))
		return {eInst::push, findType(line), findValue(line)};
	else if (std::regex_match(line.c_str(), rAssert))
		return {eInst::assert, findType(line), findValue(line)};
	throw(AvmExceptions::SyntaxError(line));*/

	cmd command;
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
	return command;
}


//test tokeniser
/*void Lexer::tokenise(std::string &line, cmd &instr) {
	static const std::map<std::string, eInst > typ = {
			{"dump",	eInst::dump	 },
			{"add",		eInst::add	 },
			{"sub",		eInst::subtract },
			{"mul",		eInst::multiply },
			{"div",		eInst::divide	 },
			{"mod",		eInst::modulo	 },
			{"print",	eInst::print	 },
			{"exit",	eInst::exit	 },
	};

	std::smatch m;
	if (std::regex_match(line, m, rInst))
	{
		auto it = typ.lower_bound(m.str());
		std::cout << m.str() << (int)it->second << std::endl;
		if(it != typ.end())
			instr.inst = it->second;
	}
	else if (std::regex_match(line.c_str(), rPush))
	{
//		instr = {.inst = eInst::push, .type = findType(line), .value = findValue(line)};
		instr.inst = eInst::push;
		instr.type = findType(line);
		instr.value = findValue(line);
	}
	else if (std::regex_match(line.c_str(), rAssert))
	{
//		instr = {.inst = eInst::assert, .type = findType(line), .value = findValue(line)};
		instr.inst = eInst::assert;
		instr.type = findType(line);
		instr.value = findValue(line);
	}
	else
		throw(AvmExceptions::SyntaxError(line));
}*/

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
			instr = tokenise(line);
		}
		catch (std::exception &e) {
			std::cout << "ERROR: " << e.what() << std::endl;
			continue;
		}
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
//			tokenise(line, instr);
		}
		catch (std::exception &e) {
			std::cout << "ERROR: " << e.what() << std::endl;
			continue;
		}
//		cmdStack.push_back(instr);
		PARSER.cmdStack.push_back(instr);
	}
}

void Lexer::input(int ac, char **av) {

	if (ac == 2)
		read(av[1]);
	else
		read();
}
