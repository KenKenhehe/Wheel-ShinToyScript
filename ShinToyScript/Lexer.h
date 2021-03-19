#pragma once

#include "Token.h"
#include <vector>
#include <exception>

class Lexer
{
public:
	Lexer(std::string text);

	void Advance();

	std::vector<Token> GenerateTokens();

	Token GenerateNumber();
	Token GenerateIdentifier();
	Token GenerateEquals();
	Token GenerateNotEqual();
	Token GenerateGreaterThan();
	Token GenerateLessThan();

	bool IsKeyword(std::string str);

	std::string ToLower(std::string str);
	

private:
	char current_char;
	std::string m_Text;
	int m_CurrentIndex = 0;

	//Constant variables
	const std::string m_WhiteSpace = " \t";
	//const std::string m_NewLine = "\n";
	const std::string m_Digit = "0123456789";

	std::vector<std::string> m_Keywords = { "var", "if", "and", "or", "not" };

};

