#ifndef STACK_CLASS_HPP
#define STACK_CLASS_HPP

#include <cassert> // для assert
#include <iostream>
 
#include <iomanip> // для std::setw

class Stack
{
	private:
		char		*stackPtr;				// указатель на стек
		const int	_size;                   // максимальное количество элементов в стеке
		int			top;					// номер текущего элемента стека

	public:
		Stack(int = 10);					// по умолчанию размер стека равен 10 элементам
		Stack(const Stack &);				// конструктор копирования
		~Stack();							// деструктор
	
		void		push(const char & );	// поместить элемент в вершину стека
		char		pop();					// удалить элемент из вершины стека и вернуть его
		void		printStack();			// вывод стека на экран
		const char	&peek(int ) const;		// n-й элемент от вершины стека
		int			getStackSize() const;	// получить размер стека
		char		*getPtr() const;		// получить указатель на стек
		int			getTop() const;			// получить номер текущего элемента в стеке
};


 
#endif // STACK_CLASS_HPP