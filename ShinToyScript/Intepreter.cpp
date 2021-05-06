
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
	NullValue = symbles.Get("null");
}



RunTimeResult Intepreter::Visit(Node* node)
{
	if (node == nullptr)
	{
		return RunTimeResult();
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
	else if (strcmp(str, "class ReturnNode") == 0)
	{
		return VisitReturnNode(node);
	}
	else if (strcmp(str, "class ContinueNode") == 0)
	{
		return VisitContinueNode(node);
	}
	else if (strcmp(str, "class BreakNode") == 0)
	{
		return VisitBreakNode(node);
	}

	std::string errStr = "MATH ERROR: " + errorInfo;
	throw errStr;
}

RunTimeResult Intepreter::VisitNumberNode(Node* node)
{
	RunTimeResult rt;

	float value = std::stof(((NumberNode*)node)->GetValue());
	Value* num = new NumberValue(value);
	rt.value = num;
	return rt;
}

RunTimeResult Intepreter::VisitStringNode(Node* node)
{
	RunTimeResult rt;
	std::string value = ((NumberNode*)node)->GetValue();
	Value* str = new StringValue(value);
	rt.value = str;

	return rt;
}

RunTimeResult Intepreter::VisitListNode(Node* node)
{
	RunTimeResult rt;
	std::vector<Value*> elements;
	ListNode* listNode = (ListNode*)node;
	for (auto element : listNode->GetElements())
	{
		elements.emplace_back(rt.AscendValue(Visit(element)));
		if (rt.shouldReturn())
			return rt;
	}
	rt.value = new ListValue(elements);
	return rt;
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



RunTimeResult Intepreter::VisitAddNode(Node* node)
{
	RunTimeResult rt;
	Value* left = rt.AscendValue(Visit(((AddNode*)node)->GetLeft()));
	if (rt.shouldReturn())
		return rt;
	Value* right = rt.AscendValue(Visit(((AddNode*)node)->GetRight()));
	if (rt.shouldReturn())
		return rt;

	Value* result = ComputeResult(left, "+", right);
	rt.value = result;
	return rt;
}

RunTimeResult Intepreter::VisitSubtractNode(Node* node)
{
	RunTimeResult rt;
	Value* left = Visit(((SubtractNode*)node)->GetLeft()).value;
	if (rt.shouldReturn())
		return rt;
	Value* right = Visit(((SubtractNode*)node)->GetRight()).value;
	if (rt.shouldReturn())
		return rt;

	Value* result = ComputeResult(left, "-", right);
	rt.value = result;
	return rt;
}

RunTimeResult Intepreter::VisitMultiplyNode(Node* node)
{
	RunTimeResult rt;
	Value* left = Visit(((MultiplyNode*)node)->GetLeft()).value;
	Value* right = Visit(((MultiplyNode*)node)->GetRight()).value;

	//float computeResult = ((NumberValue*)left)->ComputeWith("*", right);

	Value* result = ComputeResult(left, "*", right);
	rt.value = result;
	return rt;
}

RunTimeResult Intepreter::VisitDivideNode(Node* node)
{
	RunTimeResult rt;
	Value* left = Visit(((DivideNode*)node)->GetLeft()).value;
	Value* right = Visit(((DivideNode*)node)->GetRight()).value;

	float computeResult = ((NumberValue*)left)->ComputeWith("/", right);

	Value* result = new NumberValue(computeResult);
	if (std::stof(right->GetValue()) == 0)
	{
		errorInfo = "can not divide by zero";
		throw std::string("Math error: ") + errorInfo;
	}
	else
	{
		rt.value = result;
		return rt;
	}
}

RunTimeResult Intepreter::VisitModulusNode(Node* node)
{
	RunTimeResult rt;
	Value* left = Visit(((ModulusNode*)node)->GetLeft()).value;
	Value* right = Visit(((ModulusNode*)node)->GetRight()).value;

	float computeResult = ((NumberValue*)left)->ComputeWith("%", right);

	Value* result = new NumberValue(computeResult);
	rt.value = result;
	return rt;
}

RunTimeResult Intepreter::VisitVarAccessNode(Node* node)
{
	RunTimeResult rt;
	std::string varName = ((VarAccessNode*)node)->GetVarName();
	Value* result = symbles.Get(varName);
	if (result == nullptr)
	{
		throw "Runtime error: '" + varName + "' is not defined";
	}
	rt.value = result;
	return rt;
}

RunTimeResult Intepreter::VisitVarAssignNode(Node* node)
{
	RunTimeResult rt;
	std::string varName = ((VarAssignNode*)node)->GetVarName();
	Value* value = rt.AscendValue(Visit(((VarAssignNode*)node)->GetRight()));
	if (rt.shouldReturn())
		return rt;
	symbles.set(varName, value);
	rt.value = value;
	return rt;
}

RunTimeResult Intepreter::VisitNotNode(Node* node)
{
	RunTimeResult rt;
	Value* value = Visit(((NotNode*)node)->GetNode()).value;
	if (rt.shouldReturn())
		return rt;
	rt.value = new NumberValue(!std::stoi(value->GetValue()));
	return rt;
}

RunTimeResult Intepreter::VisitCompareNode(Node* node)
{
	RunTimeResult rt;
	Value* leftValue = rt.AscendValue(Visit(((CompareNode*)node)->GetLeft()));
	if (rt.shouldReturn())
		return rt;
	Value* rightValue = rt.AscendValue(Visit(((CompareNode*)node)->GetRight()));
	if (rt.shouldReturn())
		return rt;
	std::string op = ((CompareNode*)node)->GetOp();

	int result = ((NumberValue*)leftValue)->CompareTo(op, (NumberValue*)rightValue);
	rt.value = new NumberValue(result);
	return rt;
}

RunTimeResult Intepreter::VisitIfNode(Node* node)
{
	RunTimeResult rt;
	for (auto c : ((IfNode*)node)->GetCases())
	{
		Value* conditionValue = rt.AscendValue(Visit(c.condition));
		if (rt.shouldReturn())
			return rt;
		int boolValue = std::stoi(((NumberValue*)conditionValue)->GetValue());
		if (boolValue == 1)
		{
			Value* expressionValue = rt.AscendValue(Visit(c.expression));
			if (rt.shouldReturn())
				return rt;
			rt.value = expressionValue;
			return rt;
		}
	}
	if (((IfNode*)node)->GetElseCase() != nullptr)
	{
		Node* elseCase = ((IfNode*)node)->GetElseCase();
		Value* elseValue = rt.AscendValue(Visit(elseCase));
		if (rt.shouldReturn())
			return rt;
		return rt;
	}
	return RunTimeResult();
}


RunTimeResult Intepreter::VisitForNode(Node* node)
{
	RunTimeResult rt;
	Value* startValue = rt.AscendValue(Visit(((ForNode*)node)->GetStart()));
	Value* endValue = rt.AscendValue(Visit(((ForNode*)node)->GetEnd()));
	if (rt.shouldReturn())
		return rt;
	Value* stepValue = nullptr;
	if (((ForNode*)node)->GetStep() != nullptr)
	{
		stepValue = rt.AscendValue(Visit(((ForNode*)node)->GetStep()));
		if (rt.shouldReturn())
			return rt;
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
		Value* value = rt.AscendValue(Visit(((ForNode*)node)->GetExpression()));
		if (rt.shouldReturn())
			return rt;
		if (value->LoopShouldBreak == true)
			break;

		if (value->LoopShouldContinue == true)
			continue;
	}

	rt.value = NullValue;
	return rt;
}

RunTimeResult Intepreter::VisitWhileNode(Node* node)
{
	RunTimeResult rt;
	std::vector<Value*> Elements;
	while (true)
	{
		Value* condition = rt.AscendValue(Visit(((WhileNode*)node)->GetCondition()));
		if (rt.shouldReturn())
			return rt;
		if (std::stoi(((NumberValue*)condition)->GetValue()) != 1)
		{
			break;
		}
		Value* value = rt.AscendValue(Visit(((WhileNode*)node)->GetExpression()));
		if (rt.shouldReturn() && rt.LoopShouldBreak == false && rt.LoopShouldContinue == false)
			return rt;

		if (rt.LoopShouldBreak == true)
		{
			break;
		}

		else if (rt.LoopShouldContinue == true)
		{
			continue;
		}
		Elements.emplace_back(value);
	}
	rt.value = new ListValue(Elements);
	rt.Reset();
	return rt;
}

RunTimeResult Intepreter::VisitCallNode(Node* node)
{
	RunTimeResult rt;
	std::vector<Value*> args;
	FunctionValue* valueToCall = (FunctionValue*)(rt.AscendValue(Visit(((FunctionCallNode*)node)->GetNodeToCall())));
	if (rt.shouldReturn())
		return rt;
	for (auto argNodes : ((FunctionCallNode*)node)->GetArgNodes())
	{
		args.emplace_back(rt.AscendValue(Visit(argNodes)));
		if (rt.shouldReturn())
			return rt;
	}
	rt.value = valueToCall->Execute(*this, symbles, args);
	return rt;
}

RunTimeResult Intepreter::VisitFuncDefNode(Node* node)
{
	RunTimeResult rt;
	std::string functionName = ((FunctionDefNode*)node)->GetFunctionName();
	std::vector<std::string> argNames = ((FunctionDefNode*)node)->GetArgs();
	Node* functionBody = ((FunctionDefNode*)node)->GetBody();
	bool shouldAutoReturn = ((FunctionDefNode*)node)->GetAutoReturn();
	FunctionValue* functionValue = new FunctionValue(functionName, functionBody, argNames, shouldAutoReturn);
	symbles.set(functionName, functionValue);
	rt.value = functionValue;
	return rt;
}

RunTimeResult Intepreter::VisitContinueNode(Node* node)
{
	RunTimeResult rt;
	rt.Reset();
	rt.LoopShouldContinue = true;
	return rt;
}

RunTimeResult Intepreter::VisitReturnNode(Node* node)
{
	RunTimeResult rt;
	if (((ReturnNode*)node)->GetExptToReturn() != nullptr)
	{
		Value* valueToReturn = rt.AscendValue(Visit(((ReturnNode*)node)->GetExptToReturn()));
		if (rt.shouldReturn())
			return rt;
		rt.LoopShouldBreak = true;
		rt.value = new ReturnValue(valueToReturn);
		return rt;
	}
	return rt;
}

RunTimeResult Intepreter::VisitBreakNode(Node* node)
{
	RunTimeResult rt;
	rt.Reset();
	rt.LoopShouldBreak = true;
	return rt;
}


RunTimeResult Intepreter::VisitPlusNode(Node* node)
{
	RunTimeResult rt;
	std::string valueStr = (rt.AscendValue(Visit(((PlusNode*)node)->GetNode())))->GetValue();
	if (rt.shouldReturn())
		return rt;
	float value = std::stof(valueStr);
	Value* num = new NumberValue(value);
	rt.value = num;
	return rt;
}

RunTimeResult Intepreter::VisitMinusNode(Node* node)
{
	RunTimeResult rt;

	std::string valueStr = (rt.AscendValue(Visit(((PlusNode*)node)->GetNode())))->GetValue();
	if (rt.shouldReturn())
		return rt;
	float value = std::stof(valueStr);
	Value* num = new NumberValue(-value);
	rt.value = num;
	return rt;
}

RunTimeResult Intepreter::VisitPowerNode(Node* node)
{
	RunTimeResult rt;
	std::string left = rt.AscendValue(Visit(((PowerNode*)node)->GetLeft()))->GetValue();
	if (rt.shouldReturn())
		return rt;
	std::string right = rt.AscendValue(Visit(((PowerNode*)node)->GetRight()))->GetValue();
	if (rt.shouldReturn())
		return rt;
	float leftValue = std::stof(left);
	float rightValue = std::stof(right);
	Value* num = new NumberValue(pow(leftValue, rightValue));
	rt.value = num;
	return rt;
}

void RunTimeResult::Reset()
{
	LoopShouldBreak = false;
	LoopShouldContinue = false;
}

Value* RunTimeResult::AscendValue(RunTimeResult result)
{
	LoopShouldBreak = result.LoopShouldBreak;
	LoopShouldContinue = result.LoopShouldContinue;
	value = result.value;
	return value;
}

bool RunTimeResult::shouldReturn()
{
	return LoopShouldBreak || LoopShouldContinue;
}
