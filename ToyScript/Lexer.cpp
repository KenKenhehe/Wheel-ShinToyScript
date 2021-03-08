#include "Lexer.h"

Lexer::Lexer(std::string text): m_Text(text)
{
	current_char = m_Text[m_CurrentIndex];
	//Advance();
}

void Lexer::Advance()
{
	m_CurrentIndex++;
	current_char = m_Text[m_CurrentIndex];
}

std::vector<Token> Lexer::GenerateTokens()
{
	std::vector<Token> tokens;

	/*Avoiding addition copying by reserving the vector with the text count, 
	The number of token is definately lower than the number of text input, 
	a few extra space in the memory is fine since it's mostly text file*/
	tokens.reserve(strlen(m_Text.c_str()));

	while (m_CurrentIndex < strlen(m_Text.c_str())) {
		if (m_WhiteSpace.find(current_char) != std::string::npos) 
		{
			Advance();
		}
		else if (std::string("\n").find(current_char) != std::string::npos)
		{
			tokens.emplace_back(Token::TokenType::NEW_LINE, "+");
			Advance();
		}
		else if (std::string(m_Digit).find(current_char) != std::string::npos ||
				std::string(".").find(current_char) != std::string::npos)
		{
			Token token = GenerateNumber();
			tokens.emplace_back(token);
		}
		else if (std::string("+").find(current_char) != std::string::npos) 
		{
			tokens.emplace_back(Token::TokenType::PLUS, "+");
			Advance();
		}
		else if (std::string("-").find(current_char) != std::string::npos)
		{
			tokens.emplace_back(Token::TokenType::MINUS, "-");
			Advance();
		}
		else if (std::string("*").find(current_char) != std::string::npos)
		{
			tokens.emplace_back(Token::TokenType::MUL, "*");
			Advance();
		}
		else if (std::string("/").find(current_char) != std::string::npos)
		{
			tokens.emplace_back(Token::TokenType::DIV, "/");
			Advance();
		}
		else if (std::string("(").find(current_char) != std::string::npos)
		{
			tokens.emplace_back(Token::TokenType::L_PAREN, "(");
			Advance();
		}
		else if (std::string(")").find(current_char) != std::string::npos)
		{
			tokens.emplace_back(Token::TokenType::R_PAREN, ")");
			Advance();
		}
		else if (std::string("^").find(current_char) != std::string::npos) 
		{
			tokens.emplace_back(Token::TokenType::POWER, "^");
			Advance();
		}
		else if (std::string("%").find(current_char) != std::string::npos)
		{
			tokens.emplace_back(Token::TokenType::MODULUS, "%");
			Advance();
		}
		else 
		{
			std::string errStr = "Invalid character: '";
			errStr.push_back(current_char);
			errStr.push_back('\'');
			throw errStr;
		}
	}
	return tokens;
}

Token Lexer::GenerateNumber()
{
	int decimalCount = 0;
	std::string numStr;
	numStr.push_back(current_char);
	Advance();
	while (current_char != '\0' &&
		(current_char == '.' || m_Digit.find(current_char) != std::string::npos)) 
	{
		if (current_char == '.') 
		{
			decimalCount++;
			if (decimalCount > 1) 
			{
				break;
			}
		}
		numStr = numStr + current_char;
		Advance();
	}

	if (numStr[0] == '.') 
	{
		numStr = "0" + numStr;
	}

	
	if (numStr[strlen(numStr.c_str()) - 1] == '.') 
	{
		numStr = numStr + "0";
	}
	

	return Token(Token::TokenType::NUMBER, numStr);
}
