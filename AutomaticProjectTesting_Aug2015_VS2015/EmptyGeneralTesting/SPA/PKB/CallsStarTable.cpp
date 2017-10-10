#include "CallsStarTable.h"

using namespace std;

CallsStarTable::CallsStarTable() {
}

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
			string callsStarRel = to_string(caller) + "," + to_string(callee);
			callsStarRelPairs[callsStarRel] = true;
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
	string callsStarRel = to_string(caller) + "," + to_string(callee);
	return callsStarRelPairs[callsStarRel];
}

pair<list<int>, list<int>> CallsStarTable::getAllCallsStar() {
	return allCallsStar;
}

