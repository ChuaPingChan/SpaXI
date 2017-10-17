#include "NextTable.h"

using namespace std;

NextTable::NextTable() {
}

bool NextTable::setNextRel(int stmt, int stmtNext) {
	string nextRel = to_string(stmt) + "," + to_string(stmtNext);
	if (allNextRel.find(nextRel) != allNextRel.end()) {
		return true;
	}
	nextMap[stmt].push_back(stmtNext);
	nextMapReverse[stmtNext].push_back(stmt);
	prevList.push_back(stmt);
	nextList.push_back(stmtNext);
	allNextRel.insert(nextRel);
	return true;
}

bool NextTable::isNext(int stmtBef, int stmtAft) {
	string nextRel = to_string(stmtBef) + "," + to_string(stmtAft);
	return allNextRel.find(nextRel) != allNextRel.end();
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

bool NextTable::isNextStar(int stmtBef, int stmtAft) {
	unordered_set<int> visited;
	queue<int> toVisit;
	if (nextMap.find(stmtBef) == nextMap.end()) {
		return false;
	}

	list<int> afters = nextMap[stmtBef];
	for (int i : afters) {
		if (i == stmtAft) {
			return true;
		}
		toVisit.push(i);
	}

	while (!toVisit.empty()) {
		int curr = toVisit.front();
		toVisit.pop();
		if (curr == stmtAft) {
			return true;
		}
		if (visited.find(curr) != visited.end()) {
			continue;
		}

		if (nextMap.find(curr) != nextMap.end()) {
			afters = nextMap[curr];
			for (int i : afters) {
				if (i == stmtAft) {
					return true;
				}
				toVisit.push(i);
			}
		}
		visited.insert(curr);
	}

	return false;
}

//TODO implement cache
list<int> NextTable::getExecutedAfterStar(int stmtBef) {
	list<int> afterStar;
	unordered_set<int> visited;
	queue<int> toVisit;
	if (nextMap.find(stmtBef) == nextMap.end()) {
		return afterStar;
	}

	list<int> afters = nextMap[stmtBef];
	for (int i : afters) {
		toVisit.push(i);
		afterStar.push_back(i);
	}

	while (!toVisit.empty()) {
		int curr = toVisit.front();
		toVisit.pop();

		if (visited.find(curr) != visited.end()) {
			continue;
		}
		if (nextMap.find(curr) != nextMap.end()) {
			afters = nextMap[curr];
			for (int i : afters) {
				toVisit.push(i);
				afterStar.push_back(i);
			}
		}
		visited.insert(curr);
	}

	afterStar.sort();
	afterStar.unique();

	return afterStar;
}

list<int> NextTable::getExecutedBeforeStar(int stmtAft) {
	list<int> beforeStar;
	unordered_set<int> visited;
	queue<int> toVisit;
	if (nextMapReverse.find(stmtAft) == nextMapReverse.end()) {
		return beforeStar;
	}

	list<int> befores = nextMapReverse[stmtAft];
	for (int i : befores) {
		toVisit.push(i);
		beforeStar.push_back(i);
	}

	while (!toVisit.empty()) {
		int curr = toVisit.front();
		toVisit.pop();

		if (visited.find(curr) != visited.end()) {
			continue;
		}
		if (nextMapReverse.find(curr) != nextMap.end()) {
			befores = nextMapReverse[curr];
			for (int i : befores) {
				toVisit.push(i);
				beforeStar.push_back(i);
			}
		}
		visited.insert(curr);
	}

	beforeStar.sort();
	beforeStar.unique();

	return beforeStar;
}

pair<list<int>, list<int>> NextTable::getAllNextStar() {
	list<int> befList;
	list<int> aftList;
	list<int> afters;
	int befStmt;
	string currPair;
	queue<int> toVisit;
	unordered_set<string> nextStarRel;
	for (unordered_map<int, list<int>>::iterator it = nextMap.begin(); it != nextMap.end(); ++it) {
		unordered_set<int> visited;
		befStmt = (*it).first;
		afters = (*it).second;

		for (int aftStmt : afters) {
			toVisit.push(aftStmt);
		}

		while (!toVisit.empty()) {
			int aftStmt = toVisit.front();
			toVisit.pop();
			currPair = to_string(befStmt) + "," + to_string(aftStmt);
			if (nextStarRel.find(currPair) != nextStarRel.end()) {
				continue;
			}
			if (visited.find(aftStmt) != visited.end()) {
				continue;
			}
			befList.push_back(befStmt);
			aftList.push_back(aftStmt);
			nextStarRel.insert(currPair);
			if (nextMap.find(aftStmt) != nextMap.end()) {
				for (int i : nextMap[aftStmt]) {
					toVisit.push(i);
				}
			}
			visited.insert(aftStmt);
		}

	}
	return make_pair(befList, aftList);
}
