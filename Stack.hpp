#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <stack>
# include <iterator>

#include "IOperand.hpp"
#include "OperandsFactory.hpp"
#include "OperandsFactory.hpp"

class Stack : public std::stack<IOperand>
{
public:
	Stack() {}
	Stack(Stack const &cp) {
		*this = cp;
	}
	~Stack() {}

	Stack &operator=(Stack const &rhs) {
		if (this != &rhs)
			this->c = rhs.c;
		return *this;
	}

	typedef typename std::stack<IOperand>::container_type::const_iterator iterator;

	iterator begin() {
		return this->c.begin();
	}
	iterator end() {
		return this->c.end();
	}

	/*void push(const IOperand *op) {
		this->emplace(op);
	}*/


	void add() {
		if (this->size() > 1)
		{
			auto lop = this->top();
			this->pop();
			auto rop = this->top();
			this->pop();
			this->emplace(lop + rop);
		}
		else
			std::cout << "Stack size is les then 2" << std::endl;
	}

	void sub() {
		if (this->size() > 1)
		{
			auto lop = this->top();
			this->pop();
			auto rop = this->top();
			this->pop();
			this->emplace(lop - rop);
		}
		else
			std::cout << "Stack size is les then 2" << std::endl;
	}

	void myl() {
		if (this->size() > 1)
		{
			auto lop = this->top();
			this->pop();
			auto rop = this->top();
			this->pop();
			this->emplace(lop * rop);
		}
		else
			std::cout << "Stack size is les then 2" << std::endl;
	}

	void div() {
		if (this->size() > 1)
		{
			auto lop = this->top();
			this->pop();
			auto rop = this->top();
			this->pop();
			this->emplace(lop / rop);
		}
		else
			std::cout << "Stack size is les then 2" << std::endl;
	}

	void mod() {
		if (this->size() > 1)
		{
			auto lop = this->top();
			this->pop();
			auto rop = this->top();
			this->pop();
			this->emplace(lop % rop);
		}
		else
			std::cout << "Stack size is les then 2" << std::endl;
	}
};

#endif //STACK_HPP
