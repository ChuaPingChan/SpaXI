#include "NextTable.h"

using namespace std;

NextTable::NextTable() {
}

bool NextTable::setNextRel(int stmt, int stmtNext) {
	nextMap[stmt].push_back(stmtNext);
	nextMapReverse[stmtNext].push_back(stmt);
	prevList.push_back(stmt);
	nextList.push_back(stmtNext);
	string nextRel = to_string(stmt) + "," + to_string(stmtNext);
	allNextRel.insert(nextRel);
	return true;
}

bool NextTable::isNext(int stmtBef, int stmtAft) {
	if (nextMap.find(stmtBef) == nextMap.end()) {
		return false;
	}

	return find(nextMap[stmtBef].begin(), nextMap[stmtBef].end(), stmtAft) != nextMap[stmtBef].end();
}

bool NextTable::isExecutedBefore(int stmtBef) {
	return nextMap.find(stmtBef) != nextMap.end();
}

list<int> NextTable::getExecutedAfter(int stmtBef) {
	if (nextMap.find(stmtBef) == nextMap.end()) {
		return list<int>();
	}

	return nextMap[stmtBef];
}

bool NextTable::hasNext() {
	return !nextMap.empty();
}

list<int> NextTable::getAllExecutedAfter() {
	return nextList;
}

list<int> NextTable::getExecutedBefore(int stmtAft) {
	if (nextMapReverse.find(stmtAft) == nextMapReverse.end()) {
		return list<int>();
	}

	return nextMapReverse[stmtAft];
}

list<int> NextTable::getExecutedBefore() {
	return prevList;
}

bool NextTable::isExecutedAfter(int stmtAft) {
	return nextMapReverse.find(stmtAft) != nextMap.end();
}

list<int> NextTable::getAllExecutedBefore() {
	return prevList;
}

pair<list<int>, list<int>>  NextTable::getAllNext() {
	return make_pair(prevList, nextList);
}

bool NextTable::isNextStar(int stmtBef, int stmtAft, NextStarCache &nextStarCache) {
	if (!nextStarCache.isComputedBefore(stmtBef)) {
		nextStarCache.computeStmtBef(stmtBef, nextMap);
	}
    return true;
}