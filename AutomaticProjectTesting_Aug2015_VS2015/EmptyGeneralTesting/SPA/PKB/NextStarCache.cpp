#include "NextStarCache.h"

using namespace std;

NextStarCache::NextStarCache() {
}

bool NextStarCache::isComputedBefore(int stmtBef) {
	return nextStarMap.find(stmtBef) != nextStarMap.end();
}

bool NextStarCache::computeStmtBef(int stmtBef, unordered_map<int, list<int>> nextMap) {
	queue<int> toVisit;
	unordered_set<int> visited;
}

bool NextStarCache::computeStmtAft(int stmtAft, unordered_map<int, list<int>> nextMapReverse) {
	queue<int> toVisit;
	unordered_set<int> visited;
}