#pragma once
#include<stdio.h>
#include<string>
#include<vector>
#include<map>
#include<utility>
#include<unordered_map>

using namespace std;

class FollowsTable {
public:
    FollowsTable();

    bool addFollows(int before, int after);

    int getStmtBef(int stmt);

    int getStmtAft(int stmt);

    bool hasFollows();

    unordered_map<int, int> getFollowsBeforeMap();

    unordered_map<int, int> getFollowsAfterMap();

    bool hasBefore(int afterStmt);

    bool hasAfter(int beforeStmt);

    bool isFollows(int stmt1, int stmt2);

    list<int> getAllBefore();

    list<int> getAllAfter();

    pair<list<int>, list<int>> getAllFollows();

private:
    unordered_map<int, pair<int, int>> followsMap;
    unordered_map<int, int> followsBeforeMap;
    unordered_map<int, int> followsAfterMap;
    list<int> beforeList;
    list<int> afterList;
};