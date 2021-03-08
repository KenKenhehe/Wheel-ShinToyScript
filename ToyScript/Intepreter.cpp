
#include "Intepreter.h"
#include <typeinfo>
#include <cmath>

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







