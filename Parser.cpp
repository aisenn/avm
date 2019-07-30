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
	//TODO: do not use STACK macro here
//	for (auto i : cmdStack)
	for (auto it = cmdStack.begin(); it != cmdStack.end(); ++it) {
		switch (it->inst) {
			case eInst::push : {
				STACK.push(FACTORY.createOperand(it->type, it->value));
				break;
			}
			case eInst::assert : {
//				STACK.assert(it->value, it->type);
				break;
			}
			case eInst::pop : STACK.pop();		break; //TODO: overload pop
			case eInst::dump : STACK.dump();	break;
			case eInst::add : STACK.add();		break;
			case eInst::subtract : STACK.sub();	break;
			case eInst::multiply : STACK.mul();	break;
			case eInst::divide : STACK.div();	break;
			case eInst::modulo : STACK.mod();	break;
			case eInst::print : STACK.print();	break;
			case eInst::exit : std::exit(0);			//TODO: exit ??
			default: throw (AvmExceptions::UndefinedInstruction());
		}
	}
}