#pragma once
#include <unordered_map>
#include "Values.h"
class SymbleTable
{
public:
	Value* Get(std::string varName);
	void set(std::string name, Value* value);
	void remove(std::string name);
	std::unordered_map<std::string, Value*> symbles;
	SymbleTable* parent;
};

