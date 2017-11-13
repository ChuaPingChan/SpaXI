#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>
#include "../Entity.h"

using namespace std;

class Cache
{
public:
    Cache();

    bool putAllNextStar(pair<list<int>, list<int>> allNextStar, Entity type1, Entity type2);

    bool putAllNextStar(unordered_map<int, list<int>> nextStarMap, unordered_map<int, list<int>> nextStarMapReverse, unordered_map<int, unordered_set<int>> nextStarRelMap);

    unordered_map<int, list<int>> getNextStarMap();

    unordered_map<int, list<int>> getNextStarMapReverse();

    unordered_map<int, unordered_set<int>> getNextStarRelMap();

    bool containsAllNextStar(Entity type1, Entity type2);

    pair<list<int>, list<int>> getAllNextStar(Entity type1, Entity type2);

    bool putAllAffects(pair<list<int>, list<int>> allAffects, unordered_map<int, unordered_set<int>> affectsRelMap);

    bool containsAllAffects();

    pair<list<int>, list<int>> getAllAffects();

    bool putAllAffectsStar(pair<list<int>, list<int>> allAffectsStar, unordered_map<int, unordered_set<int>> affectsStarRelMap, unordered_map<int, list<int>> affectsStarMap, unordered_map<int, list<int>> affectsStarMapReverse);

    unordered_map<int, list<int>> getAffectsStarMap();

    unordered_map<int, list<int>> getAffectsStarMapReverse();

    bool putAllAffectsStar(pair<list<int>, list<int>> allAffectsStar, unordered_map<int, unordered_set<int>> affectsStarRelMap);

    bool containsAllAffectsStar();

    pair<list<int>, list<int>> getAllAffectsStar();

    unordered_map<int, unordered_set<int>> getAllAffectsStarRelMap();

    unordered_map<int, unordered_set<int>> getAllAffectsRelMap();

    bool putAllAffectsSameSyn(list<int> allAffectsSamSynList);

    bool containsAllAffectsSameSyn();

    list<int> getAllAffectsSameSyn();

    bool putAllAffectsStarSameSyn(list<int> allAffectsStarSameSynList);

    bool containsAllAffectsStarSameSyn();

    list<int> getAllAffectsStarSameSyn();

private:
    pair<list<int>, list<int>> allNextStarPair;
    bool hasAllNextStar = false;
    unordered_map<int, list<int>> nextStarMap;
    unordered_map<int, list<int>> nextStarMapReverse;
    unordered_map<int, unordered_set<int>> nextStarRelMap;
    pair<list<int>, list<int>> allAffectsPair;
    pair<list<int>, list<int>> allAffectsStarPair;
    unordered_map<int, unordered_set<int>> affectsRelMap;
    bool hasAllAffects = false;
    bool hasAllAffectsStar = false;
    bool hasAllAffectsSameSyn = false;
    bool hasAllAffectsStarSameSyn = false;
    list<int> allAffectsSameSyn;
    list<int> allAffectsStarSameSyn;
    unordered_map<int, unordered_map<int, pair<list<int>, list<int>>>> allNextStarPairMap;
    unordered_map<int, unordered_set<int>> affectsStarRelMap;
    unordered_map<int, list<int>> affectsStarMap;
    unordered_map<int, list<int>> affectsStarMapReverse;
};