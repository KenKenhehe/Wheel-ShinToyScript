#include "SymbleTable.h"
#

Value* SymbleTable::Get(std::string varName)
{

	if (symbles.find(varName) != symbles.end())
		return symbles[varName];
	else if (parent != nullptr && (parent->symbles.find(varName) != parent->symbles.end()))
		return parent->symbles[varName];
	else
	{
		std::string nullVarName = varName;
		throw "Exception: variable '" + varName + "' doesn't exist";
	}


}

void SymbleTable::set(std::string name, Value* value)
{
	symbles[name] = value;
}

void SymbleTable::remove(std::string name)
{
	symbles.erase(name);
}
