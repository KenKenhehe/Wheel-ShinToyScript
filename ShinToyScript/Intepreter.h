#pragma once
#include "Values.h"
#include "Node.h"
#include "SymbleTable.h"

class RunTimeResult 
{
public:
	Value* value = nullptr;
	bool LoopShouldBreak = false;
	bool LoopShouldContinue = false;

	void Reset();
	Value* AscendValue(RunTimeResult result);

	bool shouldReturn();

};

class Intepreter
{
public:
	Value* NullValue;

	void SetSymbles();
	void SetBuiltinFunction();
	RunTimeResult Visit(Node* node);

	//----------Visit Data------------
	RunTimeResult VisitNumberNode(Node* node);
	RunTimeResult VisitStringNode(Node* node);
	RunTimeResult VisitListNode(Node* node);

	//----------Visit operators------------
	RunTimeResult VisitAddNode(Node* node);
	RunTimeResult VisitSubtractNode(Node* node);
	RunTimeResult VisitMultiplyNode(Node* node);
	RunTimeResult VisitDivideNode(Node* node);
	RunTimeResult VisitPlusNode(Node* node);
	RunTimeResult VisitMinusNode(Node* node);
	RunTimeResult VisitPowerNode(Node* node);
	RunTimeResult VisitModulusNode(Node* node);

	//----------Visit variable-------------
	RunTimeResult VisitVarAccessNode(Node* node);
	RunTimeResult VisitVarAssignNode(Node* node);

	//----------Visit comparision----------
	RunTimeResult VisitNotNode(Node* node);
	RunTimeResult VisitCompareNode(Node* node);

	//----------If Node----------
	RunTimeResult VisitIfNode(Node* node);

	//----------Loop Nodes----------
	RunTimeResult VisitForNode(Node* node);
	RunTimeResult VisitWhileNode(Node* node);

	//----------Function Nodes----------
	RunTimeResult VisitCallNode(Node* node);
	RunTimeResult VisitFuncDefNode(Node* node);

	RunTimeResult VisitContinueNode(Node* node);
	RunTimeResult VisitReturnNode(Node* node);
	RunTimeResult VisitBreakNode(Node* node);


	//----------Utility-----------------
	Value* ComputeResult(Value* left, const std::string& op, Value* right);
	Value* CompareResult(Value* left, const std::string& op, Value* right);
private:
	SymbleTable symbles;
	std::string errorInfo;

};

