#include "Values.h"
#include "SymbleTable.h"
#include "Intepreter.h"
#include <iterator>
#include <iostream>
int NumberValue::CompareTo(const std::string& op, NumberValue* other)
{
	if (op == std::string("=="))
	{
		int result = GetNumericValue() == other->GetNumericValue();
		return result;
	}

	else if (op == std::string(">="))
	{
		int result = GetNumericValue() >= other->GetNumericValue();
		return result;
	}
	else if (op == std::string(">"))
	{
		int result = GetNumericValue() > other->GetNumericValue();
		return result;
	}
	else if (op == std::string("<="))
	{
		int result = GetNumericValue() <= other->GetNumericValue();
		return result;
	}
	else if (op == std::string("<"))
	{
		int result = GetNumericValue() < other->GetNumericValue();
		return result;
	}
	else if (op == std::string("!="))
	{
		int result = GetNumericValue() != other->GetNumericValue();
		return result;
	}
	else if (op == std::string("and"))
	{
		int result = GetNumericValue() && other->GetNumericValue();
		return result;
	}
	else if (op == std::string("or"))
	{
		int result = GetNumericValue() || other->GetNumericValue();
		return result;
	}
}

float NumberValue::ComputeWith(const std::string& op, Value* other)
{
	const char* str = typeid(*other).name();
	if (strcmp(str, "class NumberValue") == 0)
	{
		if (op == std::string("+"))
		{
			float result = GetNumericValue() + ((NumberValue*)other)->GetNumericValue();
			return result;
		}
		if (op == std::string("-"))
		{
			float result = GetNumericValue() - ((NumberValue*)other)->GetNumericValue();
			return result;
		}
		if (op == std::string("*"))
		{
			float result = GetNumericValue() * ((NumberValue*)other)->GetNumericValue();
			return result;
		}
		if (op == std::string("/"))
		{
			float result = GetNumericValue() / ((NumberValue*)other)->GetNumericValue();

			return result;
		}
		if (op == std::string("^"))
		{
			float result = pow(GetNumericValue(), ((NumberValue*)other)->GetNumericValue());
			return result;
		}
		if (op == std::string("%"))
		{
			float result = (int)GetNumericValue() % (int)((NumberValue*)other)->GetNumericValue();
			return result;
		}
	}

	std::string err = "Compute error: cannot perform this operation between '";
	throw err + typeid(*this).name() + "' and '" + str + "'";
}

std::string StringValue::ComputeWith(const std::string& op, Value* other)
{
	const char* str = typeid(*other).name();
	if (strcmp(str, "class StringValue") == 0)
	{
		if (op == std::string("+"))
		{
			std::string result = GetValue() + ((StringValue*)other)->GetValue();
			return result;
		}

		if (op == std::string("*"))
		{
			std::string result;
			for (int i = 0; i < ((NumberValue*)other)->GetNumericValue(); i++)
			{
				result += GetValue();
			}
			return result;
		}
	}

	std::string err = "Compute error: cannot perform this operation between '";
	throw err + typeid(*this).name() + "' and '" + str + "'";
}

Value* FunctionValue::Execute(Intepreter& intepreter, SymbleTable& table, std::vector<Value*>& args)
{
	if (args.size() < m_ArgNames.size())
	{
		std::string error = "Runtime Error: Too few argument(s) are passed in. Function: "
			+ m_Value;
		throw error;
	}
	else if (args.size() > m_ArgNames.size())
	{
		std::string error = "Runtime Error: Too much arguments are passed in. Function: "
			+ m_Value;
		throw error;
	}
	for (int i = 0; i < args.size(); i++)
	{
		std::string argName = m_ArgNames[i];
		Value* argValue = args[i];
		table.set(argName, argValue);
	}

	Value* value = intepreter.Visit(m_BodyNode);

	return value;

}

Value* BuiltinFunctionValue::Execute(Intepreter& intepreter, SymbleTable& table, std::vector<Value*>& args)
{
	//Try to reduce copying as much as possible
	m_ArgNames.reserve(args.size());

	InitFuncArgs(table);

	if (args.size() < m_ArgNames.size())
	{
		if (m_HasDefault == false) 
		{
			std::string error = "Runtime Error: Too few argument(s) are passed in. Function: "
				+ m_Value;
			throw error;
		}
	}
	else if (args.size() > m_ArgNames.size())
	{
		std::string error = "Runtime Error: Too much arguments are passed in. Function: "
			+ m_Value;
		throw error;
	}
	for (int i = 0; i < args.size(); i++)
	{
		std::string argName = m_ArgNames[i];
		Value* argValue = args[i];
		table.set(argName, argValue);
	}

	Value* retValue = nullptr;


	if (m_Value == "print") 
	{
		retValue = ExecutePrint(table);
	}
	else if (m_Value == "input") 
	{
		retValue = ExecuteInput(table);
	}
	return retValue;
}

void BuiltinFunctionValue::InitFuncArgs(SymbleTable& table)
{
	m_ArgNames.clear();
	if (m_Value == "print") 
	{
		m_ArgNames.emplace_back("value");
	}
	else if (m_Value == "input") 
	{
		std::string defaultArg = "value";
		std::string none = "";
		table.set(defaultArg, new StringValue(none));
		m_ArgNames.emplace_back(defaultArg);
	}
}

Value* BuiltinFunctionValue::ExecutePrint(SymbleTable& table)
{
	std::string stringValue = table.Get("value")->GetValue();
	std::cout << table.Get("value")->GetValue() << std::endl;
	return new StringValue(stringValue);
}

Value* BuiltinFunctionValue::ExecuteInput(SymbleTable& table)
{
	std::string stringValue = table.Get("value")->GetValue();
	std::cout << table.Get("value")->GetValue() << std::endl;
	std::string input;
	std::cin >> input;
	return new StringValue(input);
}

std::string ListValue::ToString()
{
	std::string elementStrs;
	for (auto c : m_ValueElements) {
		elementStrs = elementStrs + c->ToString() + ", ";
	}
	elementStrs.pop_back();
	elementStrs.pop_back();

	std::string str = "(List: ["
		+ elementStrs + "])";
	return str;
}

std::vector<Value*> ListValue::ComputeWith(const std::string& op, Value* other)
{
	const char* str = typeid(*other).name();
	if (strcmp(str, "class ListValue") == 0)
	{
		std::vector<Value*> resultList = m_ValueElements;
		std::vector<Value*> otherList = ((ListValue*)other)->GetValueElements();
		if (op == std::string("+"))
		{
			resultList.insert(resultList.end(),
				std::make_move_iterator(otherList.begin()),
				std::make_move_iterator(otherList.end())
				);
		}

		return resultList;
	}

	else if (strcmp(str, "class NumberValue") == 0) 
	{
		if (op == std::string("*"))
		{
			std::vector<Value*> resultList = m_ValueElements;
			int num = std::stoi(((NumberValue*)other)->GetValue());

			if (num < 0) 
			{
				std::string err = "Compute error: cannot multiply list with negitive number";
				throw err;
			}

			std::vector<Value*> origininalListToMul = resultList;
			for (int i = 1; i < num; i++) {
				resultList.insert(resultList.end(),
					std::make_move_iterator(origininalListToMul.begin()),
					std::make_move_iterator(origininalListToMul.end())
				);
			}
			return resultList;
		}
	}

	std::string err = "Compute error: cannot perform this operation between '";
	throw err + typeid(*this).name() + "' and '" + str + "'";
}


