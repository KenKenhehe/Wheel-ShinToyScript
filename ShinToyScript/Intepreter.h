#pragma once
#include "Values.h"
#include "Node.h"
#include "SymbleTable.h"
class Intepreter
{
public:
	void SetSymbles();
	Value* Visit(Node* node);

	//----------Visit operators------------
	Value* VisitNumberNode(Node* node);
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
private:
	SymbleTable symbles;
	std::string errorInfo;

};

