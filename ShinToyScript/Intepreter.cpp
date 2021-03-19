
#include "Intepreter.h"
#include <typeinfo>
#include <cmath>

void Intepreter::SetSymbles()
{
	symbles.set(std::string("null"), new NumberValue(0));
	symbles.set(std::string("true"), new NumberValue(1));
	symbles.set(std::string("false"), new NumberValue(0));

}

Value* Intepreter::Visit(Node* node)
{
	if (node == nullptr) 
	{
		return nullptr;
	}
	const char* str = typeid(*node).name();
	if (strcmp(str, "class NumberNode") == 0)
	{
		return VisitNumberNode(node);
	}
	else if (strcmp(str, "class PlusNode") == 0)
	{
		return VisitPlusNode(node);
	}
	else if (strcmp(str, "class MinusNode") == 0)
	{
		return VisitMinusNode(node);
	}
	else if (strcmp(str, "class AddNode") == 0)
	{
		return VisitAddNode(node);
	}
	else if (strcmp(str, "class SubtractNode") == 0)
	{
		return VisitSubtractNode(node);
	}
	else if (strcmp(str, "class MultiplyNode") == 0)
	{
		return VisitMultiplyNode(node);
	}
	else if (strcmp(str, "class DivideNode") == 0)
	{
		return VisitDivideNode(node);
	}
	else if (strcmp(str, "class ModulusNode") == 0) 
	{
		return VisitModulusNode(node);
	}
	else if (strcmp(str, "class PowerNode") == 0) 
	{
		return VisitPowerNode(node);
	}
	else if (strcmp(str, "class CompareNode") == 0) 
	{
		return VisitCompareNode(node);
	}
	else if (strcmp(str, "class NotNode") == 0) 
	{
		return VisitNotNode(node);
	}
	else if (strcmp(str, "class VarAssignNode") == 0) 
	{
		return VisitVarAssignNode(node);
	}

	else if (strcmp(str, "class VarAccessNode") == 0)
	{
		return VisitVarAccessNode(node);
	}
	

	std::string errStr = "MATH ERROR: " + errorInfo;
	throw errStr;
}

Value* Intepreter::VisitNumberNode(Node* node)
{
	float value = atof(((NumberNode*)node)->GetValue().c_str());
	Value* num = new NumberValue(value);
	return num;
}

Value* Intepreter::VisitAddNode(Node* node)
{
	float leftValue = Visit(((AddNode*)node)->GetLeft())->GetValue();
	float rightValue = Visit(((AddNode*)node)->GetRight())->GetValue();

	Value* result = new NumberValue(leftValue + rightValue);
	return result;
}

Value* Intepreter::VisitSubtractNode(Node* node)
{
	float leftValue = Visit(((SubtractNode*)node)->GetLeft())->GetValue();
	float rightValue = Visit(((SubtractNode*)node)->GetRight())->GetValue();

	Value* result = new NumberValue(leftValue - rightValue);
	return result;
}

Value* Intepreter::VisitMultiplyNode(Node* node)
{
	float leftValue = Visit(((MultiplyNode*)node)->GetLeft())->GetValue();
	float rightValue = Visit(((MultiplyNode*)node)->GetRight())->GetValue();

	Value* result = new NumberValue(leftValue * rightValue);
	return result;
}

Value* Intepreter::VisitDivideNode(Node* node)
{
	float leftValue = Visit(((DivideNode*)node)->GetLeft())->GetValue();
	float rightValue = Visit(((DivideNode*)node)->GetRight())->GetValue();
	if (rightValue == 0)
	{
		errorInfo = "can not divide by zero";
		throw std::string("Math error: ") + errorInfo;
	}
	else
	{
		Value* result = new NumberValue(leftValue / rightValue);
		return result;
	}
}

Value* Intepreter::VisitModulusNode(Node* node)
{
	float leftValue = Visit(((ModulusNode*)node)->GetLeft())->GetValue();
	float rightValue = Visit(((ModulusNode*)node)->GetRight())->GetValue();
	if (rightValue == 0)
	{
		errorInfo = "can not divide by zero";
	}
	else
	{
		Value* result = new NumberValue((int)leftValue % (int)rightValue);
		return result;
	}
}

Value* Intepreter::VisitVarAccessNode(Node* node)
{
	std::string varName = ((VarAccessNode*)node)->GetVarName();
	Value* result = symbles.Get(varName);
	if (result == nullptr) 
	{
		throw "Runtime error: '" + varName + "' is not defined";
	}
	return result;
}

Value* Intepreter::VisitVarAssignNode(Node* node)
{
	std::string varName = ((VarAssignNode*)node)->GetVarName();
	Value* value = Visit(((VarAssignNode*)node)->GetRight());
	symbles.set(varName, value);
	return value;
}

Value* Intepreter::VisitNotNode(Node* node)
{
	Value* value = Visit(((NotNode*)node)->GetNode());
	return new NumberValue(!(int)(value->GetValue()));
}

Value* Intepreter::VisitCompareNode(Node* node)
{
	Value* leftValue = Visit(((CompareNode*)node)->GetLeft());
	Value* rightValue = Visit(((CompareNode*)node)->GetRight());
	std::string op = ((CompareNode*)node)->GetOp();
	
	int result = ((NumberValue*)leftValue)->CompareTo(op, rightValue);
	return new NumberValue(result);
}

Value* Intepreter::VisitPlusNode(Node* node)
{
	float value = Visit(((PlusNode*)node)->GetNode())->GetValue();
	Value* num = new NumberValue(value);
	return num;
}

Value* Intepreter::VisitMinusNode(Node* node)
{
	float value = Visit(((MinusNode*)node)->GetNode())->GetValue();
	Value* num = new NumberValue(-value);
	return num;
}

Value* Intepreter::VisitPowerNode(Node* node)
{
	float leftValue = Visit(((PowerNode*)node)->GetLeft())->GetValue();
	float rightValue = Visit(((PowerNode*)node)->GetRight())->GetValue();

	Value* num = new NumberValue(pow(leftValue, rightValue));
	return num;
}







