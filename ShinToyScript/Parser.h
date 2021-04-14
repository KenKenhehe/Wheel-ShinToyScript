#pragma once
#include "Node.h"
#include "Lexer.h"

struct CasesAndElseCase 
{
	std::vector<IfNode::Case> cases;
	Node* elseCase;
};

class Parser
{
public:
	Parser(std::vector<Token> tokens);

	void Advance();
	void Reverse();
	Node* Parse();

	Node* Statements();
	Node* Expr();
	Node* ComExpr();
	Node* ArthExpr();
	Node* Term();
	Node* Factor();
	Node* Power();
	Node* CallStatement();
	Node* Atom();

	Node* IfExprElseIfCase();
	Node* IfExprElseCase();

	Node* IfExpr();

	CasesAndElseCase IfExprCases(const std::string& keyword);

	Node* ForExpr();
	Node* WhileExpr();
	Node* FuncDef();
	Node* ListExpr();


	void Dispose(void* obj);
private:
	std::vector<Token> m_Tokens;
	int m_CurrentIndex = 0;
	Token m_CurrentToken;
	std::string errorInfo;
};

