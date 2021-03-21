#pragma once
#include "Node.h"
#include "Lexer.h"


class Parser
{
public:
	Parser(std::vector<Token> tokens);

	void Advance();
	Node* Parse();

	Node* Expr();
	Node* ComExpr();
	Node* ArthExpr();
	Node* Term();
	Node* Factor();
	Node* Power();
	Node* Atom();
	Node* IfExpr();
	Node* ForExpr();
	Node* WhileExpr();



	void Dispose(void* obj);
private:
	std::vector<Token> m_Tokens;
	int m_CurrentIndex = 0;
	Token m_CurrentToken;
	std::string errorInfo;
};

