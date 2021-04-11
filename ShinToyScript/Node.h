#pragma once
#include <string>
#include <vector>
class Node
{
public:
	virtual std::string ToString() { return ""; }
	virtual const char* ToCstr() { return ToString().c_str(); }
};

class NumberNode : public Node
{
public:
	NumberNode(std::string value) : m_Value(value) {}

	std::string ToString() override { return m_Value; }

	std::string GetValue() { return m_Value; }
private:
	std::string m_Value;
};

class StringNode : public Node
{
public:
	StringNode(std::string value) : m_Value(value) {}

	std::string ToString() override { return m_Value; }

	std::string GetValue() { return m_Value; }
private:
	std::string m_Value;
};

class ListNode : public Node 
{
public:
	ListNode(std::vector<Node*>& elementNodes) : m_ElementNodes(elementNodes){}
	std::vector<Node*> GetElements() { return m_ElementNodes; }
	std::string ToString() override;
private:
	std::vector<Node*> m_ElementNodes;
};

class AddNode : public Node
{
public:
	AddNode(Node* left, Node* right) :
		m_Left(left), m_Right(right) {}

	Node* GetLeft() { return m_Left; }
	Node* GetRight() { return m_Right; }

	std::string ToString() override { return "(" + m_Left->ToString() + " + " + m_Right->ToString() + ")"; }
private:
	Node* m_Left;
	Node* m_Right;
};

class SubtractNode : public Node
{
public:
	SubtractNode(Node* left, Node* right) :
		m_Left(left), m_Right(right) {}

	Node* GetLeft() { return m_Left; }
	Node* GetRight() { return m_Right; }

	std::string ToString() override { return "(" + m_Left->ToString() + " - " + m_Right->ToString() + ")"; }
private:
	Node* m_Left;
	Node* m_Right;
};

class MultiplyNode : public Node
{
public:
	MultiplyNode(Node* left, Node* right) :
		m_Left(left), m_Right(right) {}

	Node* GetLeft() { return m_Left; }
	Node* GetRight() { return m_Right; }

	std::string ToString() override { return "(" + m_Left->ToString() + " * " + m_Right->ToString() + ")"; }

private:
	Node* m_Left;
	Node* m_Right;
};

class DivideNode : public Node
{
public:
	DivideNode(Node* left, Node* right) :
		m_Left(left), m_Right(right) {}

	Node* GetLeft() { return m_Left; }
	Node* GetRight() { return m_Right; }

	std::string ToString() override { return "(" + m_Left->ToString() + " / " + m_Right->ToString() + ")"; }

private:
	Node* m_Left;
	Node* m_Right;
};

class ModulusNode : public Node
{
public:
	ModulusNode(Node* left, Node* right) :
		m_Left(left), m_Right(right) {}

	Node* GetLeft() { return m_Left; }
	Node* GetRight() { return m_Right; }

	std::string ToString() override { return "(" + m_Left->ToString() + " % " + m_Right->ToString() + ")"; }
	
private:
	Node* m_Left;
	Node* m_Right;
};

class PlusNode : public Node
{
public:
	PlusNode(Node* node) : m_Node(node) {}

	std::string ToString() override { return "(+" + m_Node->ToString() + ")"; }
	Node* GetNode() { return m_Node; }
private:
	Node* m_Node;
};

class MinusNode : public Node
{
public:
	MinusNode(Node* node) : m_Node(node) {}

	std::string ToString() override { return "(-" + m_Node->ToString() + ")"; }
	
	Node* GetNode() { return m_Node; }
private:
	Node* m_Node;
};

class PowerNode : public Node
{
public:
	PowerNode(Node* left, Node* right) :
		m_Left(left), m_Right(right) {}

	Node* GetLeft() { return m_Left; }
	Node* GetRight() { return m_Right; }

	std::string ToString() override { return "(" + m_Left->ToString() + " ^ " + m_Right->ToString() + ")"; }
	
private:
	Node* m_Left;
	Node* m_Right;
};

class VarAssignNode : public Node
{
public:
	VarAssignNode(std::string varName, Node* right) :
		m_VarName(varName), m_Right(right) {}

	VarAssignNode(Node* leftValue, Node* right): 
		m_LeftValue(leftValue), m_Right(right) {}

	std::string ToString() override 
	{ 
		if(m_VarName.empty() == false)
			return "(" + m_VarName + " = " + m_Right->ToString() + ")"; 
		else
			return "(" + m_Right->ToString() + " = " + m_Right->ToString() + ")";

	}
	
