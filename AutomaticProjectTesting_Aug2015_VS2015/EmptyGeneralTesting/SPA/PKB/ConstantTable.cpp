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
        constantTableMap[stmtNumber].unique();
        return true;
    }
    else {
        // else, expand the list of variables
        constantTableMap[stmtNumber].push_back(constant);
        constantTableMap[stmtNumber].unique();
        return true;
    }
    return false;
}

list<int> ConstantTable::getConstants(int stmtNumber)
{
    return constantTableMap[stmtNumber];
}

bool ConstantTable::hasConstants(int stmtNumber, int constant)
{
    return find(constantTableMap[stmtNumber].begin(),constantTableMap[stmtNumber].end(),constant) != constantTableMap[stmtNumber].end();
}
