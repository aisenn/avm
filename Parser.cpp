#include "Parser.hpp"

//TODO https://github.com/brhamidi/abstract-vm/blob/master/Lexer.cpp
//TODO: could I use = default??

Parser::Parser() {}
Parser::~Parser() {}

void Parser::commandLineInput() {

}

void Parser::fileInput(const char *fileName) {

}

Parser &Parser::instance() {
	static Parser instance;
	return instance;
}


