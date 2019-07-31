#include "Lexer.hpp"
#include "AvmExceptions.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <sstream> //
#include <sys/stat.h> //

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
	  rEndOfProg(R"(^[ \t\n]*(;;)[ \t\n]*)") {}
Lexer::~Lexer() {}

Lexer &Lexer::instance() {
	static Lexer instance;
	return instance;
}

// TODO: throw ex when more the one match?
// TODO: empty arg int()
// TODO: argument like int8(42

std::string	Lexer::findValue(const std::string &line) const {
	auto		wBegin = std::sregex_iterator(line.begin(), line.end(), rDigit);
	auto		wEnd = std::sregex_iterator();
	std::string	val = (*wBegin).str();

	for (char c: "()") {
		val.erase(std::remove(val.begin(), val.end(), c), val.end());
	}
	if (std::distance(wBegin, wEnd) > 1 || val.empty())
		throw(AvmExceptions::SyntaxError());
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
	throw(AvmExceptions::SyntaxError());
}

void Lexer::tokenise(std::string &line, cmd &inst) const {
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

	if (std::regex_match(line.c_str(), rPush)) {
		inst.inst = eInst::push;
		inst.type = findType(line);
		inst.value = findValue(line);
	}
	else if (std::regex_match(line.c_str(), rAssert)) {
		inst.inst = eInst::assert;
		inst.type = findType(line);
		inst.value = findValue(line);
	}
	else if (std::regex_match(line.c_str(), rPop))
		inst.inst = eInst::pop;
	else if (std::regex_match(line.c_str(), rDump))
		inst.inst = eInst::dump;
	else if (std::regex_match(line.c_str(), rAssert))
		inst.inst = eInst::assert;
	else if (std::regex_match(line.c_str(), rAdd))
		inst.inst = eInst::add;
	else if (std::regex_match(line.c_str(), rSub))
		inst.inst = eInst::subtract;
	else if (std::regex_match(line.c_str(), rMul))
		inst.inst = eInst::multiply;
	else if (std::regex_match(line.c_str(), rDiv))
		inst.inst = eInst::divide;
	else if (std::regex_match(line.c_str(), rMod))
		inst.inst = eInst::modulo;
	else if (std::regex_match(line.c_str(), rPrint))
		inst.inst = eInst::print;
	else if (std::regex_match(line.c_str(), rExit))
		inst.inst = eInst::exit;
	else
		throw(AvmExceptions::SyntaxError());
}

void Lexer::read()
{
	std::string line;
	cmd instr;
	int i = 0;

	while (!std::getline(std::cin, line).eof()) {
		if (std::regex_match(line.c_str(), rEndOfProg))
			break;
		size_t column = line.find(';');
		if (column != std::string::npos)
			line.erase(column);
		if (line.empty())
			continue;
		try {
			i++;
			tokenise(line, instr);
		}
		catch (std::exception &e) {
			std::cout << "Line " << i << ": " << e.what() << std::endl;
			continue;
		}
		PARSER.setCommand(instr);
	}
	if (instr.inst != eInst::exit)
		throw (AvmExceptions::ExceptionString("No exit command"));
}

void Lexer::read(std::string &fileName)
{
	std::ifstream buff(fileName);
	std::string line;
	cmd instr;
	int i = 0;

	{
		struct stat s;
		if ((stat(fileName.c_str(), &s) != 0) || !(s.st_mode & S_IFREG) || !buff.is_open())
			throw AvmExceptions::ExceptionString("Failed to open " + fileName);
	}
	while (std::getline(buff, line)) {
		std::string tmp = line;
		size_t comment = line.find(';');
		if (comment != std::string::npos)
			line.erase(comment);
		if (line.empty())
			continue;
		try {
			i++;
			tokenise(line, instr);
		}
		catch (AvmExceptions::SyntaxError &e) {
			std::cout << "Line " << i << ": " << e.what() << tmp << std::endl;
			continue;
		}
		catch (std::exception &e) {
			std::cout << "Line " << i << ": " << e.what() << std::endl;
			continue;
		}
		PARSER.setCommand(instr);
	}
	if (instr.inst != eInst::exit)
		throw (AvmExceptions::ExceptionString("No exit command"));
}

//TODO: more then one file
void Lexer::input(int ac, char **av) {
	if (ac == 2)
	{
		std::string fileName(av[1]);
		read(fileName);
	}
	else
		read();
}
