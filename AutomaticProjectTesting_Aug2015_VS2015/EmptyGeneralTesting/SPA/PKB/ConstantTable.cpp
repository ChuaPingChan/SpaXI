#include "ConstantTable.h"

ConstantTable::ConstantTable()
{
}

bool ConstantTable::addConstantList(int stmtNumber, int constant)
{
    // if stmt number does not exist as a key, create new list and insert data to hash map
    if (constantTableMap.find(stmtNumber) == constantTableMap.end()) {
        constantTableMap[stmtNumber] = list<int>();
        constantTableMap[stmtNumber].push_back(constant);
        return true;
    }
    else {
        // else, expand the list of variables
        constantTableMap[stmtNumber].push_back(constant);
		constantTableMap[stmtNumber].sort();
        constantTableMap[stmtNumber].unique();
        return true;
    }
    return false;
}

list<int> ConstantTable::getStmtConstants(int stmtNumber)
{
    return constantTableMap[stmtNumber];
}

list<int> ConstantTable::getAllConstants() {
	list<int> constantList;
	for (std::unordered_map<int, list<int>>::iterator it = constantTableMap.begin(); it != constantTableMap.end(); ++it) {
		int currStmt = (*it).first;
		list<int> after = (*it).second;
		constantList.insert(constantList.end(), after.begin(), after.end());
		constantList.sort();
		constantList.unique();
	}

	return constantList;
}

bool ConstantTable::hasConstants(int stmtNumber, int constant)
{
    return find(constantTableMap[stmtNumber].begin(),constantTableMap[stmtNumber].end(),constant) != constantTableMap[stmtNumber].end();
}
