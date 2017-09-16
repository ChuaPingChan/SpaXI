#include "VarIdxTable.h"

VarIdxTable::VarIdxTable() {

}

bool VarIdxTable::addToVarIdxTable(string var, int index) {
    // if variable does not exist as a key, create new list and insert data to hash map
    if (varIdxMap.find(var) == varIdxMap.end()) {
        varIdxMap[var] = index;
        return true;
    }
    return false;
}

int VarIdxTable::getIdxFromVar(string var) {
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
