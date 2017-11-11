#include "ProcIdxTable.h"

ProcIdxTable::ProcIdxTable() {

}

/*
Adds given procedure to the procedure index table
*/
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

/*
Gets the index of the procedure,,
returns -1 if procedure does not exist
*/
int ProcIdxTable::getIdxFromProc(string proc) {
    if (procIdxMap.find(proc) == procIdxMap.end()) {
        return -1;
    }

    return procIdxMap[proc];
}

/*
Gets procedure given index
returns empty string if does not exist
*/
string ProcIdxTable::getProcFromIdx(int procIdx) {
    if (procIdxToStringMap.find(procIdx) == procIdxToStringMap.end()) {
        return "";
    }

    return procIdxToStringMap[procIdx];
}

/*
Gets the index of all procedures
*/
list<int> ProcIdxTable::getAllProceduresIndex() {
    return allProcIdx;
}

/*
Gets the names of all procedures
*/
list<string> ProcIdxTable::getAllProceduresName() {
    return allProcString;
}

bool ProcIdxTable::isProcedure(string procName) {
    return procIdxMap.find(procName) != procIdxMap.end();
}

bool ProcIdxTable::addStmtToProc(int stmt, int procIdx) {
    procToStmtMap[procIdx].push_back(stmt);
    stmtToProcMap[stmt] = procIdx;
    return true;
}

int ProcIdxTable::getProcIdxFromStmt(int stmt) {
    if (stmtToProcMap.find(stmt) == stmtToProcMap.end()) {
        return -1;
    }

    return stmtToProcMap[stmt];
}

int ProcIdxTable::getFirstStmtFromProc(int procIdx) {
    if (procToStmtMap.find(procIdx) == procToStmtMap.end()) {
        return -1;
    }

    return procToStmtMap[procIdx].front();
}

list<int> ProcIdxTable::getAllStmtsFromProc(int procIdx) {
    if (procToStmtMap.find(procIdx) == procToStmtMap.end()) {
        return list<int>();
    }

    return procToStmtMap[procIdx];
}