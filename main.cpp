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

	try {
		LEXER.input(argc, argv);
		PARSER.commandsParsing();

		const IOperand *a = OperandsFactory::instance().createOperand(INT8, "127");
		const IOperand *b = OperandsFactory::instance().createOperand(FLOAT, "123");

	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
