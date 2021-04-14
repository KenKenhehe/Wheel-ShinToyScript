
#include "Intepreter.h"
#include <typeinfo>
#include <cmath>

void Intepreter::SetSymbles()
{
	symbles.set(std::string("null"), new NumberValue(0));
	symbles.set(std::string("true"), new NumberValue(1));
	symbles.set(std::string("false"), new NumberValue(0));

	symbles.set(std::string("print"), new BuiltinFunctionValue(std::string("print"), false));
	symbles.set(std::string("input"), new BuiltinFunctionValue(std::string("input"), true));
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
	else if (strcmp(str, "class StringNode") == 0)
	{
		return VisitStringNode(node);
	}
	else if (strcmp(str, "class ListNode") == 0) 
	{
		return VisitListNode(node);
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

	else if (strcmp(str, "class IfNode") == 0)
	{
		return VisitIfNode(node);
	}

	else if (strcmp(str, "class ForNode") == 0)
	{
		return VisitForNode(node);
	}
	else if (strcmp(str, "class WhileNode") == 0)
	{
		return VisitWhileNode(node);
	}
	else if (strcmp(str, "class FunctionDefNode") == 0) 
	{
		return VisitFuncDefNode(node);
	}
	else if (strcmp(str, "class FunctionCallNode") == 0)
	{
		return VisitCallNode(node);
	}

	std::string errStr = "MATH ERROR: " + errorInfo;
	throw errStr;
}

Value* Intepreter::VisitNumberNode(Node* node)
{
	float value = std::stof(((NumberNode*)node)->GetValue());
	Value* num = new NumberValue(value);
	return num;
}

Value* Intepreter::VisitStringNode(Node* node)
{
	std::string value = ((NumberNode*)node)->GetValue();
	Value* num = new StringValue(value);
	return num;
}

Value* Intepreter::VisitListNode(Node* node)
{
	std::vector<Value*> elements;
	ListNode* listNode = (ListNode*)node;
	for (auto element : listNode->GetElements()) 
	{
		elements.emplace_back(Visit(element));
	}
	//static ListValue valueToRet(elements);
	return new ListValue(elements);
}

Value* Intepreter::ComputeResult(Value* left, const std::string& op, Value* right)
{
	const char* str = typeid(*left).name();
	const char* strRight = typeid(*right).name();
	Value* result;
	if (strcmp(str, "class NumberValue") == 0) {
		float computeResult = ((NumberValue*)left)->ComputeWith(op, right);
		result = new NumberValue(computeResult);
		return result;
	}
	else if (strcmp(str, "class StringValue") == 0) 
	{
		std::string strResult = ((StringValue*)left)->ComputeWith(op, right);
		result = new StringValue(strResult);
		return result;
	}
	else if (strcmp(str, "class ListValue") == 0) 
	{
		std::vector<Value*> resultList = ((ListValue*)left)->ComputeWith(op, right);
		return new ListValue(resultList);
	}
	return nullptr;
}

Value* Intepreter::VisitAddNode(Node* node)
{
	Value* left = Visit(((AddNode*)node)->GetLeft());
	Value* right = Visit(((AddNode*)node)->GetRight());

	//float computeResult = ((NumberValue*)left)->ComputeWith("+", right);

	Value* result = ComputeResult(left, "+", right);
	return result;
}

Value* Intepreter::VisitSubtractNode(Node* node)
{

	Value* left = Visit(((SubtractNode*)node)->GetLeft());
	Value* right = Visit(((SubtractNode*)node)->GetRight());

	float computeResult = ((NumberValue*)left)->ComputeWith("-", right);


	Value* result = new NumberValue(computeResult);
	return result;
}

Value* Intepreter::VisitMultiplyNode(Node* node)
{
	Value* left = Visit(((MultiplyNode*)node)->GetLeft());
	Value* right = Visit(((MultiplyNode*)node)->GetRight());

	//float computeResult = ((NumberValue*)left)->ComputeWith("*", right);

	Value* result = ComputeResult(left, "*", right);
	return result;
}

Value* Intepreter::VisitDivideNode(Node* node)
{
	Value* left = Visit(((MultiplyNode*)node)->GetLeft());
	Value* right = Visit(((MultiplyNode*)node)->GetRight());

	float computeResult = ((NumberValue*)left)->ComputeWith("/", right);

	Value* result = new NumberValue(computeResult);
	if (std::stof(right->GetValue()) == 0)
	{
		errorInfo = "can not divide by zero";
		throw std::string("Math error: ") + errorInfo;
	}
	else
	{
		return result;
	}
}

Value* Intepreter::VisitModulusNode(Node* node)
{
	Value* left = Visit(((ModulusNode*)node)->GetLeft());
	Value* right = Visit(((ModulusNode*)node)->GetRight());

	float computeResult = ((NumberValue*)left)->ComputeWith("%", right);

	Value* result = new NumberValue(computeResult);
	return result;
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
	return new NumberValue(!std::stoi(value->GetValue()));
}

Value* Intepreter::VisitCompareNode(Node* node)
{
	Value* leftValue = Visit(((CompareNode*)node)->GetLeft());
	Value* rightValue = Visit(((CompareNode*)node)->GetRight());
	std::string op = ((CompareNode*)node)->GetOp();

	int result = ((NumberValue*)leftValue)->CompareTo(op, (NumberValue*)rightValue);
	return new NumberValue(result);
}

Value* Intepreter::VisitIfNode(Node* node)
{
	for (auto c : ((IfNode*)node)->GetCases())
	{
		Value* conditionValue = Visit(c.condition);
		int boolValue = std::stoi(((NumberValue*)conditionValue)->GetValue());
		if (boolValue == 1)
		{
			Value* expressionValue = Visit(c.expression);
			return expressionValue;
		}
	}
	if (((IfNode*)node)->GetElseCase() != nullptr)
	{
		Node* elseCase = ((IfNode*)node)->GetElseCase();
		Value* elseValue = Visit(elseCase);
		return elseValue;
	}
	return nullptr;
}

Value* Intepreter::VisitForNode(Node* node)
{
	Value* startValue = Visit(((ForNode*)node)->GetStart());
	Value* endValue = Visit(((ForNode*)node)->GetEnd());

	Value* stepValue = nullptr;
	if (((ForNode*)node)->GetStep() != nullptr)
	{
		stepValue = Visit(((ForNode*)node)->GetStep());
	}
	else
	{
		stepValue = new NumberValue(1);
	}

	int indexCount = std::stoi(startValue->GetValue());
	int indexDiff = std::stoi(stepValue->GetValue());
	int condition = false;
	if (std::stoi(stepValue->GetValue()) >= 0)
	{
		condition = indexCount < std::stoi(endValue->GetValue());
	}
	else
	{
		condition = indexCount > std::stoi(endValue->GetValue());
	}

	while (condition)
	{
		condition = (std::stoi(stepValue->GetValue()) >= 0) ? 
			indexCount < std::stoi(endValue->GetValue())
			: 
			indexCount > std::stoi(endValue->GetValue());

		symbles.set(((ForNode*)node)->GetVarName(), &NumberValue(indexCount));
		indexCount += indexDiff;
		Visit(((ForNode*)node)->GetExpression());
	}

	return nullptr;
}

Value* Intepreter::VisitWhileNode(Node* node)
{
	while (true)
	{
		Value* condition = Visit(((WhileNode*)node)->GetCondition());
		if (std::stoi(((NumberValue*)condition)->GetValue()) != 1)
		{
			break;
		}
		Visit(((WhileNode*)node)->GetExpression());
	}

	return nullptr;
}

Value* Intepreter::VisitCallNode(Node* node)
{
	std::vector<Value*> args;
	FunctionValue* valueToCall = (FunctionValue*)Visit(((FunctionCallNode*)node)->GetNodeToCall());

	for (auto argNodes : ((FunctionCallNode*)node)->GetArgNodes()) 
	{
		args.emplace_back(Visit(argNodes));
	}
	return valueToCall->Execute(*this, symbles, args);
}

Value* Intepreter::VisitFuncDefNode(Node* node)
{
	std::string functionName = ((FunctionDefNode*)node)->GetFunctionName();
	std::vector<std::string> argNames = ((FunctionDefNode*)node)->GetArgs();
	Node* functionBody = ((FunctionDefNode*)node)->GetBody();
	FunctionValue* functionValue = new FunctionValue(functionName, functionBody, argNames);
	symbles.set(functionName, functionValue);
	return functionValue;
}



Value* Intepreter::VisitPlusNode(Node* node)
{
	std::string valueStr = Visit(((PlusNode*)node)->GetNode())->GetValue();
	float value = std::stof(valueStr);
	Value* num = new NumberValue(value);
	return num;
}

Value* Intepreter::VisitMinusNode(Node* node)
{
	std::string valueStr = Visit(((PlusNode*)node)->GetNode())->GetValue();
	float value = std::stof(valueStr);
	Value* num = new NumberValue(-value);
	return num;
}

Value* Intepreter::VisitPowerNode(Node* node)
{
	std::string left = Visit(((PowerNode*)node)->GetLeft())->GetValue();
	std::string right = Visit(((PowerNode*)node)->GetRight())->GetValue();

	float leftValue = std::stof(left);
	float rightValue = std::stof(right);
	Value* num = new NumberValue(pow(leftValue, rightValue));
	return num;
}







