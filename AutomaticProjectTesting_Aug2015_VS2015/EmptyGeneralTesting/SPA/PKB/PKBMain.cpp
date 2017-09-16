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
pair<list<int>, list<int>> PKBMain::getAllFollows(string type1, string type2) {
	pair<list<int>, list<int>> allFollows = followsTable.getAllFollows();
	list<int> bef = allFollows.first;
	list<int> aft = allFollows.second;
//	int first;
//	int second;
	/*
	int listSize = bef.size();
	for (int i = 0; i < listSize; i++) {
		if (type1 == "WHILE") {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isWhile(first) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}

		if (type1 == "ASSIGN") {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isAssign(first)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}
	}

	int listSize = bef.size();
	for (int i = 0; i < listSize; i++) {
		if (type2 == "WHILE") {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isWhile(second)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}

		if (type2 == "ASSIGN") {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isAssign(second)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}
	}*/

	return make_pair(bef, aft);
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

bool PKBMain::isFollowsStar(int befStmt, int aftStmt) {
	return followsStarAfter.isAfterStar(befStmt, aftStmt);
}

list<int> PKBMain::getAfterStar(int befStmt, string type) {
	list<int> aft = followsStarAfter.getAfterStar(befStmt);
	int first;
	int listSize = aft.size();
	if (type == "STMT") {
		return aft;
	}
	/*
	for (int i = 0; i < listSize; i++) {
		first = aft.front();
		aft.pop_front();
		if (type == "WHILE") {
			if (isWhile(first)) {
				aft.push_back(first);
			}
		}
		if (type == "ASSIGN") {
			if (isAssign(first)) {
				aft.push_back(first);
			}

		}
	}*/
	return aft;
}

list<int> PKBMain::getBeforeStar(int aftStmt, string type) {
	list<int> bef = followsStarBefore.getBeforeStar(aftStmt);
	int first;
	int listSize = bef.size();
	if (type == "STMT") {
		return bef;
	}
	/*
	for (int i = 0; i < listSize; i++) {
		first = bef.front();
		bef.pop_front();
		if (type == "WHILE") {
			if (isWhile(first)) {
				bef.push_back(first);
			}
		}
		if (type == "ASSIGN") {
			if (isAssign(first)) {
				bef.push_back(first));
			}
		}*/

	return bef;
}

list<int> PKBMain::getAllBeforeStar(string type) {
	list<int> bef = followsStarBefore.getAllBeforeStar();
	int first;
	int listSize = bef.size();
	if (type == "STMT") {
		return bef;
	}
	/*
	for (int i = 0; i < listSize; i++) {
		first = bef.front();
		bef.pop_front();
		if (type == "WHILE") {
			if (isWhile(first)) {
				bef.push_back(first);
			}
		}
		if (type == "ASSIGN") {
			if (isAssign(first)) {
				bef.push_back(first));
			}
		}*/

	return bef;
}

list<int> PKBMain::getAllAfterStar(string type) {
	list<int> aft = followsStarAfter.getAllAfterStar();
	int first;
	int listSize = aft.size();
	if (type == "STMT") {
		return aft;
	}

	/*
	for (int i = 0; i < listSize; i++) {
	first = aft.front();
	aft.pop_front();
	if (type == "WHILE") {
	if (isWhile(first)) {
	aft.push_back(first);
	}
	}
	if (type == "ASSIGN") {
	if (isAssign(first)) {
	aft.push_back(first));
	}
	}*/

	return aft;
}

pair<list<int>, list<int>> PKBMain::getAllFollowsStar(string type1, string type2) {
	pair<list<int>, list<int>> allFollows = followsStarAfter.getAllFollows();
	list<int> bef = allFollows.first;
	list<int> aft = allFollows.second;
	//	int first;
	//	int second;
	/*
	int listSize = bef.size();
	for (int i = 0; i < listSize; i++) {
	if (type1 == "WHILE") {
	first = bef.front();
	bef.pop_front();
	second = aft.front();
	aft.pop_front();
	if (isWhile(first) {
	bef.push_back(first);
	aft.push_back(second);
	}
	}

	if (type1 == "ASSIGN") {
	first = bef.front();
	bef.pop_front();
	second = aft.front();
	aft.pop_front();
	if (isAssign(first)) {
	bef.push_back(first);
	aft.push_back(second);
	}
	}
	}

	int listSize = bef.size();
	for (int i = 0; i < listSize; i++) {
	if (type2 == "WHILE") {
	first = bef.front();
	bef.pop_front();
	second = aft.front();
	aft.pop_front();
	if (isWhile(second)) {
	bef.push_back(first);
	aft.push_back(second);
	}
	}

	if (type2 == "ASSIGN") {
	first = bef.front();
	bef.pop_front();
	second = aft.front();
	aft.pop_front();
	if (isAssign(second)) {
	bef.push_back(first);
	aft.push_back(second);
	}
	}
	}*/

	return make_pair(bef, aft);
}

bool PKBMain::startProcessComplexRelations() {
	DesignExtractor de;
	childToParentStarTable.setMap(de.computeChildToParentStarTable(childToParentTable));
	parentToChildStarTable.setMap(de.computeParentToChildStarTable(parentToChildTable));
	followsStarAfter.setMap(de.computeFollowsStarAfterTable(followsTable));
	followsStarBefore.setMap(de.computeFollowsStarBeforeTable(followsTable));
	return true;
}

