#pragma once
#include <string>
#include <typeinfo>
#include <vector>
#include "Node.h"

class Intepreter;
class SymbleTable;

class Value
{
public:
	virtual std::string ToString() = 0;
	virtual std::string GetValue() = 0;
	//virtual std::string GetValue() = 0;
};

class NumberValue : public Value 
{
public:
	NumberValue(float value): m_Value(value){}
	std::string ToString() override { return "Value: " + std::to_string(m_Value); }

	std::string GetValue()  { return std::to_string(m_Value); }

	float GetNumericValue() { return m_Value; }

	int CompareTo(const std::string& op, NumberValue* other);

	float ComputeWith(const std::string& op, Value* other);
private:
	float m_Value;
};

class StringValue : public Value 
{
public:
	StringValue(std::string value) : m_Value(value) {}
	std::string ToString() override { return "Value: " + m_Value; }

	std::string GetValue() override{ return m_Value; }

	std::string ComputeWith(const std::string& op, Value* other);
private:
	std::string m_Value;
};

class FunctionValue : public Value 
{
public:
	FunctionValue(std::string value, Node* bodyNode, std::vector<std::string> argNames) : 
		m_Value(value), m_BodyNode(bodyNode), m_ArgNames(argNames) {}
	std::string ToString() override { return "Function: " + m_Value; }

	std::string GetValue() override { return m_Value; }

	//This is where the programmer-specifed argument are passed in
	Value* Execute(Intepreter& intepreter, SymbleTable& table, std::vector<Value*> args);
private:
	std::string m_Value;
	Node* m_BodyNode;
	std::vector<std::string> m_ArgNames;
};

