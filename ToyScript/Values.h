#pragma once
#include <string>
class Value
{
public:
	virtual std::string ToString() = 0;
	virtual float GetValue() = 0;
};

class NumberValue : public Value 
{
public:
	NumberValue(float value): m_Value(value){}
	std::string ToString() override { return "Value: " + std::to_string(m_Value); }

	float GetValue() override { return m_Value; }
private:
	float m_Value;
};

