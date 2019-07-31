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
	for (auto &it : _cmdStack) {
		switch (it.inst) {
			case eInst::push : STACK.push(FACTORY.createOperand(it.type, it.value)); break;
			case eInst::assert : STACK.massert(it.type, it.value); break;
			case eInst::pop : STACK.mpop();		break;
			case eInst::dump : STACK.dump();	break;
			case eInst::add : STACK.add();		break;
			case eInst::subtract : STACK.sub();	break;
			case eInst::multiply : STACK.mul();	break;
			case eInst::divide : STACK.div();	break;
			case eInst::modulo : STACK.mod();	break;
			case eInst::print : STACK.print();	break;
			case eInst::exit : STACK.exit();	break;
			default: throw (AvmExceptions::UndefinedInstruction());
		}
	}
}

void Parser::setCommand(cmd &command) {
	_cmdStack.push_back(command);
}