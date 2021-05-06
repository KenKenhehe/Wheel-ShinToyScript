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
		else if (std::string("/").find(current_char) != std::string::npos) 
		{
			GenerateComment();
		}
		else if (std::string(";\n").find(current_char) != std::string::npos)
		{
			tokens.emplace_back(Token::TokenType::NEW_LINE, "new line");
			Advance();
		}
		else if (isalpha(current_char))
		{
			Token token = GenerateIdentifier();
			tokens.emplace_back(token);
		}
		else if (std::string(m_Digit).find(current_char) != std::string::npos ||
				std::string(".").find(current_char) != std::string::npos)
		{
			Token token = GenerateNumber();
			tokens.emplace_back(token);
		}
		else if (std::string("\"").find(current_char) != std::string::npos) 
		{
			Token token = GenerateString();
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
		else if (std::string("[").find(current_char) != std::string::npos)
		{
			tokens.emplace_back(Token::TokenType::L_SQUARE, "[");
			Advance();
		}
		else if (std::string("]").find(current_char) != std::string::npos)
		{
			tokens.emplace_back(Token::TokenType::R_SQUARE, "]");
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
		else if (std::string("=").find(current_char) != std::string::npos)
		{
			Token token = GenerateEquals();
			tokens.emplace_back(token);
		}
		else if (std::string("!").find(current_char) != std::string::npos)
		{
			Token token = GenerateNotEqual();
			tokens.emplace_back(token);
		}
		else if (std::string(">").find(current_char) != std::string::npos)
		{
			Token token = GenerateGreaterThan();
			tokens.emplace_back(token);
		}
		else if (std::string("<").find(current_char) != std::string::npos)
		{
			Token token = GenerateLessThan();
			tokens.emplace_back(token);
		}
		else if (std::string(",").find(current_char) != std::string::npos)
		{
			Token token = GenerateLessThan();
			tokens.emplace_back(Token::TokenType::COMMA, ",");
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

Token Lexer::GenerateString()
{
	bool isEscapeChar = false;
	std::string value;
	Advance();
	while (current_char != '\0' && (current_char != '"' || isEscapeChar == true)) 
	{
		if (isEscapeChar) 
		{
			char charToAdd = MapEscapeChar(current_char);
			value += charToAdd;
			isEscapeChar = false;
		}
		else {
			if (current_char == '\\')
			{
				isEscapeChar = true;
			}
			else
			{
				value += current_char;
			}
		}
		Advance();
	}
	//value.pop_back();
	//value.pop_back();
	Advance();
	return Token(Token::TokenType::STRING, value);
}



Token Lexer::GenerateIdentifier()
{
	std::string identifierStr;
	while (current_char != '\0' && 
		(isalpha(current_char) ||
		std::string("_").find(current_char) != std::string::npos ||
		m_Digit.find(current_char) != std::string::npos))
	{
		identifierStr += current_char;
		Advance();
	}

	if (IsKeyword(identifierStr) == true) 
	{
		return Token(Token::TokenType::KEYWORD, identifierStr);
	}

	return Token(Token::TokenType::IDENTIFIER, identifierStr);
}

Token Lexer::GenerateEquals()
{
	std::string equalStr;
	
	int equCount = 0;
	while (current_char != '\0' && (std::string("=").find(current_char) != std::string::npos)) 
	{
		if (equCount >= 2)
		{
			break;
		}
		equalStr += current_char;
		equCount += 1;
		
		Advance();
	}
	if (equalStr.find("==") != std::string::npos) 
	{
		return Token(Token::TokenType::EQEQ, equalStr);
	}

	if (current_char == '>')
	{
		Advance();
		return Token(Token::TokenType::ARROW, "=>");
	}
		
	return Token(Token::TokenType::EQU, "=");
}

Token Lexer::GenerateNotEqual()
{
	Advance();
	if (current_char == '=') {
		Advance();
		return Token(Token::TokenType::NEQU, "!=");
	}
	throw std::string("Expected: '='");
}

Token Lexer::GenerateGreaterThan()
{
	Advance();
	if (current_char == '=') 
	{
		Advance();
		return Token(Token::TokenType::GTEQ, ">=");
	}
	return Token(Token::TokenType::GT, ">");
}

Token Lexer::GenerateLessThan()
{
	Advance();
	if (current_char == '=') 
	{
		Advance();
		return Token(Token::TokenType::LTEQ, "<=");
	}
	return Token(Token::TokenType::LT, "<");
}

void Lexer::GenerateComment()
{
	Advance();
	if (current_char == '/') 
	{
		while (std::string(";\n").find(current_char) == std::string::npos)
		{
			Advance();
		}
	}
	else if (current_char == '*') 
	{
		while (std::string("*").find(current_char) == std::string::npos)
		{
			Advance();
		}
		while (std::string("/").find(current_char) == std::string::npos)
		{
			Advance();
		}
	}
}

char Lexer::MapEscapeChar(char& charToMap)
{
	char charToRet = charToMap;
	switch (charToMap)
	{
	case 'n':
		charToRet = '\n';
		break;
	case 't':
		charToRet = '\t';
		break;
	default:
		break;
	}
	return charToRet;
}

bool Lexer::IsKeyword(std::string str)
{
	//std::string lowerStr = ToLower(str);
	return std::find(m_Keywords.begin(), m_Keywords.end(), str) != m_Keywords.end();
}

std::string Lexer::ToLower(std::string str)
{
	int counter = 0;

	char c;
	while (str[counter]) {
		c = str[counter];
		str[counter] = tolower(c);
		counter++;
	}

	return str;
}
