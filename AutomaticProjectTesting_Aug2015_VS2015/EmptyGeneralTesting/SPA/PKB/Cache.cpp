#include "Cache.h"

using namespace std;

Cache::Cache() {
}

bool Cache::putAllNextStar(pair<list<int>, list<int>> allNextStar, Entity type1, Entity type2) {
	allNextStarPairMap[type1][type2] = allNextStar;
	return true;
}

bool Cache::containsAllNextStar(Entity type1, Entity type2) {
	return (allNextStarPairMap.find(type1) != allNextStarPairMap.end() &&
		allNextStarPairMap[type1].find(type2) != allNextStarPairMap[type1].end());
}

pair<list<int>, list<int>> Cache::getAllNextStar(Entity type1, Entity type2) {
	if (!containsAllNextStar(type1, type2)) {
		return make_pair(list<int>(), list<int>());
	}
	return allNextStarPairMap[type1][type2];
}

bool Cache::putAllAffects(pair<list<int>, list<int>> allAffects, unordered_map<int, unordered_set<int>> affectsRelMap) {
	this->allAffectsPair = allAffects;
	this->affectsRelMap = affectsRelMap;
	hasAllAffects = true;
	return true;
}

bool Cache::containsAllAffects() {
	return hasAllAffects;
}

pair<list<int>, list<int>> Cache::getAllAffects() {
	return allAffectsPair;
}

bool Cache::putAllAffectsStar(pair<list<int>, list<int>> allAffectsStar,
	unordered_map<int, unordered_set<int>> affectsStarRelMap) {

	return true;
}

bool Cache::containsAllAffectsStar() {
	return hasAllAffectsStar;
}