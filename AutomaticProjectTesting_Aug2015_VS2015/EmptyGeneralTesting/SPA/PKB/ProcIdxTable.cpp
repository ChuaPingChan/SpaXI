#include "ProcIdxTable.h"

ProcIdxTable::ProcIdxTable() {

}

bool ProcIdxTable::addToProcIdxTable(string proc) {
    // if variable does not exist as a key, create new list and insert data to hash map
    if (procIdxMap.find(proc) == procIdxMap.end()) {
        procIdxMap[proc] = procIdx;
		procIdxToStringMap[procIdx] = proc;
		allProcIdx.push_back(procIdx);
		allProcString.push_back(proc);
        procIdx++;
        return true;
    }
    return false;
}

int ProcIdxTable::getIdxFromProc(string proc) {
	if (procIdxMap.find(proc) == procIdxMap.end()) {
		return -1;
	}

    return procIdxMap[proc];
}

list<int> ProcIdxTable::getAllProceduresIndex() {
	return allProcIdx;
}