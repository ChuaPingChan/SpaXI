#include "ProcIdxTable.h"

ProcIdxTable::ProcIdxTable() {

}

bool ProcIdxTable::addToProcIdxTable(string proc, int index) {
    // if variable does not exist as a key, create new list and insert data to hash map
    if (procIdxMap.find(proc) == procIdxMap.end()) {
        procIdxMap[proc] = index;
        return true;
    }
    return false;
}

int ProcIdxTable::getIdxFromProc(string proc) {
    return procIdxMap[proc];
}