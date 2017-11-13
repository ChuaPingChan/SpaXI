#include "NextTable.h"

using namespace std;

NextTable::NextTable() {
}

bool NextTable::setNextRel(int stmt, int stmtNext) {
    nextMap[stmt].push_back(stmtNext);
    nextMapReverse[stmtNext].push_back(stmt);
    prevList.push_back(stmt);
    nextList.push_back(stmtNext);
    if (stmt != 0 || stmtNext != 0) {
        nextRelMap[stmt].insert(stmtNext);
    }
    return true;
}

bool NextTable::isNext(int stmtBef, int stmtAft) {
    if (nextRelMap.find(stmtBef) != nextRelMap.end()) {
        return nextRelMap[stmtBef].find(stmtAft) != nextRelMap[stmtBef].end();
    }
    return false;
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
    return nextMapReverse.find(stmtAft) != nextMapReverse.end();
}

list<int> NextTable::getAllExecutedBefore() {
    return prevList;
}

pair<list<int>, list<int>>  NextTable::getAllNext() {
    return make_pair(prevList, nextList);
}

/*
This method traverses through the next map to find
if Next*(stmtBef, stmtAft) is true*/
bool NextTable::isNextStar(int stmtBef, int stmtAft) {
    unordered_set<int> visited;
    queue<int> toVisit;
    if (nextMap.find(stmtBef) == nextMap.end()) { //Early termination
        return false;
    }

    list<int> afters = nextMap[stmtBef];
    for (int i : afters) {
        if (i == stmtAft) { //Once found, terminate
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
                if (i == stmtAft) { //Once found, terminate
                    return true;
                }
                toVisit.push(i);
            }
        }
        visited.insert(curr);
    }

    return false;
}

/*
This method gets all the statements executed after the statement
*/
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

/*
This method gets all the statements executed before the
statement.
*/
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
        if (nextMapReverse.find(curr) != nextMapReverse.end()) {
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

/*
This method runs through the CFG for everynode and
populates the respective nextStar relations
*/
pair<list<int>, list<int>> NextTable::getAllNextStar(unordered_map<int, list<int>> &nextStarMap,
    unordered_map<int, list<int>> &nextStarMapReverse, unordered_map<int, unordered_set<int>> &nextStarRelMap) {
    list<int> befList;
    list<int> aftList;
    list<int> afters;
    int befStmt;
    string currPair;
    queue<int> toVisit;
    for (unordered_map<int, list<int>>::iterator it = nextMap.begin(); it != nextMap.end(); ++it) { // Go through every node
		if (AbstractWrapper::GlobalStop) { // If timeout
			return make_pair(befList, aftList);
		}
		unordered_set<int> visited;
        befStmt = (*it).first;
        afters = (*it).second;

        for (int aftStmt : afters) {
            toVisit.push(aftStmt);
        }

        while (!toVisit.empty()) {
            int aftStmt = toVisit.front();
            toVisit.pop();
            if (nextStarRelMap.find(befStmt) != nextStarRelMap.end()
                && nextStarRelMap[befStmt].find(aftStmt) != nextStarRelMap[befStmt].end()) {
                continue;
            }
            if (visited.find(aftStmt) != visited.end()) {
                continue;
            }
            befList.push_back(befStmt);
            aftList.push_back(aftStmt);
            nextStarRelMap[befStmt].insert(aftStmt);
            nextStarMap[befStmt].push_back(aftStmt);
            nextStarMapReverse[aftStmt].push_back(befStmt);
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
