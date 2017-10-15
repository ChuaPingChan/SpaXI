#include "NextTable.h"

using namespace std;

NextTable::NextTable() {
}

bool NextTable::setNextRel(int stmt, int stmtNext) {
	nextMap[stmt].push_back(stmtNext);
	nextMapReverse[stmtNext].push_back(stmt);
	prevList.push_back(stmt);
	nextList.push_back(stmtNext);
	string nextRel = to_string(stmt) + "," + to_string(stmtNext);
	allNextRel.insert(nextRel);
	return true;
}