#ifndef PARSER_HPP
#define PARSER_HPP


class Parser {
private:
	Parser() {}

public:
	Parser &operator=(Parser const &) = delete;
	Parser(Parser const &) = delete;

	void commandLineInput();
	void fileInput(const char *fileName);

};


#endif //PARSER_HPP
