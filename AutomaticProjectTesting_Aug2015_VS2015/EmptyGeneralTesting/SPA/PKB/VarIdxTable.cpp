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