#include "Cache.h"

using namespace std;

Cache::Cache() {
}

bool Cache::putAllNextStar(pair<list<int>, list<int>> allNextStar) {
	allNextStarPair = allNextStar;
	hasAllNextStar = true;
	return true;
}

bool Cache::containsAllNextStar() {
	return hasAllNextStar;
}

pair<list<int>, list<int>> Cache::getAllNextStar() {
	return allNextStarPair;
}