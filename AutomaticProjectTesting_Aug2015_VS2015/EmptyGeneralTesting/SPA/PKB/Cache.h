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

	bool containsAllNextStar(Entity type1, Entity type2);

	pair<list<int>, list<int>> getAllNextStar(Entity type1, Entity type2);

	bool putAllAffects(pair<list<int>, list<int>> allAffects, unordered_map<int, unordered_set<int>> affectsRelMap);

	bool containsAllAffects();

	pair<list<int>, list<int>> getAllAffects();

private:
	pair<list<int>, list<int>> allNextStarPair;
	bool hasAllNextStar = false;
	pair<list<int>, list<int>> allAffectsPair;
	unordered_map<int, unordered_set<int>> affectsRelMap;
	bool hasAllAffects = false;
	unordered_map<int, unordered_map<int, pair<list<int>, list<int>>>> allNextStarPairMap;
};