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
	bool LoopShouldBreak = false;
	bool LoopShouldContinue = false;
	virtual std::string ToString() = 0;
	virtual std::string GetValue() = 0;
	//virtual std::string GetValue() = 0;
	//virtual float ComputeWith(const std::string& op, Value* other) = 0;
};

class ReturnValue : public Value 
{
public:
	ReturnValue(Value* valueToRet) : m_ValueToRet(valueToRet){}
	std::string ToString() { return m_ValueToRet->ToString();}
	std::string GetValue() { return m_ValueToRet->GetValue();}

private:
	Value* m_ValueToRet;
};

class ContinueValue : public Value
{
public:
	std::string ToString() { return "Continue"; }
	std::string GetValue() { return ""; }
};

class BreakValue : public Value
{
public:
	std::string ToString() { return "Break"; }
	std::string GetValue() { return ""; }
};

class NumberValue : public Value 
{
public:
	NumberValue(float value): m_Value(value){}
	std::string ToString() override { return "Value: " + GetValue(); }

	std::string GetValue()  { 
		if((int)m_Value == m_Value)
			return std::to_string((int)m_Value); 
		else 
			return std::to_string(m_Value);
	}

	float GetNumericValue() { return m_Value; }

	int CompareTo(const std::string& op, NumberValue* other);

	float ComputeWith(const std::string& op, Value* other);
private:
	float m_Value;
};

class StringValue : public Value 
{
public:
	StringValue(std::string& value) : m_Value(value) {}
	std::string ToString() override { return "Value: " + m_Value; }

	std::string GetValue() override{ return m_Value; }

	std::string ComputeWith(const std::string& op, Value* other);
private:
	std::string m_Value;
};

class ListValue : public Value 
{
public:
	ListValue(std::vector<Value*>& valueElements): m_ValueElements(valueElements) {}
	std::string ToString() override;

	std::string GetValue() override { return ToString(); }
	std::vector<Value*> GetValueElements() { return m_ValueElements; }

	std::vector<Value*> ComputeWith(const std::string& op, Value* other);
private:
	std::vector<Value*> m_ValueElements;
	std::string m_Value;
};

class FunctionValue : public Value 
{
public:
	FunctionValue(std::string& value, Node* bodyNode, std::vector<std::string>& argNames, bool shouldAutoReturn) : 
		m_Value(value), m_BodyNode(bodyNode), m_ArgNames(argNames), m_ShouldAutoReturn(shouldAutoReturn){}
	std::string ToString() override { return "Function: " + m_Value; }

	std::string GetValue() override { return m_Value; }

	//This is where the programmer-specifed argument are passed in
	virtual Value* Execute(Intepreter& intepreter, SymbleTable& table, std::vector<Value*>& args);
protected:
	std::string m_Value;
	Node* m_BodyNode;
	std::vector<std::string> m_ArgNames;
	bool m_ShouldAutoReturn;
};

class BuiltinFunctionValue : public FunctionValue 
{
	using FunctionValue::FunctionValue;
public:
	BuiltinFunctionValue(std::string value, bool hasDefalutValue) :
		FunctionValue(value, nullptr, m_ArgNames, false), m_HasDefault(hasDefalutValue){}

	Value* Execute(Intepreter& intepreter, SymbleTable& table, std::vector<Value*>& args) override;

	//------Builtin function executions------
	void InitFuncArgs(SymbleTable& table);
	Value* ExecutePrint(SymbleTable& table);
	Value* ExecuteInput(SymbleTable& table);
private:
	bool m_HasDefault;
};
