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
	if (m_CurrentToken.Match(Token::TokenType::KEYWORD, std::string("var")))
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
	Node* result = ComExpr();
	while (&m_CurrentToken != nullptr &&
		(m_CurrentToken.Match(Token::TokenType::KEYWORD, "and") ||
			m_CurrentToken.Match(Token::TokenType::KEYWORD, "or")))
	{
		Token currentToken = m_CurrentToken;
		Advance();
		Node* right = ComExpr();
		result = new CompareNode(result, currentToken.GetTokenValue(), right);
	}

	return result;
}

Node* Parser::ComExpr()
{
	if (m_CurrentToken.Match(Token::TokenType::KEYWORD, "not"))
	{
		Advance();
		Node* result = ComExpr();
		return new NotNode(result);
	}

	Node* result = ArthExpr();
	while (
		&m_CurrentToken != nullptr &&
		(m_CurrentToken.GetTokenType() == Token::TokenType::GT ||
			m_CurrentToken.GetTokenType() == Token::TokenType::LT ||
			m_CurrentToken.GetTokenType() == Token::TokenType::GTEQ ||
			m_CurrentToken.GetTokenType() == Token::TokenType::LTEQ ||
			m_CurrentToken.GetTokenType() == Token::TokenType::NEQU ||
			m_CurrentToken.GetTokenType() == Token::TokenType::EQEQ)
		)
	{
		Token currentToken = m_CurrentToken;
		Advance();
		Node* right = ArthExpr();
		result = new CompareNode((Node*)result, currentToken.GetTokenValue(), right);
	}

	return result;
}

Node* Parser::ArthExpr()
{
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
	std::string errStr = "SYNTAX ERROR: " + errorInfo;
	throw errStr;
}

Node* Parser::Power()
{
	Node* result = CallStatement();
	while (&m_CurrentToken != nullptr &&
		m_CurrentToken.GetTokenType() == Token::TokenType::POWER)
	{
		Advance();
		Node* right = Factor();
		result = new PowerNode(result, right);
	}
	return result;
}


