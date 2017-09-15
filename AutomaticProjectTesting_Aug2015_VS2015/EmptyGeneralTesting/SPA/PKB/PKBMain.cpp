#include "PKBMain.h"

using namespace std;

PKBMain::PKBMain()
{
}

//PARENT
bool PKBMain::setParentChildRel(int parentStmt, int childStmt) {
	return (parentToChildTable.addParentChild(parentStmt, childStmt) && childToParentTable.addChildParent(childStmt, parentStmt));
}

//FOLLOWS
pair<list<int>, list<int>> PKBMain::getAllFollows() {
	return followsTable.getAllFollows();
}

bool PKBMain::hasFollows() {
	for (std::unordered_map<int, int>::iterator it = followsBeforeMap.begin(); it != followsBeforeMap.end(); ++it) {
		int before = (*it).first;
		int after = (*it).second;
		if (before != 0 && after != 0) {
			return true;
		}
	}

	return false;
}

bool PKBMain::setFollowsRel(int stmtBef, int stmtCurr) {
	if (stmtBef != 0) {
		followsAfterMap[stmtBef] = stmtCurr;
	}

	followsBeforeMap[stmtCurr] = stmtBef;

	//if there is a statement before the stmtBef (not the first line of a new nest)
	if (followsBeforeMap.find(stmtBef) != followsBeforeMap.end()) {
		followsTable.addFollows(stmtBef, followsBeforeMap[stmtBef], stmtCurr);
	}

	//add next statement as 0 for all unless if statement if considered above
	//which in that case will be overwritten
	followsTable.addFollows(stmtCurr, stmtBef, 0); 
	return true;
}

bool PKBMain::isAfter(int stmtAft) {
	return followsTable.hasBefore(stmtAft);
}

bool PKBMain::isBefore(int stmtBef) {
	return followsTable.hasAfter(stmtBef);
}

bool PKBMain::isFollows(int stmtBef, int stmtAft) {
	return followsTable.isFollows(stmtBef, stmtAft);
}

int PKBMain::getBefore(int currStmt) {
	if (followsBeforeMap.find(currStmt) == followsBeforeMap.end()) {
		return 0;
	}

	else {
		return followsBeforeMap[currStmt];
	}
}

int PKBMain::getAfter(int currStmt) {
	if (followsAfterMap.find(currStmt) == followsAfterMap.end()) {
		return 0;
	}

	else {
		return followsAfterMap[currStmt];
	}
}

list<int> PKBMain::getAfter(int currStmt, string type) {
	int after = getAfter(currStmt);
	list<int> stmtList;
	list<int> emptyList;
	if (after == 0) {
		return emptyList;
	}

	stmtList.push_back(after);

	if (type == "ASSIGN") {
		/*
		if (isAssignment(after)) {
			return stmtList;
		}
		else {
			return emptyList;
		}
		*/
	}

	if (type == "WHILE") {
		/*
		if (isWhile(after)) {
			return stmtList;
		}
		else {
			return emptyList;
		}
		*/
	}

	return stmtList;
}

list<int> PKBMain::getBefore(int currStmt, string type) {
	int before = getBefore(currStmt);
	list<int> stmtList;
	list<int> emptyList;
	if (before == 0) {
		return emptyList;
	}

	stmtList.push_back(before);

	if (type == "ASSIGN") {
		/*
		if (isAssignment(before) {
		return stmtList;
		}
		else {
		return emptyList;
		}
		*/
	}

	if (type == "WHILE") {
		/*
		if (isWhile(before)) {
		return stmtList;
		}
		else {
		return emptyList;
		}
		*/
	}

	return stmtList;
}

list<int> PKBMain::getAllBefore(string type) {
	list<int> stmtList;
	stmtList = followsTable.getAllBefore();

	if (type == "ASSIGN") {

	}

	if (type == "WHILE") {

	}

	return stmtList;
}

list<int> PKBMain::getAllAfter(string type) {
	list<int> stmtList;
	stmtList = followsTable.getAllAfter();

	if (type == "ASSIGN") {

	}

	if (type == "WHILE") {

	}

	return stmtList;
}

bool PKBMain::startProcessComplexRelations() {
	DesignExtractor de;
	
	return true;
}