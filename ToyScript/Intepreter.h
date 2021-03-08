#pragma once
#include "Values.h"
#include "Node.h"
class Intepreter
{
public:
	Value* Visit(Node* node);
	Value* VisitNumberNode(Node* node);
	Value* VisitAddNode(Node* node);
	Value* VisitSubtractNode(Node* node);
	Value* VisitMultiplyNode(Node* node);
	Value* VisitDivideNode(Node* node);
	Value* VisitPlusNode(Node* node);
	Value* VisitMinusNode(Node* node);
	Value* VisitPowerNode(Node* node);
	Value* VisitModulusNode(Node* node);
private:
	std::string errorInfo;

};

