#include <iostream>
#include <string>
#include <sstream>
#include "Stack.hpp"


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
	Stack s;


//	OperandsFactory & a = OperandsFactory::instance();
	const IOperand *a = OperandsFactory::instance().createOperand(INT8, "42");
/*	s.push("1");
	s.push("2");
	s.push("3");*/
//	s.add();
	return 9;
}
