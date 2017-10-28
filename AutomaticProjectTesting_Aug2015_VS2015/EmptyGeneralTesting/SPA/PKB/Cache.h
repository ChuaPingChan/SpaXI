#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <queue>

using namespace std;

class Cache
{
public:
	Cache();

	bool putAllNextStar(pair<list<int>, list<int>> allNextStar);

	bool containsAllNextStar();

	pair<list<int>, list<int>> getAllNextStar();

private:
	pair<list<int>, list<int>> allNextStarPair;
	bool hasAllNextStar = false;
};