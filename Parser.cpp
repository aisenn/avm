#include "Parser.hpp"
#include "Stack.hpp"


//TODO https://github.com/brhamidi/abstract-vm/blob/master/Lexer.cpp
//TODO: could I use = default??

Parser::Parser() {}
Parser::~Parser() {}

Parser &Parser::instance() {
	static Parser instance;
	return instance;
}

void	Parser::commandsParsing() {
	for (auto it = cmdStack.begin(); it != cmdStack.end(); ++it) {
		switch (it->inst) {
			case eInst::push : {
				STACK->push(FACTORY.createOperand(it->type, it->value));
				STACK.push();
			}
		}
	}
}