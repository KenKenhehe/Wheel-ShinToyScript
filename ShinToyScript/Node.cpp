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
