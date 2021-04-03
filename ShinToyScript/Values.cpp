#include "Values.h"
#include "SymbleTable.h"
#include "Intepreter.h"
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

Value* FunctionValue::Execute(Intepreter& intepreter, SymbleTable& table, std::vector<Value*> args)
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
