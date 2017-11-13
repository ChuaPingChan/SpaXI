#include "Cache.h"

using namespace std;

Cache::Cache() {
}

/*
This puts all the next star relation into the cache with specified entity
*/
bool Cache::putAllNextStar(pair<list<int>, list<int>> allNextStar, Entity type1, Entity type2) {
    allNextStarPairMap[type1][type2] = allNextStar;
    return true;
}

/*
This sets the maps and reverse maps as well as the general relation map
*/
bool Cache::putAllNextStar(unordered_map<int, list<int>> nextStarMap, unordered_map<int, list<int>> nextStarMapReverse,
    unordered_map<int, unordered_set<int>> nextStarRelMap) {
    this->nextStarMap = nextStarMap;
    this->nextStarMapReverse = nextStarMapReverse;
    this->nextStarRelMap = nextStarRelMap;
    return true;
}

unordered_map<int, list<int>> Cache::getNextStarMap() {
    return nextStarMap;
}

unordered_map<int, list<int>> Cache::getNextStarMapReverse() {
    return nextStarMapReverse;
}

unordered_map<int, unordered_set<int>> Cache::getNextStarRelMap() {
    return nextStarRelMap;
}

/*
Checks if the next star relations pairs are already stored in cache
*/
bool Cache::containsAllNextStar(Entity type1, Entity type2) {
    return (allNextStarPairMap.find(type1) != allNextStarPairMap.end() &&
        allNextStarPairMap[type1].find(type2) != allNextStarPairMap[type1].end());
}

/*
Get all next star relations pair
*/
pair<list<int>, list<int>> Cache::getAllNextStar(Entity type1, Entity type2) {
    if (!containsAllNextStar(type1, type2)) { //safety check
        return make_pair(list<int>(), list<int>());
    }
    return allNextStarPairMap[type1][type2];
}

/*
Adds the affects relation pair and relation map into cache
Does not need to take into account entity as affects is only for
assignment statements
*/
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

/*
Puts all relevant information regarding affects* into the cache
*/
bool Cache::putAllAffectsStar(pair<list<int>, list<int>> allAffectsStar,
    unordered_map<int, unordered_set<int>> affectsStarRelMap, unordered_map<int, list<int>> affectsStarMap,
    unordered_map<int, list<int>> affectsStarMapReverse) {
    this->allAffectsStarPair = allAffectsStar;
    this->affectsStarRelMap = affectsStarRelMap;
    this->affectsStarMap = affectsStarMap;
    this->affectsStarMapReverse = affectsStarMapReverse;
    hasAllAffectsStar = true;
    return true;
}

unordered_map<int, list<int>> Cache::getAffectsStarMap() {
    return affectsStarMap;
}

unordered_map<int, list<int>> Cache::getAffectsStarMapReverse() {
    return affectsStarMapReverse;
}

bool Cache::containsAllAffectsStar() {
    return hasAllAffectsStar;
}

pair<list<int>, list<int>> Cache::getAllAffectsStar() {
    return allAffectsStarPair;
}

unordered_map<int, unordered_set<int>> Cache::getAllAffectsStarRelMap() {
    return affectsStarRelMap;
}

unordered_map<int, unordered_set<int>> Cache::getAllAffectsRelMap() {
    return affectsRelMap;
}

/*
Puts the affects relation into cache with the case of same synonym
*/
bool Cache::putAllAffectsSameSyn(list<int> allAffectsSameSynList) {
    allAffectsSameSyn = allAffectsSameSynList;
    hasAllAffectsSameSyn = true;
    return true;
}

bool Cache::containsAllAffectsSameSyn() {
    return hasAllAffectsSameSyn;
}

list<int> Cache::getAllAffectsSameSyn() {
    return allAffectsSameSyn;
}

/*
Puts the affects* relation into cache with the case of same synonym
*/
bool Cache::putAllAffectsStarSameSyn(list<int> allAffectsStarSameSynList) {
    allAffectsStarSameSyn = allAffectsStarSameSynList;
    hasAllAffectsStarSameSyn = true;
    return true;
}

bool Cache::containsAllAffectsStarSameSyn() {
    return hasAllAffectsStarSameSyn;
}

list<int> Cache::getAllAffectsStarSameSyn() {
    return allAffectsStarSameSyn;
}