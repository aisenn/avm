#include "Lexer.hpp"
#include "AvmExceptions.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <sys/stat.h>

//**********************************************
//*          CONSTRUCTOR / DESTRUCTOR          *
//**********************************************
Lexer::Lexer()
	: rPush(R"(^[\s]*(push)[\s]*((int(8|16|32))|double|float)\(([^)]+)\)[\s]*)"),
	  rAssert(R"(^[\s]*(assert)[\s]*((int(8|16|32))|double|float)\(([^)]+)\)[\s]*)"),
	  rType("(int(8|16|32)|(double|float))"),
	  rDigit(R"(\(((\+|-)?[[:digit:]]+)(\.(([[:digit:]]+)?))?((e|E)((\+|-)?)[[:digit:]]+)?\))"),
	  rPow(R"(^[\s]*(pow)[\s]*((int(8|16|32))|double|float)\(([^)]+)\)[\s]*)"),
	  rEndOfProg(R"(^[\s]*(;;)[\s]*)"),
	  rInst("((pop|dump|add|sub|mul|div|mod|average|log|sqrt|clear|exit|print))"){}

Lexer::~Lexer() {}

//**********************************************
//*              INSTANCE GETTER               *
//**********************************************
Lexer &Lexer::instance() {
	static Lexer instance;
	return instance;
}

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
		static const std::map<std::string, eInst > typ = {
			{"dump",	eInst::dump },
			{"add",		eInst::add },
			{"sub",		eInst::subtract },
			{"mul",		eInst::multiply },
			{"div",		eInst::divide },
			{"mod",		eInst::modulo },
			{"print",	eInst::print },
			{"average",	eInst::average },
			{"log",		eInst::log },
			{"sqrt",	eInst::sqrt },
			{"clear",	eInst::clear },
			{"exit",	eInst::exit },
	};

	std::smatch m;
	if (std::regex_search(line, m, rInst))
	{
		std::regex tt(R"((\s*)(\S+)(\s*))");
		if (!std::regex_match(line.c_str(), tt))
			throw (AvmExceptions::SyntaxError());
		auto it = typ.find(m.str());
		if(it != typ.end())
			inst.inst = it->second;
	}
	else if (std::regex_match(line.c_str(), rPush)) {
		inst.inst = eInst::push;
		inst.type = findType(line);
		inst.value = findValue(line);
	}
	else if (std::regex_match(line.c_str(), rAssert)) {
		inst.inst = eInst::assert;
		inst.type = findType(line);
		inst.value = findValue(line);
	}
	else if (std::regex_match(line.c_str(), rPow)) {
		inst.inst = eInst::pow;
		inst.type = findType(line);
		inst.value = findValue(line);
	}
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
