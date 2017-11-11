#include "FollowsTable.h"

using namespace std;

FollowsTable::FollowsTable() {
}
/*
This method adds the follows relation ship
It performs a check to make sure no 0 statements are added
(might be dummy which we used in iteration 1, put here just as a
safety check :p)
*/
bool FollowsTable::addFollows(int before, int after)
{
    if (before != 0 || after != 0) {
        beforeList.push_back(before);
        afterList.push_back(after);
    }
    followsBeforeMap[after] = before;
    followsAfterMap[before] = after;
    return true;
}

int FollowsTable::getStmtBef(int after) {
    if (followsBeforeMap.find(after) == followsBeforeMap.end()) {
        return 0;
    }
    return followsBeforeMap[after];
}

int FollowsTable::getStmtAft(int before) {
    if (followsAfterMap.find(before) == followsAfterMap.end()) {
        return 0;
    }
    return followsAfterMap[before];
}

bool FollowsTable::hasFollows() {
    return !followsBeforeMap.empty();
}
unordered_map<int, int> FollowsTable::getFollowsBeforeMap() {
    return followsBeforeMap;
}

unordered_map<int, int> FollowsTable::getFollowsAfterMap() {
    return followsAfterMap;
}

bool FollowsTable::hasBefore(int afterStmt) {
    return followsBeforeMap.find(afterStmt) != followsBeforeMap.end();
}

bool FollowsTable::hasAfter(int beforeStmt) {
    return followsAfterMap.find(beforeStmt) != followsAfterMap.end();
}

bool FollowsTable::isFollows(int beforeStmt, int afterStmt) {
    if (followsAfterMap.find(beforeStmt) != followsAfterMap.end()) {
        return followsAfterMap[beforeStmt] == afterStmt;
    }

    return false;
}

list<int> FollowsTable::getAllBefore() {
    return beforeList;
}

list<int> FollowsTable::getAllAfter() {
    return afterList;
}

pair<list<int>, list<int>> FollowsTable::getAllFollows() {
    return make_pair(beforeList, afterList);
}