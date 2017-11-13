#include "FollowsStarBefore.h"

using namespace std;

FollowsStarBefore::FollowsStarBefore() {
}

/*
Populate the required data by iteration through the map
*/
void FollowsStarBefore::setMap(unordered_map<int, list<int>> targetMap) {
    int after;
    for (auto it : targetMap) {
        after = it.first;
        list<int> targetList = it.second;
        for (int before : targetList) {
            beforeList.push_back(before);
            afterList.push_back(after);
            followsStarBeforeRelMap[after].insert(before);
        }
    }
    beforeList.sort();
    beforeList.unique();
    afterList.sort();
    afterList.unique();
    followsStarBeforeMap = targetMap;
}

list<int> FollowsStarBefore::getBeforeStar(int stmt) {
    if (followsStarBeforeMap.find(stmt) == followsStarBeforeMap.end()) {
        return list<int>();
    }

    return followsStarBeforeMap[stmt];
}

bool FollowsStarBefore::isBeforeStar(int stmtBefore, int stmtAfter) {
    if (followsStarBeforeRelMap.find(stmtAfter) != followsStarBeforeRelMap.end()) {
        return followsStarBeforeRelMap[stmtAfter].find(stmtBefore) != followsStarBeforeRelMap[stmtAfter].end();
    }
    return false;
}

list<int> FollowsStarBefore::getAllBeforeStar() {
    return beforeList;
}