Node* Parser::CallStatement()
{
	std::vector<Node*> argNodes;
	Node* atom = Atom();
	if (m_CurrentToken.GetTokenType() == Token::TokenType::L_PAREN)
	{
		Advance();
		if (m_CurrentToken.GetTokenType() != Token::TokenType::R_PAREN)
		{
			Node* argNode = Expr();
			argNodes.emplace_back(argNode);
			while (m_CurrentToken.GetTokenType() == Token::TokenType::COMMA)
			{
				Advance();
				argNode = Expr();
				argNodes.emplace_back(argNode);
			}
			if (m_CurrentToken.GetTokenType() != Token::TokenType::R_PAREN) 
			{
				std::string errStr = "SYNTAX ERROR: Expected ')'";
				throw errStr;
			}
			Advance();
		}
		Advance();
		return new FunctionCallNode(atom, argNodes);
	}
	return atom;
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
	else if (currentToken.GetTokenType() == Token::TokenType::STRING)
	{
		Advance();
		Node* result = new StringNode(currentToken.GetTokenValue());
		return result;
	}
	else if (currentToken.GetTokenType() == Token::TokenType::IDENTIFIER)
	{
		std::string varName = m_CurrentToken.GetTokenValue();
		Advance();
		//if variable is already assigned, use the variable name to reassign value
		Node* result = new VarAccessNode(currentToken.GetTokenValue());
		if (m_CurrentToken.GetTokenType() == Token::TokenType::EQU)
		{
			Advance();

			Node* expr = Expr();
			result = new VarAssignNode(result, expr);
			((VarAssignNode*)result)->SetVarName(varName);
		}
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
	else if (currentToken.Match(Token::TokenType::KEYWORD, "if"))
	{
		Advance();
		Node* ifExpr = IfExpr();
		return ifExpr;
	}
	else if (currentToken.Match(Token::TokenType::KEYWORD, "for"))
	{
		Advance();
		Node* forExpr = ForExpr();
		return forExpr;
	}
	else if (currentToken.Match(Token::TokenType::KEYWORD, "while"))
	{
		Advance();
		Node* whileExpr = WhileExpr();
		return whileExpr;
	}
	else if (currentToken.Match(Token::TokenType::KEYWORD, "function"))
	{
		Advance();
		Node* funcDef = FuncDef();
		return funcDef;
	}
	else if (currentToken.GetTokenType() == Token::TokenType::L_SQUARE) 
	{
		Advance();
		Node* listExpr = ListExpr();
		return listExpr;
	}
	std::string errStr = "SYNTAX ERROR: " + errorInfo;
	throw errStr;
}



Node* Parser::IfExpr()
{
	Node* condition = Expr();
	if (m_CurrentToken.Match(Token::TokenType::KEYWORD, "then") == false)
	{
		std::string errStr = "SYNTAX ERROR: expected 'then' after if statement";
		throw errStr;
	}
	std::vector<IfNode::Case> cases;
	Advance();
	Node* expr = Expr();
	Node* elseCase = nullptr;
	cases.emplace_back(condition, expr);

	while (m_CurrentToken.Match(Token::TokenType::KEYWORD, "elif"))
	{
		Advance();
		Node* condition = Expr();
		if (m_CurrentToken.Match(Token::TokenType::KEYWORD, "then") == false)
		{
			std::string errStr = "SYNTAX ERROR: expected 'then' after if statement";
			throw errStr;
		}
		Advance();
		Node* expr = Expr();
		cases.emplace_back(condition, expr);
	}

	if (m_CurrentToken.Match(Token::TokenType::KEYWORD, "else"))
	{
		Advance();
		elseCase = Expr();

	}
	return new IfNode(cases, elseCase);
}

Node* Parser::ForExpr()
{
	Node* step = nullptr;
	//Advance();
	if (m_CurrentToken.GetTokenType() != Token::TokenType::IDENTIFIER)
	{
		std::string errStr = "SYNTAX ERROR: expected a variable name after 'for'";
		throw errStr;
	}
	std::string varName = m_CurrentToken.GetTokenValue();
	Advance();
	if (m_CurrentToken.GetTokenType() != Token::TokenType::EQU)
	{
		std::string errStr = "SYNTAX ERROR: expected '='";
		throw errStr;
	}
	Advance();

	Node* start = Expr();

	if (m_CurrentToken.Match(Token::TokenType::KEYWORD, "to") == false)
	{
		std::string errStr = "SYNTAX ERROR: expected 'to' after for statement";
		throw errStr;
	}
	Advance();
	Node* end = Expr();
	if (m_CurrentToken.Match(Token::TokenType::KEYWORD, "step"))
	{
		Advance();
		step = Expr();
	}

	if (m_CurrentToken.Match(Token::TokenType::KEYWORD, "then") == false)
	{
		std::string errStr = "SYNTAX ERROR: expected 'then'";
		throw errStr;
	}
	Advance();
	Node* body = Expr();
	return new ForNode(varName, start, end, step, body);
}

Node* Parser::WhileExpr()
{
	Node* condition = Expr();
	if (m_CurrentToken.Match(Token::TokenType::KEYWORD, "then") == false)
	{
		std::string errStr = "SYNTAX ERROR: expected 'then'";
		throw errStr;
	}
	Advance();
	Node* body = Expr();

	return new WhileNode(condition, body);
}

Node* Parser::FuncDef()
{
	std::vector<std::string> argList;
	std::string functionName = "<None>";
	if (m_CurrentToken.GetTokenType() == Token::TokenType::IDENTIFIER)
	{
		functionName = m_CurrentToken.GetTokenValue();
		Advance();

	}
	if (m_CurrentToken.GetTokenType() != Token::TokenType::L_PAREN)
	{
		std::string errStr = "SYNTAX ERROR: expected '('";
		throw errStr;
	}
	Advance();
	if (m_CurrentToken.GetTokenType() == Token::TokenType::IDENTIFIER)
	{
		argList.emplace_back(m_CurrentToken.GetTokenValue());
		Advance();
	}

	while ((m_CurrentToken.GetTokenType() == Token::TokenType::COMMA))
	{
		Advance();
		if (m_CurrentToken.GetTokenType() != Token::TokenType::IDENTIFIER)
		{
			std::string errStr = "SYNTAX ERROR: expected an identifier";
			throw errStr;
		}
		argList.emplace_back(m_CurrentToken.GetTokenValue());

		Advance();
	}

	if (m_CurrentToken.GetTokenType() != Token::TokenType::R_PAREN)
	{
		std::string errStr = "SYNTAX ERROR: expected ')'";
		throw errStr;
	}
	Advance();
	if (m_CurrentToken.GetTokenType() != Token::TokenType::ARROW)
	{
		std::string errStr = "SYNTAX ERROR: expected '=>'";
		throw errStr;
	}
	Advance();
	Node* expr = Expr();
	return new FunctionDefNode(functionName, argList, expr);
}

Node* Parser::ListExpr()
{
	std::vector<Node*> elements;
	elements.emplace_back(Expr());
	while ((m_CurrentToken.GetTokenType() == Token::TokenType::COMMA))
	{
		Advance();
		elements.emplace_back(Expr());
	}
	if (m_CurrentToken.GetTokenType() != Token::TokenType::R_SQUARE)
	{
		std::string errStr = "SYNTAX ERROR: expected ']'";
		throw errStr;
	}
	Advance();
	return new ListNode(elements);
}

void Parser::Dispose(void* obj)
{
	delete (Node*)obj;
}


