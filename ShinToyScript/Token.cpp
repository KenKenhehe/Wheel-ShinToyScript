#include "Token.h"

std::string Token::ToString()
{
	return "Token type: (" + mapToken(m_TokenType) + "), " + "Token value: " + m_TokenValue;
}

std::string Token::mapToken(TokenType id)
{
	std::string tokenTypeName;
	if (id == TokenType::NUMBER) 
	{
		return "NUMBER";
	}
	else if (id == TokenType::PLUS)
	{
		return "PLUS";
	}
	else if (id == TokenType::MINUS)
	{
		return "MINUS";
	}
	else if (id == TokenType::MUL)
	{
		return "MUL";
	}
	else if (id == TokenType::DIV)
	{
		return "DIV";
	}
	else if (id == TokenType::L_PAREN)
	{
		return "L_PAREN";
	}
	else if (id == TokenType::R_PAREN)
	{
		return "R_PAREN";
	}
	else if (id == TokenType::END_OF_FILE) 
	{
		return "EOF";
	}
	else if (id == TokenType::POWER) 
	{
		return "POWER";
	}
	else if (id == TokenType::MODULUS) 
	{
		return "MODULUS";
	}
	else if (id == TokenType::EQU)
	{
		return "EQU";
	}
	else if (id == TokenType::NEW_LINE) 
	{
		return "NEW_LINE";
	}
	else if (id == TokenType::KEYWORD) 
	{
		return "KEYWORD";
	}
	else if (id == TokenType::IDENTIFIER) 
	{
		return "IDENTIFIER";
	}
	else if (id == TokenType::EQEQ) 
	{
		return "EQEQ";
	}
	else if (id == TokenType::NEQU) 
	{
		return "NEQU";
	}
	else if (id == TokenType::GT) 
	{
		return "GREATER THAN";
	}
	else if (id == TokenType::GTEQ)
	{
		return "GREATER THAN EQUAL TO";
	}
	else if (id == TokenType::LT)
	{
		return "LESS THAN";
	}
	else if (id == TokenType::LTEQ)
	{
		return "LESS THAN EQUAL TO";
	}
	else if (id == TokenType::ARROW) 
	{
		return "ARROW";
	}
	else if (id == TokenType::COMMA) 
	{
		return "COMMA";
	}
	else 
	{
		return "NONE";
	}
}

bool Token::Match(Token::TokenType type, std::string keywordStr)
{
	return GetTokenType() == type && 
		GetTokenValue() == keywordStr;
		
}
