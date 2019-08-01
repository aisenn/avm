#include "Parser.hpp"
#include "Lexer.hpp"

int main (int argc, char **argv) {
	try {
		LEXER.input(argc, argv);
		PARSER.commandsParsing();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	system("leaks avm"); //TODO: delete
	return 0;
}
