// ToyScript.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include "Lexer.h"
#include "Parser.h"
#include "Intepreter.h"
//#define LOG_TOKEN 
//#define SINGLE_LINE_PROCESS
#define SHELL_COMMAND
void Execute(const std::string& line);

Intepreter intpreter;
Value* value;
int main(int argc, char* argv[])
{
	float i = 9;
	float j = 9;

	/*std::cout << "Com: " << i + j << "\n";
	std::cout <<"Com: " << (1 < 10) << "\n";
	std::cout << "\\" << "\n";*/

	intpreter.SetSymbles();
	std::ifstream file;
	if (argv[1] == nullptr) 
	{
		// if command line argument is missing, use the defalut text file to demostrate the calculation
		file = std::ifstream("D:\\MyOwnPL\\ShinToyScript\\ShinToyScript\\Test\\Loop.sts");
	}
	else 
	{
		file = std::ifstream(argv[1]);
	}
	std::string line;


	while (std::getline(file, line)) 
	{
		Execute(line);
	}
	//delete value;

#ifdef SINGLE_LINE_PROCESS

	std::string input;
	while (true) 
	{
		std::cout << "Calc > ";
		std::getline(std::cin, input);
		Execute(input);
	}

#endif // SINGLE_LINE_PROCESS
}

void Execute(const std::string& line) 
{
	Lexer lexer(line);

	try
	{
		std::vector<Token> tokens = lexer.GenerateTokens();
		Parser parser(tokens);

#ifdef LOG_TOKEN
		for (auto i = tokens.begin(); i != tokens.end(); ++i)
			std::cout << (*i).ToString() << ' ' << "\n";
		std::cout << "\n";
#endif // LOG_TOKEN

		Node* tree = parser.Parse();
		if (tree != nullptr)
		{
			std::cout << tree->ToString() << "\n";
		}

		value = intpreter.Visit(tree);
#ifdef SHELL_COMMAND
		if (value != nullptr)
		{
			std::cout <<">>>"<< value->GetValue() << "\n\n";
		}
#endif // SHELL_COMMAND
		delete tree;

	}
	catch (std::string exp)
	{
		std::cout << exp << std::endl;
	}
}