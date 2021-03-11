#include "Parser.h"

Parser::Parser(std::vector<Token> tokens) : m_Tokens(tokens), m_CurrentToken(Token(Token::TokenType::END_OF_FILE, ""))
{
	//Create space for token to avoid reallocating space, hence increase performance
	m_Tokens.reserve(tokens.size());

	if (tokens.size() > 0) 
	{
		m_CurrentToken = tokens[m_CurrentIndex];
	}
}

void Parser::Advance()
{
	if (m_CurrentIndex < m_Tokens.size() - 1) 
	{
		m_CurrentIndex++;
		m_CurrentToken = m_Tokens[m_CurrentIndex];
	}
	else 
	{
		m_CurrentToken = Token(Token::TokenType::END_OF_FILE, "EOF");
	}
	
}

Node* Parser::Parse()
{
	if (m_CurrentToken.GetTokenType() == Token::TokenType::END_OF_FILE) 
	{
		return nullptr;
	}

	Node* result = Expr();
	if (m_CurrentToken.GetTokenType() != Token::TokenType::END_OF_FILE) 
	{
		throw std::string("SYNTAX ERROR: ") + m_CurrentToken.GetTokenValue();
	}

	return result;
}


Node* Parser::Expr()
{
	if (m_CurrentToken.Match(Token::TokenType::KEYWORD,std::string("var")) )
	{
		Advance();
		if (m_CurrentToken.GetTokenType() != Token::TokenType::IDENTIFIER) 
		{
			std::string errStr = "SYNTAX ERROR: Expected an identifier";
			throw errStr;
		}
		std::string varName = m_CurrentToken.GetTokenValue();
		Advance();
		if (m_CurrentToken.GetTokenType() != Token::TokenType::EQU) 
		{
			std::string errStr = "SYNTAX ERROR: Expected '='";
			throw errStr;
		}
		Advance();
		Node* expr = Expr();
		//Return var assign node
		Node* result = new VarAssignNode(varName, expr);
		return result;
	}

	Node* result = (Node*)Term();
	while (
		&m_CurrentToken != nullptr &&
		(m_CurrentToken.GetTokenType() == Token::TokenType::PLUS ||
			m_CurrentToken.GetTokenType() == Token::TokenType::MINUS)
		)
	{
		if (m_CurrentToken.GetTokenType() == Token::TokenType::PLUS)
		{
			Advance();
			Node* right = Term();
			result = new AddNode((Node*)result, right);
		}
		else if (m_CurrentToken.GetTokenType() == Token::TokenType::MINUS)
		{
			Advance();
			Node* right = Term();
			result = new SubtractNode((Node*)result, right);
		}
	}

	std::string str = ((Node*)result)->ToString();

	return result;
}

Node* Parser::Term()
{
	Node* result = Factor();
	while (
		&m_CurrentToken != nullptr && 
		(m_CurrentToken.GetTokenType() == Token::TokenType::MUL || 
			m_CurrentToken.GetTokenType() == Token::TokenType::DIV ||
			m_CurrentToken.GetTokenType() == Token::TokenType::MODULUS)
		)
	{
		if (m_CurrentToken.GetTokenType() == Token::TokenType::MUL) 
		{
			Advance();
			Node* right = (Node*)Factor();
			result = new MultiplyNode((Node*)result, right);
		}
		else if (m_CurrentToken.GetTokenType() == Token::TokenType::DIV)
		{
			Advance();
			Node* right = (Node*)Factor();
			result = new DivideNode((Node*)result, right);
		}
		else if (m_CurrentToken.GetTokenType() == Token::TokenType::MODULUS) 
		{
			Advance();
			Node* right = (Node*)Factor();
			result = new ModulusNode((Node*)result, right);
		}
	}

	return result;
}

Node* Parser::Factor()
{
	Token currentToken = m_CurrentToken;
	if (currentToken.GetTokenType() == Token::TokenType::PLUS)
	{
		Advance();
		Node* result = new PlusNode(Power());
		return result;
	}

	else if (m_CurrentToken.GetTokenType() == Token::TokenType::MINUS)
	{
		Advance();
		Node* result = new MinusNode(Power());
		return result;
	}
	else
	{
		Node* result = Power();
		return result;
	}
	std::string errStr =  "SYNTAX ERROR: " + errorInfo; 
	throw errStr;
}

Node* Parser::Power()
{
	Node* result = Atom();
	while(&m_CurrentToken != nullptr && 
		m_CurrentToken.GetTokenType() == Token::TokenType::POWER)
	{
		Advance();
		Node* right = Factor();
		result = new PowerNode(result, right);
	}
	return result;
}

Node* Parser::Atom()
{
	Token currentToken = m_CurrentToken;

	if (currentToken.GetTokenType() == Token::TokenType::NUMBER)
	{
		Advance();
		Node* result = new NumberNode(currentToken.GetTokenValue());
		return result;
	}
	else if (currentToken.GetTokenType() == Token::TokenType::IDENTIFIER) 
	{
		Advance();
		Node* result = new VarAccessNode(currentToken.GetTokenValue());
		return result;
	}
	else if (currentToken.GetTokenType() == Token::TokenType::L_PAREN)
	{
		Advance();
		Node* expr = Expr();
		if (m_CurrentToken.GetTokenType() != Token::TokenType::R_PAREN)
		{
			errorInfo = "Expected ')'";
		}
		else
		{
			Advance();
			return expr;
		}
	}

	std::string errStr = "SYNTAX ERROR: " + errorInfo;
	throw errStr;
}



void Parser::Dispose(void* obj)
{
	delete (Node*)obj;
}


