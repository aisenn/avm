#include <iostream>
#include <string>
#include <sstream>
#include "Stack.hpp"

#include "IOperand.hpp"
#include "Operand.hpp"
#include "OperandsFactory.hpp"
#include "Parser.hpp"
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

int main () {
//	Stack s;


	Operand<int8_t > w(59);
	Operand<float > q(1.123);


	try {
		const IOperand *a = OperandsFactory::instance().createOperand(INT8, "127");
		std::string num = "340282346638528859811704183484516925440.000000";
		const IOperand *b = OperandsFactory::instance().createOperand(FLOAT, num);

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
