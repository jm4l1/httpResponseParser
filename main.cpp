#include "Parser.h"

#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
	std::string input = "";
	std::string line;
	int number_of_newlines = 0;

	HTTP::Parser parser;

	std::cout << "Paste header to be parsed\nEnter two blank lines to stop entry:\n";
	while (number_of_newlines < 2)
	{
		std::getline(std::cin, line);
		if (line == "")
		{
			number_of_newlines++;
			continue;
		}
		input += line + "\r\n";
	}

	try
	{
		parser.parse(input);
		parser.show_summary();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}