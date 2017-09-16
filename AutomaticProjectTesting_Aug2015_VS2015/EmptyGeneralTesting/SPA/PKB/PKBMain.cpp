#include "PKBMain.h"

using namespace std;

PKBMain::PKBMain()
{
}

//PARENT
bool PKBMain::setParentChildRel(int parentStmt, int childStmt) {
	return (parentToChildTable.addParentChild(parentStmt, childStmt) && childToParentTable.addChildParent(childStmt, parentStmt));
}

bool PKBMain::isParentChild(int parentStmt, int childStmt) {
	return parentToChildTable.isParentChild(parentStmt, childStmt);
}

bool PKBMain::isParent(int parentStmt) {
	return parentToChildTable.isParent(parentStmt);
}

list<int> PKBMain::getChildren(int parentStmt, string type) {
	list<int> stmtList = parentToChildTable.getChildren(parentStmt);

	if (type == "stmt") {
		return stmtList;
	}

	/*if (type == "assign") {
		int listSize = stmtList.size();
		int first;
		for (int i = 0; i < listSize; i++) {
			first = stmtList.front();
			stmtList.pop_front();
			if (isAssign(first)) {
				stmtList.push_back(first));
			}
		}
	}*/

	return stmtList;
}

bool PKBMain::isChild(int childStmt) {
	return childToParentTable.isChild(childStmt);
}

bool PKBMain::hasParentRel() {
	return parentToChildTable.empty();
}

list<int> PKBMain::getParent(int childStmt, string type) {
	list<int> stmtList;
	stmtList.push_back(childToParentTable.getParent(childStmt));
	return stmtList;
}

list<int> PKBMain::getAllParents(string type) {
	return parentToChildTable.getAllParents();
}

list<int> PKBMain::getAllChildren(string type) {
	list<int> stmtList = childToParentTable.getAllChildren();

	if (type == "stmt") {
		return stmtList;
	}

	/*if (type == "assign") {
	int listSize = stmtList.size();
	int first;
	for (int i = 0; i < listSize; i++) {
	first = stmtList.front();
	stmtList.pop_front();
	if (isAssign(first)) {
	stmtList.push_back(first));
	}
	}
	}*/

	return stmtList;
}

pair<list<int>, list<int>> PKBMain::getAllParentsRel(string type1, string type2) {
	pair<list<int>, list<int>> allParentsRel = parentToChildTable.getAllParentsRel();
	list<int> parent = allParentsRel.first;
	list<int> children = allParentsRel.second;
	//	int first;
	//	int second;
	/*
	int listSize = parent.size();
	for (int i = 0; i < listSize; i++) {
	if (type1 == "WHILE") {
	first = parent.front();
	parent.pop_front();
	second = children.front();
	children.pop_front();
	if (isWhile(first) {
	parent.push_back(first);
	children.push_back(second);
	}
	}

	if (type1 == "ASSIGN") {
	first = parent.front();
	parent.pop_front();
	second = children.front();
	children.pop_front();
	if (isAssign(first)) {
	parent.push_back(first);
	children.push_back(second);
	}
	}
	}

	int listSize = parent.size();
	for (int i = 0; i < listSize; i++) {
	if (type2 == "WHILE") {
	first = parent.front();
	parent.pop_front();
	second = children.front();
	children.pop_front();
	if (isWhile(second)) {
	parent.push_back(first);
	children.push_back(second);
	}
	}

	if (type2 == "ASSIGN") {
	first = parent.front();
	parent.pop_front();
	second = children.front();
	children.pop_front();
	if (isAssign(second)) {
	parent.push_back(first);
	children.push_back(second);
	}
	}
	}*/

	return make_pair(parent, children);
}

//
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
	if (type == "stmt") {
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
	if (type == "stmt") {
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
	if (type == "stmt") {
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
	if (type == "stmt") {
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
	followsTable.setMap(de.computeFollowsTable(followsBeforeMap, followsAfterMap)));
	childToParentStarTable.setMap(de.computeChildToParentStarTable(childToParentTable));
	parentToChildStarTable.setMap(de.computeParentToChildStarTable(parentToChildTable));
	followsStarAfter.setMap(de.computeFollowsStarAfterTable(followsTable));
	followsStarBefore.setMap(de.computeFollowsStarBeforeTable(followsTable));
	return true;
}

bool PKBMain::isPresent(string var)
{
    VarIdxTable vit;
    return vit.isVarPresent(var);
}

bool PKBMain::isPresent(int stmtNum)
{
    StmtTypeList stmtlist;
    return stmtlist.isPresent(stmtNum);
}

bool PKBMain::isAssignment(int stmtNum)
{
    StmtTypeList list;
    return list.isAssignStmt(stmtNum);
}

bool PKBMain::isWhile(int stmtNum)
{
    StmtTypeList list;
    return list.isWhileStmt(stmtNum);
}

list<int> PKBMain::getAllWhiles()
{
    StmtTypeList list;
    return list.getWhileStmtList();
}
