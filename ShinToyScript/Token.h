#pragma once
#include <string>
class Token
{
	
public:

	enum class TokenType
	{
		NUMBER,
		IDENTIFIER,
		KEYWORD,
		PLUS,
		MINUS,
		MUL,
		DIV,
		L_PAREN,
		R_PAREN,
		POWER,
		MODULUS,
		EQU,
		EQEQ,
		NEQU,
		GT,
		LT,
		LTEQ,
		GTEQ,
		COMMA,
		ARROW,
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

	bool Match(Token::TokenType type, std::string keywordStr);

private:
	TokenType m_TokenType;
	std::string m_TokenValue;
};




