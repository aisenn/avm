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


//	OperandsFactory & a = OperandsFactory::instance();
	Operand<size_t > e(42);

	Operand<int8_t > w(59);
	Operand<float > q(1.123);
	w + q;
	const IOperand *a = OperandsFactory::instance().createOperand(INT8, "127");
	const IOperand *b = OperandsFactory::instance().createOperand(INT8, "128");

	a = b + 100;
/*	s.push("1");
	s.push("2");
	s.push("3");*/
//	s.add();
	return 9;
}
