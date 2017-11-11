#pragma once
#include <stdio.h>
#include <unordered_map>
#include <list>
#include <unordered_set>

using namespace std;

class FollowsStarAfter {
public:
    FollowsStarAfter();

    void setMap(unordered_map<int, list<int>> targetMap);

    list<int> getAfterStar(int stmt);

    bool isAfterStar(int stmtBefore, int stmtAfter);

    list<int> getAllAfterStar();

    pair <list<int>, list<int>> getAllFollows();
private:
    unordered_map<int, list<int>> followsStarAfterMap;
    list<int> beforeList;
    list<int> afterList;
    unordered_map<int, unordered_set<int>> followsStarAfterRelMap;
    pair<list<int>, list<int>> allFollowsStarPair;
};