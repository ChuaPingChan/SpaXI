#include "VarIdxTable.h"

VarIdxTable::VarIdxTable() {

}

/*
Populate variable index table*/
bool VarIdxTable::addToVarIdxTable(string var) {
    // if variable does not exist as a key, create new list and insert data to hash map
    if (varIdxMap.find(var) == varIdxMap.end()) {
        varIdxMap[var] = varIdx;
		allVarIdx.push_back(varIdx);
		varIdxToStringMap[varIdx] = var;
		allVarString.push_back(var);
        varIdx++;

        return true;
    }
    return true;
}

int VarIdxTable::getIdxFromVar(string var) {
	if (varIdxMap.find(var) == varIdxMap.end()) {
		return -1;
	}

    return varIdxMap[var];
}

string VarIdxTable::getVarFromIdx(int idx) {
	if (varIdxToStringMap.find(idx) == varIdxToStringMap.end()) {
		return "";
	}

	return varIdxToStringMap[idx];
}

bool VarIdxTable::isVarPresent(string var)
{
	return varIdxMap.find(var) != varIdxMap.end();
}

list<string> VarIdxTable::getAllVariables() {
	allVarString;
}

list<int> VarIdxTable::getAllVariablesIndex() {
	return allVarIdx;
}