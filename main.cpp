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


	const IOperand *a = OperandsFactory::instance().createOperand(INT8, "127");
	const IOperand *b = OperandsFactory::instance().createOperand(INT8, "128");

	w.getType();
	w + q;
	a = b + 100;
/*	s.push("1");
	s.push("2");
	s.push("3");*/
//	s.add();
	return 9;
}
