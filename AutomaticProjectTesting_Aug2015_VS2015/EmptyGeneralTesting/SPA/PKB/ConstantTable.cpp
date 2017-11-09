#include "ConstantTable.h"

ConstantTable::ConstantTable()
{
}

/*
This method adds the constant to the PKB
*/
bool ConstantTable::addConstantList(int constant)
{
	constantList.push_back(constant);
	constantList.sort();
	constantList.unique();
	constantSet.insert(constant);
    return true;
}

list<int> ConstantTable::getAllConstants() {
	return constantList;
}

bool ConstantTable::isConstant(int constant) {
	return constantSet.find(constant) != constantSet.end();
}