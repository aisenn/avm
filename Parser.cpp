#include "Parser.hpp"
#include "Stack.hpp"
#include "OperandsFactory.hpp"

//**********************************************
//*          CONSTRUCTOR / DESTRUCTOR          *
//**********************************************
int Parser::fd = -1; //TODO: delete

Parser::Parser() : _cmdStack(), _names() {}
Parser::~Parser() {}

//**********************************************
//*              INSTANCE GETTER               *
//**********************************************
Parser &Parser::instance() {
	static Parser instance;
	return instance;
}

//**********************************************
//*          PUBLIC MEMBER FUNCTIONS           *
//**********************************************
/*void	Parser::commandsParsing() {
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
}*/

void	Parser::commandsParsing() {
	for (auto &commands : _cmdStack) {
		std::cout << "\033[1;34m";
		if (Parser::fd > 0)
			std::cout << _names.front() << "\033[1;92m" << std::endl;
		for (auto &it : commands) {
			try {
				if (it.inst == eInst::exit) {
					_names.pop_front();
					STACK.dump();
					STACK.clear();
					std::cout << "\033[1;0m" << std::endl;
					break;
				}
				switch (it.inst) {
					case eInst::push : STACK.mpush(it.type, it.value); break;
					case eInst::assert : STACK.massert(it.type, it.value); break;
					case eInst::pop : STACK.mpop(); break;
					case eInst::dump : STACK.dump(); break;
					case eInst::add : STACK.add(); break;
					case eInst::subtract : STACK.sub(); break;
					case eInst::multiply : STACK.mul(); break;
					case eInst::divide : STACK.div(); break;
					case eInst::modulo : STACK.mod(); break;
					case eInst::average : STACK.average(); break;
					case eInst::print : STACK.print(); break;
					default: throw (AvmExceptions::UndefinedInstruction());
				}
			}
			catch (std::exception &e) {
				std::cout << e.what() << std::endl;
				continue;
			}
		}
	}
}

void Parser::setCommand(cmd &command) {
	_cmdStack[Parser::fd].push_back(command);
}