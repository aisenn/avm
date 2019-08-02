#include "Lexer.hpp"
#include "AvmExceptions.hpp"
#include <iostream>
#include <fstream> //
#include <map> //
#include <sstream> //
#include <sys/stat.h> //

//TODO: https://solarianprogrammer.com/2011/10/12/cpp-11-regex-tutorial/
// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom/3279550#3279550
// http://pygments.org/docs/lexerdevelopment/
// https://nitschinger.at/Writing-a-simple-lexer-in-PHP/
// https://web-answers.ru/c/probel-shkipera-pri-ispolzovanii-boost-spirit-qi-i.html
// http://kiri11.ru/boost_spirit_qi_part5/

//**********************************************
//*          CONSTRUCTOR / DESTRUCTOR          *
//**********************************************
Lexer::Lexer()
	: rPush(R"(^[\s]*(push)[\s]*((int(8|16|32))|double|float)\(([^)]+)\)[\s]*)"),
	  rAssert(R"(^[\s]*(assert)[\s]*((int(8|16|32))|double|float)\(([^)]+)\)[\s]*)"),
	  rType("(int(8|16|32)|(double|float))"),
	  rDigit(R"(\(((\+|-)?[[:digit:]]+)(\.(([[:digit:]]+)?))?((e|E)((\+|-)?)[[:digit:]]+)?\))"),
	  rPop(R"(^[\s]*(pop)[\s]*)"),
	  rDump(R"(^[\s]*(dump)[\s]*)"),
	  rAdd(R"(^[\s]*(add)[\s]*)"),
	  rSub(R"(^[\s]*(sub)[\s]*)"),
	  rMul(R"(^[\s]*(mul)[\s]*)"),
	  rDiv(R"(^[\s]*(div)[\s]*)"),
	  rMod(R"(^[\s]*(mod)[\s]*)"),
	  rPrint(R"(^[\s]*(print)[\s]*)"),
	  rExit(R"(^[\s]*(exit)[\s]*)"),
	  rEndOfProg(R"(^[\s]*(;;)[\s]*)") {}

Lexer::~Lexer() {}

//**********************************************
//*              INSTANCE GETTER               *
//**********************************************
Lexer &Lexer::instance() {
	static Lexer instance;
	return instance;
}

// TODO: throw ex when more the one match?
// TODO: empty arg int()
// TODO: argument like int8(42

//**********************************************
//*          PRIVATE MEMBER FUNCTIONS          *
//**********************************************
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
	cmd instr{};

	std::string p;
	PARSER.fdEmplase(p);
	for (int i = 1; !std::getline(std::cin, line).eof(); i++) {
		std::string tmp = line;
		if (std::regex_match(line.c_str(), rEndOfProg))
			break;
		size_t column = line.find(';');
		if (column != std::string::npos)
			line.erase(column);
		if (line.empty())
			continue;
		try {
			if (instr.inst == eInst::exit)
				throw(AvmExceptions::ExceptionString("Commands after exit instruction"));
			tokenise(line, instr);
		}
		catch (std::exception &e) {
			std::cout << "Line " << i << ": " << e.what() << tmp << std::endl;
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
	cmd instr{};

	{
		struct stat s;
		if ((stat(fileName.c_str(), &s) != 0) || !(s.st_mode & S_IFREG) || !buff.is_open())
			throw AvmExceptions::ExceptionString("Failed to open " + fileName);
	}
	PARSER.fdEmplase(fileName); //TODO: check chmod 000 , dir and invalid name
	for (int i = 1; std::getline(buff, line); i++) {
		std::string tmp = line;
		size_t comment = line.find(';');
		if (comment != std::string::npos)
			line.erase(comment);
		if (line.empty())
			continue;
		try {
			if (instr.inst == eInst::exit)
				throw(AvmExceptions::ExceptionString("Commands after exit instruction"));
			tokenise(line, instr);
		}
		catch (AvmExceptions::SyntaxError &e) {
			std::cout << "FIle " << fileName << ": Line " << i << ": " << e.what() << tmp << std::endl;
			continue;
		}
		catch (std::exception &e) {
			std::cout << "FIle " << fileName << ": Line " << i << ": " << e.what() << std::endl;
			continue;
		}
		PARSER.setCommand(instr);
	}
	if (instr.inst != eInst::exit)
		throw (AvmExceptions::ExceptionString("No exit command"));
}

//**********************************************
//*           PUBLIC MEMBER FUNCTIONS          *
//**********************************************
//TODO: more then one file
void Lexer::input(int ac, char **av) {
	if (ac > 1)
	{
		for (int i = 1; i < ac; i++) {
			try {
				std::string fileName(av[i]);
				read(fileName);
			}
			catch (std::exception &e) {
				std::cout << e.what() << std::endl;
				continue;
			}
		}
	}
	else
		read();
	//TODO: https://github.com/Svalorzen/cpp-readline
}
