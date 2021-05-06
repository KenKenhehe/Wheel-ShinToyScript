#include "Node.h"

std::string IfNode::GetCaseListStr()
{
	std::string caseStr;
	for (auto c = begin(m_Cases); c != end(m_Cases); ++c) {
		caseStr += "Condition: " + c->condition->ToString() + 
			", Expression: " + c->expression->ToString() + "\n";
	}
	caseStr.pop_back();
	return caseStr;
}

std::string ForNode::ToString()
{
	std::string stepStr;
	if (m_StepNode != nullptr) 
	{
		stepStr = m_StepNode->ToString();
	}
	else
	{
		stepStr = "None";
	}
	 
	return "Var name: " + m_VarName + ", start: " + 
		m_StartNode->ToString() + ", end: " + m_EndNode->ToString() + 
		", step: " + stepStr + ", expression: " + m_Expression->ToString();
}

std::string FunctionDefNode::ToString()
{
	std::string argStr;
	for (auto c = begin(m_Args); c != end(m_Args); ++c) {
		argStr = argStr + *c + ", ";
	}
	if (strlen(argStr.c_str()) > 0) {
		argStr.pop_back();
		argStr.pop_back();
	}
	std::string str = "Func name: " + m_FunctionName + ", args :(" 
		+ argStr + ")\nexpression: " + m_Body->ToString();

	return str;

}

std::string FunctionCallNode::ToString()
{
	std::string argStr;
	for (auto c : m_ArgNodes) {
		argStr = argStr + c->ToString() + ", ";
	}
	if (strlen(argStr.c_str()) > 0) {
		argStr.pop_back();
		argStr.pop_back();
	}
	std::string str = "[Func to call: " + m_NodeToCall->ToString() + ", args :("
		+ argStr + ")]";

	return str;
}

std::string ListNode::ToString()
{
	std::string elementStrs;
	for (auto c : m_ElementNodes) {
		elementStrs = elementStrs + c->ToString() + ", ";
	}
	elementStrs.pop_back();
	elementStrs.pop_back();

	std::string str = "List: ["
		+ elementStrs + "]";
	return str;
}
