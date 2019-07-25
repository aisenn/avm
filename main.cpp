#include <iostream>
#include <string>
#include <sstream>
#include "Stack.hpp"

#include "IOperand.hpp"
#include "Operand.hpp"
#include "OperandsFactory.hpp"
#include "Parser.hpp"
#include "Lexer.hpp"



//#include ""

/*
 * at ?
 * top
 * push +
 * pop +
 * swap +
 * peek ?
 * dump
 * assert
 * add
 * subtract
 * multiply
 * divide
 * modulo
 * print
 * average
 * */
#include <fstream>

int main (int argc, char **argv) {

//	Stack s;

	Lexer::instance().input(argc, argv);


	Operand<int8_t > w(59);
	Operand<float > q(1.123);


	auto tmp = Lexer::instance().cmdStack;
	try {
		const IOperand *a = OperandsFactory::instance().createOperand(INT8, "127");
		const IOperand *b = OperandsFactory::instance().createOperand(FLOAT, "123");

		w.getType();
		w + q;
		a = b + 100;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}


/*	s.push("1");
	s.push("2");
	s.push("3");*/
//	s.add();
	return 9;
}
