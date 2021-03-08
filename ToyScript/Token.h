#pragma once
#include <string>
class Token
{
	
public:

	enum class TokenType
	{
		NUMBER,
		PLUS,
		MINUS,
		MUL,
		DIV,
		L_PAREN,
		R_PAREN,
		POWER,
		MODULUS,
		EQU,
		NEW_LINE,
		END_OF_FILE
	};

	Token(TokenType tokenType, std::string tokenValue) :
		m_TokenValue(tokenValue), m_TokenType(tokenType)
	{}

	std::string ToString();

	std::string mapToken(TokenType id);

	TokenType GetTokenType() { return m_TokenType; }
	std::string GetTokenValue() { return m_TokenValue; }

private:
	TokenType m_TokenType;
	std::string m_TokenValue;
};




