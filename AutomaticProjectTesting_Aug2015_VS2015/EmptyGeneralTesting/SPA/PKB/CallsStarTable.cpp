#include "CallsStarTable.h"

using namespace std;

CallsStarTable::CallsStarTable() {
}

/*
This method sets the call star map from the one we generated in design extractor
It will iterate all relations and populate the required tables
*/
bool CallsStarTable::setCallsStarMap(pair<unordered_map<int, list<int>>, unordered_map<int, list<int>>> callsStarPair) {
    callsStarProcMap = callsStarPair.first;
    callsStarProcMapReverse = callsStarPair.second;

    for (std::unordered_map<int, list<int>>::iterator it = callsStarProcMap.begin(); it != callsStarProcMap.end(); ++it) {
        int caller = (*it).first;
        int callee;
        list<int> callees = (*it).second;
        for (list<int>::iterator it2 = callees.begin(); it2 != callees.end(); ++it2) {
            callerList.push_back(caller);
            callee = (*it2);
            calleeList.push_back(*it2);
            callsStarRelMap[caller].insert(callee);
        }
    }

    allCallsStar = make_pair(callerList, calleeList);
    return true;
}

list<int> CallsStarTable::getCalleeStar(int caller) {
    return callsStarProcMap[caller];
}

list<int> CallsStarTable::getCallerStar(int callee) {
    return callsStarProcMapReverse[callee];
}

bool CallsStarTable::isCallsStar(int caller, int callee) {
    if (callsStarRelMap.find(caller) == callsStarRelMap.end()) {
        return false;
    }
    return callsStarRelMap[caller].find(callee) != callsStarRelMap[caller].end();
}

pair<list<int>, list<int>> CallsStarTable::getAllCallsStar() {
    return allCallsStar;
}

unordered_map<int, list<int>> CallsStarTable::getMap() {
    return callsStarProcMap;
}
