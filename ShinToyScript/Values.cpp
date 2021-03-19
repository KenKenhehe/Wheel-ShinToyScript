#include "Values.h"

int NumberValue::CompareTo(const std::string& op, Value* other)
{
	if (op == std::string("==")) 
	{
		int result = GetValue() == other->GetValue();
		return result;
	}

	else if (op == std::string(">="))
	{
		int result = GetValue() >= other->GetValue();
		return result;
	}
	else if (op == std::string(">"))
	{
		int result = GetValue() > other->GetValue();
		return result;
	}
	else if (op == std::string("<="))
	{
		int result = GetValue() <= other->GetValue();
		return result;
	}
	else if (op == std::string("<"))
	{
		int result = GetValue() < other->GetValue();
		return result;
	}
	else if (op == std::string("!="))
	{
		int result = GetValue() != other->GetValue();
		return result;
	}
	else if (op == std::string("and"))
	{
		int result = GetValue() && other->GetValue();
		return result;
	}
	else if (op == std::string("or"))
	{
		int result = GetValue() || other->GetValue();
		return result;
	}
}
