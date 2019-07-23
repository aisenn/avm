#include "Lexer.hpp"

Lexer::Lexer() {}

Lexer::~Lexer() {}

Lexer &Lexer::instance() {
	static Lexer instance;
	return instance;
}