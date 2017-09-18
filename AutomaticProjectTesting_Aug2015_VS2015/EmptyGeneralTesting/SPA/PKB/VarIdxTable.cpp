#include "VarIdxTable.h"

VarIdxTable::VarIdxTable() {

}

bool VarIdxTable::addToVarIdxTable(string var) {
    // if variable does not exist as a key, create new list and insert data to hash map
    if (varIdxMap.find(var) == varIdxMap.end()) {
        varIdxMap[var] = varIdx;
        varIdx++;
        return true;
    }
    return false;
}

int VarIdxTable::getIdxFromVar(string var) {
	if (varIdxMap.find(var) == varIdxMap.end()) {
		return -1;
	}

    return varIdxMap[var];
}

bool VarIdxTable::isVarPresent(string var)
{
    unordered_map<string, int>::iterator it;
    for (it = varIdxMap.begin(); it != varIdxMap.end(); ++it)
    {
        if (it->first.compare(var) == 0)
        {
            return true;
        }
    }
    return false;
}

list<string> VarIdxTable::getAllVariables() {
	list<string> varList;

	for (unordered_map<string, int>::iterator it = varIdxMap.begin(); it != varIdxMap.end(); ++it) {
		varList.push_back((*it).first);
	}

	return varList;
}