	std::string GetVarName() { return m_VarName; }
	Node* GetRight() { return m_Right; }

	Node* GetLeftValue() { return m_LeftValue; }

	void SetVarName(std::string& varName) { m_VarName = varName; }
private:
	std::string m_VarName;
	Node* m_Right;
	Node* m_LeftValue = nullptr;
};


class VarAccessNode : public Node
{
public:
	VarAccessNode(std::string varName) : m_VarName(varName) {}

	std::string ToString() override { return m_VarName; }
	
	std::string GetVarName() { return m_VarName; }
private:
	std::string m_VarName;
};


class NotNode : public Node
{
public:
	NotNode(Node* node) : m_Node(node) {}

	std::string ToString() override { return "(not " + m_Node->ToString() + ")"; }
	
	Node* GetNode() { return m_Node; }
private:
	Node* m_Node;
};

class CompareNode : public Node
{
public:
	CompareNode(Node* leftNode, std::string op, Node* rightNode) :
		m_LeftNode(leftNode),  m_RightNode(rightNode), m_Op(op) {}

	std::string ToString() override { 
		return "(" + m_LeftNode->ToString() + " " + m_Op + " " + m_RightNode->ToString() + ")"; }
	
	Node* GetLeft() { return m_LeftNode; }
	Node* GetRight() { return m_RightNode; }
	std::string GetOp() { return m_Op; }
private:
	Node* m_LeftNode;
	Node* m_RightNode;
	std::string m_Op;
};

class IfNode : public Node 
{
public: 
	struct Case
	{
		Node* condition;
		Node* expression;
		Case(Node* cond, Node* expr): expression(expr), condition(cond){}
	};
public:
	IfNode(std::vector<Case>& cases, Node* elseCase) : m_Cases(cases), m_ElseCase(elseCase) {}

	std::string ToString() override {
		return GetCaseListStr();
	}
	
	std::string GetCaseListStr();
	std::vector<Case> GetCases() { return m_Cases; };
	Node* GetElseCase() { return m_ElseCase; }

private:
	std::vector<Case> m_Cases;
	Node* m_ElseCase;
};

class ForNode : public Node 
{
public:
	ForNode(std::string varNameNode, Node* startNode, Node* endNode, Node* stepNode, Node* expression):
		m_VarName(varNameNode), m_StartNode(startNode), m_EndNode(endNode), 
		m_StepNode(stepNode), m_Expression(expression){}

	//TODO: Implement proper tostring method
	std::string ToString() override;
	std::string GetVarName(){ return m_VarName; }
	Node* GetStart() { return m_StartNode; }
	Node* GetEnd() { return m_EndNode; }
	Node* GetStep() { return m_StepNode; }
	Node* GetExpression() { return m_Expression; }

private:
	std::string m_VarName;
	Node* m_StartNode;
	Node* m_EndNode;
	Node* m_StepNode;
	Node* m_Expression;
};

class WhileNode : public Node 
{
public:
	WhileNode(Node* condition, Node* expression): 
		m_Condition(condition), m_Expression(expression){}
	////TODO: Implement proper tostring method
	std::string ToString() override {
		return "Condition: " + m_Condition->ToString() + ", expression: " + m_Expression->ToString();
	}
	Node* GetCondition() { return m_Condition; }
	Node* GetExpression() { return m_Expression; }

private:
	Node* m_Condition;
	Node* m_Expression;
};

class FunctionDefNode: public Node
{
public:
	FunctionDefNode(std::string functionName, std::vector<std::string>& args, Node* body):
		m_FunctionName(functionName), m_Args(args), m_Body(body)
	{}
	std::string ToString() override;
	std::string GetFunctionName() { return m_FunctionName; }
	std::vector<std::string> GetArgs() { return m_Args; }
	Node* GetBody() { return m_Body; }
private:
	std::string m_FunctionName;
	std::vector<std::string> m_Args;
	Node* m_Body;
};

class FunctionCallNode : public Node 
{
public:
	FunctionCallNode(Node* nodeToCall, std::vector<Node*> argNodes): 
		m_NodeToCall(nodeToCall), m_ArgNodes(argNodes){}
	std::string ToString() override;
	Node* GetNodeToCall() { return m_NodeToCall; }
	std::vector<Node*> GetArgNodes() { return m_ArgNodes; }
private:
	Node* m_NodeToCall;
	std::vector<Node*> m_ArgNodes;
};
