#include "Stack.class.hpp"

// конструктор Стека
Stack::Stack(int size) : _size(size) // инициализация константы
{
    stackPtr = new char[this->_size]; // выделить память под стек
    top = 0; // инициализируем текущий элемент нулем;
}
 
// конструктор копирования
Stack::Stack(const Stack & otherStack) : _size(otherStack.getStackSize()) // инициализация константы
{
    stackPtr = new char[this->_size]; // выделить память под новый стек
    top = otherStack.getTop();
 
    for(int ix = 0; ix < top; ix++)
        stackPtr[ix] = otherStack.getPtr()[ix];
}
 
// функция деструктора Стека
Stack::~Stack()
{
    delete [] stackPtr; // удаляем стек
}
 
// функция добавления элемента в стек
void Stack::push(const char &value)
{
    // проверяем размер стека
    assert(top < this->_size); // номер текущего элемента должен быть меньше размера стека
 
    stackPtr[top++] = value; // помещаем элемент в стек
}
 
// функция удаления элемента из стека
char Stack::pop()
{
    // проверяем размер стека
    assert(top > 0); // номер текущего элемента должен быть больше 0
    return stackPtr[--top]; // удаляем элемент из стека
}
 
// функция возвращает n-й элемент от вершины стека

const char &Stack::peek(int nom) const
{
  //
  assert(nom <= top);
 
  return stackPtr[top - nom]; // вернуть n-й элемент стека
}
 
// вывод стека на экран
void Stack::printStack()
{
    for (int ix = top - 1; ix >= 0; ix--)
        std::cout << "|" << std::setw(4) << stackPtr[ix] << std::endl;
}
 
// вернуть размер стека
int Stack::getStackSize() const
{
    return this->_size;
}
 
// вернуть указатель на стек (для конструктора копирования)
char *Stack::getPtr() const
{
    return stackPtr;
}
 
// вернуть размер стека
int Stack::getTop() const
{
    return top;
}