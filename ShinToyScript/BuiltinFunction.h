#pragma once
#include "Values.h"
#include <iostream>
class BuiltinFunction
{
public:
	BuiltinFunction(SymbleTable table);
	static Value* ExecutePrint();
};

