#pragma once
#include <string>
class Node
{
public:
	virtual std::string ToString() = 0;
	virtual const char* ToCstr() = 0;
};

class NumberNode : public Node 
{
public:
	NumberNode(std::string value) : m_Value(value){}

	 std::string ToString() override { return m_Value; }
	 const char* ToCstr() override { return m_Value.c_str(); }

	std::string GetValue() { return m_Value; }
private:
	std::string m_Value;
};

class AddNode : public Node 
{
public:
	AddNode(Node* left, Node* right) : 
		m_Left(left), m_Right(right) {}

	Node* GetLeft() { return m_Left; }
	Node* GetRight() { return m_Right; }

	std::string ToString() override { return "(" + m_Left->ToString() + " + " + m_Right->ToString() + ")"; }
	const char* ToCstr() override { return ("(" + m_Left->ToString() + " + " + m_Right->ToString() + ")").c_str(); }
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
	const char* ToCstr() override { return ("(" + m_Left->ToString() + " - " + m_Right->ToString() + ")").c_str(); }
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
	const char* ToCstr() override { return ("(" + m_Left->ToString() + " * " + m_Right->ToString() + ")").c_str(); }

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
	const char* ToCstr() override { return ("(" + m_Left->ToString() + " / " + m_Right->ToString() + ")").c_str(); }

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
	const char* ToCstr() override { return ("(" + m_Left->ToString() + " % " + m_Right->ToString() + ")").c_str(); }

private:
	Node* m_Left;
	Node* m_Right;
};

class PlusNode : public Node 
{
public:
	PlusNode(Node* node) : m_Node(node){}

	std::string ToString() override { return "(+" + m_Node->ToString() + ")"; }
	const char* ToCstr() override { return ("(+" + m_Node->ToString() + ")").c_str(); }
	Node* GetNode() { return m_Node; }
private:
	Node* m_Node;
};

class MinusNode : public Node
{
public:
	MinusNode(Node* node) : m_Node(node) {}

	std::string ToString() override { return "(-" + m_Node->ToString() + ")"; }
	const char* ToCstr() override { return ("(-" + m_Node->ToString() + ")").c_str(); }
	
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
	const char* ToCstr() override { return ("(" + m_Left->ToString() + " ^ " + m_Right->ToString() + ")").c_str(); }

private:
	Node* m_Left;
	Node* m_Right;
};

