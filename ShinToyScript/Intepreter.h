#pragma once
#include "Values.h"
#include "Node.h"
#include "SymbleTable.h"
class Intepreter
{
public:
	void SetSymbles();
	void SetBuiltinFunction();
	Value* Visit(Node* node);

	//----------Visit Data------------
	Value* VisitNumberNode(Node* node);
	Value* VisitStringNode(Node* node);
	Value* VisitListNode(Node* node);

	//----------Visit operators------------
	Value* VisitAddNode(Node* node);
	Value* VisitSubtractNode(Node* node);
	Value* VisitMultiplyNode(Node* node);
	Value* VisitDivideNode(Node* node);
	Value* VisitPlusNode(Node* node);
	Value* VisitMinusNode(Node* node);
	Value* VisitPowerNode(Node* node);
	Value* VisitModulusNode(Node* node);

	//----------Visit variable-------------
	Value* VisitVarAccessNode(Node* node);
	Value* VisitVarAssignNode(Node* node);

	//----------Visit comparision----------
	Value* VisitNotNode(Node* node);
	Value* VisitCompareNode(Node* node);

	//----------If Node----------
	Value* VisitIfNode(Node* node);

	//----------Loop Nodes----------
	Value* VisitForNode(Node* node);
	Value* VisitWhileNode(Node* node);

	//----------Function Nodes----------
	Value* VisitCallNode(Node* node);
	Value* VisitFuncDefNode(Node* node);

	//----------Utility-----------------
	Value* ComputeResult(Value* left, const std::string& op, Value* right);

private:
	SymbleTable symbles;
	std::string errorInfo;

};

