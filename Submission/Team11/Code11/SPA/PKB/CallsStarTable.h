#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>

using namespace std;

class CallsStarTable
{
public:
    CallsStarTable();
    bool setCallsStarMap(pair<unordered_map<int, list<int>>, unordered_map<int, list<int>>>);
    list<int> getCalleeStar(int caller);
    list<int> getCallerStar(int callee);
    bool isCallsStar(int caller, int callee);
    pair<list<int>, list<int>> getAllCallsStar();
    unordered_map<int, list<int>> getMap();
private:
    unordered_map<int, list<int>> callsStarProcMap;
    unordered_map<int, list<int>> callsStarProcMapReverse;
    unordered_map<int, int> callsStmtToProcMap;
    unordered_map<int, list<int>> callsProcToStmtMap;
    unordered_map <int, unordered_set<int>> callsStarRelMap;
    list<int> callerList;
    list<int> calleeList;
    pair<list<int>, list<int>> allCallsStar;
};