#include "PKBMain.h"

using namespace std;

PKBMain* PKBMain::singleton = NULL;

PKBMain::PKBMain()
{
}

PKBMain* PKBMain::getInstance()
{
    if (singleton == NULL) {
        singleton = new PKBMain();
    }
    return singleton;
}

void PKBMain::resetInstance()
{
    delete singleton;
    singleton = NULL;
    singleton = new PKBMain();
}

//Utility functions
list<string> PKBMain::convertIdxToString(list<int> indexList, Entity type) {
	list<string> resultString;
	list<int>::iterator it;
	if (type == PROCEDURE) {
		for (it = indexList.begin(); it != indexList.end(); ++it) {
			resultString.push_back(prodIdxTable.)
		}
	}

	if (type == VARIABLE) {
		for (it = indexList.begin; it != indexList.end(); ++it) {

		}
	}
}

//CALLS
bool PKBMain::setCallsRel(int stmt, string callerProcName, string calleeProcName) {
	int callerProcIdx = procIdxTable.getIdxFromProc(callerProcName);
	stmtTypeList.addToCallsStmtList(stmt);
	if (procIdxTable.getIdxFromProc(calleeProcName) == -1) {
		procIdxTable.addToProcIdxTable(calleeProcName);
	}
	int calleeProcIdx = procIdxTable.getIdxFromProc(calleeProcName);
	return callsTable.addCallsRel(callerProcIdx, calleeProcIdx) && callsTable.addCallsStmt(stmt, calleeProcIdx);
}

bool PKBMain::isCalls(string callerProcName, string calleeProcName) {
	int callerProcIdx = procIdxTable.getIdxFromProc(callerProcName);
	int calleeProcIdx = procIdxTable.getIdxFromProc(calleeProcName);

	if (callerProcIdx == -1 || calleeProcIdx == -1) {
		return false;
	}

	return callsTable.isCalls(callerProcIdx, calleeProcIdx);
}

bool PKBMain::isCaller(string callerProcName) {
	int callerProcIdx = procIdxTable.getIdxFromProc(callerProcName);
	return callsTable.isCaller(callerProcIdx);
}

list<int> PKBMain::getCallee(string callerProcName) {
	int callerProcIdx = procIdxTable.getIdxFromProc(callerProcName);
	return callsTable.getCallee(callerProcIdx);
}

bool PKBMain::isCallee(string calleeProcName) {
	int calleeProcIdx = procIdxTable.getIdxFromProc(calleeProcName);
	return callsTable.isCaller(calleeProcIdx);
}

bool PKBMain::hasCalls() {
	return callsTable.hasCalls();
}

list<int> PKBMain::getAllCallees() {
	return callsTable.getAllCallees();
}

list<int> PKBMain::getCaller(string calleeProcName) {
	int calleeProcIdx = procIdxTable.getIdxFromProc(calleeProcName);
	return callsTable.getCaller(calleeProcIdx);
}

list<int> PKBMain::getAllCallers() {
	return callsTable.getAllCallers();
}

pair<list<int>, list<int>> PKBMain::getAllCalls() {
	return callsTable.getAllCalls();
}

bool PKBMain::isCallsStar(string callerProcName, string calleeProcName) {
	int callerProcIdx = procIdxTable.getIdxFromProc(callerProcName);
	int calleeProcIdx = procIdxTable.getIdxFromProc(calleeProcName);

	return callsStarTable.isCallsStar(callerProcIdx, calleeProcIdx);
}

list<int> PKBMain::getCalleeStar(string callerProcName) {
	int callerProcIdx = procIdxTable.getIdxFromProc(callerProcName);
	return callsStarTable.getCalleeStar(callerProcIdx);
}

list<int> PKBMain::getCallerStar(string calleeProcName) {
	int calleeProcIdx = procIdxTable.getIdxFromProc(calleeProcName);
	return callsStarTable.getCallerStar(calleeProcIdx);
}

pair<list<int>, list<int>> PKBMain::getAllCallsStar() {
	return callsStarTable.getAllCallsStar();
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

list<int> PKBMain::getChildren(int parentStmt, Entity type) {
	list<int> stmtList = parentToChildTable.getChildren(parentStmt);

	if (type == STMT) {
		return stmtList;
	}

	if (type == ASSIGN) {
		int listSize = stmtList.size();
		int first;
		for (int i = 0; i < listSize; i++) {
			first = stmtList.front();
			stmtList.pop_front();
			if (isAssignment(first)) {
				stmtList.push_back(first);
			}
		}
	}

	return stmtList;
}

bool PKBMain::isChild(int childStmt) {
	return childToParentTable.isChild(childStmt);
}

bool PKBMain::hasParentRel() {
	return !parentToChildTable.empty();
}

list<int> PKBMain::getParent(int childStmt, Entity type) {
	list<int> stmtList;
	int parentStmt = childToParentTable.getParent(childStmt);
	if (type == WHILE) {
		if (isWhile(parentStmt)) {
			stmtList.push_back(parentStmt);
		}
	}
//TODO 1 implement once isIf is done
/*	if (type == IF) {
		if (isIf(parentStmt)) {
			stmtList.push_back(parentStmt);
		}
	}
	*/

	return stmtList;
}

list<int> PKBMain::getAllParents(Entity type) {
	//TODO 1 implement entity search
	return parentToChildTable.getAllParents();
}

list<int> PKBMain::getAllChildren(Entity type) {
	list<int> stmtList = childToParentTable.getAllChildren();
	//TODO 3 change if possible, the way to get all children of certain type
	if (type == STMT) {
		return stmtList;
	}

	if (type == ASSIGN) {
		int listSize = stmtList.size();
		int first;
		for (int i = 0; i < listSize; i++) {
			first = stmtList.front();
			stmtList.pop_front();
			if (isAssignment(first)) {
				stmtList.push_back(first);
			}
		}
	}

	return stmtList;
}


bool PKBMain::isParentStarChild(int parentStmt, int childStmt) {
	return parentToChildStarTable.isParentStarChild(parentStmt, childStmt);
}

list<int> PKBMain::getChildrenStar(int parentStmt, Entity type) {
	list<int> childStmt = parentToChildStarTable.getChildren(parentStmt);
	if (type == STMT) {
		return childStmt;
	}
	int listSize = childStmt.size();
	int first;
	if (type == WHILE) {
		for (int i = 0; i < listSize; i++) {
			first = childStmt.front();
			childStmt.pop_front();
			if (isWhile(first)) {
				childStmt.push_back(first);
			}
		}
	}

	if (type == ASSIGN) {
		for (int i = 0; i < listSize; i++) {
			first = childStmt.front();
			childStmt.pop_front();
			if (isAssignment(first)) {
				childStmt.push_back(first);
			}
		}
	}
	//TODO 1 add if or calls

	return childStmt;
}

list<int> PKBMain::getParentStar(int childStmt, Entity type) {
	list<int> parentStmt = childToParentStarTable.getParentStar(childStmt);
	if (type == STMT) {
		return parentStmt;
	}
	int listSize = parentStmt.size();
	int first;
	if (type == WHILE) {
		for (int i = 0; i < listSize; i++) {
			first = parentStmt.front();
			parentStmt.pop_front();
			if (isWhile(first)) {
				parentStmt.push_back(first);
			}
		}
	}

	if (type == ASSIGN) {
		for (int i = 0; i < listSize; i++) {
			first = parentStmt.front();
			parentStmt.pop_front();
			if (isAssignment(first)) {
				parentStmt.push_back(first);
			}
		}
	}

	//TODO 1 Add if

	return parentStmt;
}


pair<list<int>, list<int>> PKBMain::getAllParentsRel(Entity type1, Entity type2) {
	pair<list<int>, list<int>> allParentRel = parentToChildTable.getAllParentsRel();
	list<int> parent = allParentRel.first;
	list<int> children = allParentRel.second;
	int first;
	int second;

	int listSize = parent.size();
	for (int i = 0; i < listSize; i++) {
		if (type1 == WHILE) {
			first = parent.front();
			parent.pop_front();
			second = children.front();
			children.pop_front();
			if (isWhile(first)) {
				parent.push_back(first);
				children.push_back(second);
			}
		}


		if (type1 == ASSIGN) {
			first = parent.front();
			parent.pop_front();
			second = children.front();
			children.pop_front();
			if (isAssignment(first)) {
				parent.push_back(first);
				children.push_back(second);
			}
		}
	}


	listSize = parent.size();
	for (int i = 0; i < listSize; i++) {
		if (type2 == WHILE) {
			first = parent.front();
			parent.pop_front();
			second = children.front();
			children.pop_front();
			if (isWhile(second)) {
				parent.push_back(first);
				children.push_back(second);
			}
		}

		if (type2 == ASSIGN) {
			first = parent.front();
			parent.pop_front();
			second = children.front();
			children.pop_front();
			if (isAssignment(second)) {
				parent.push_back(first);
				children.push_back(second);
			}
		}
	}
	//TODO 1 add if
	return make_pair(parent, children);
}

pair<list<int>, list<int>> PKBMain::getAllParentStarRel(Entity type1, Entity type2) {
	pair<list<int>, list<int>> allParentStarRel = parentToChildStarTable.getAllParentStarRel();
	list<int> parent = allParentStarRel.first;
	list<int> children = allParentStarRel.second;
	int first;
	int second;

	int listSize = parent.size();
	for (int i = 0; i < listSize; i++) {
		if (type1 == WHILE) {
			first = parent.front();
			parent.pop_front();
			second = children.front();
			children.pop_front();
			if (isWhile(first)) {
				parent.push_back(first);
				children.push_back(second);
			}
		}

		if (type1 == ASSIGN) {
			first = parent.front();
			parent.pop_front();
			second = children.front();
			children.pop_front();
			if (isAssignment(first)) {
				parent.push_back(first);
				children.push_back(second);
			}
		}
	}

	listSize = parent.size();
	for (int i = 0; i < listSize; i++) {
		if (type2 == WHILE) {
			first = parent.front();
			parent.pop_front();
			second = children.front();
			children.pop_front();
			if (isWhile(second)) {
				parent.push_back(first);
				children.push_back(second);
			}
		}

		if (type2 == ASSIGN) {
			first = parent.front();
			parent.pop_front();
			second = children.front();
			children.pop_front();
			if (isAssignment(second)) {
				parent.push_back(first);
				children.push_back(second);
			}
		}
	}

	return make_pair(parent, children);
}

//
//FOLLOWS
pair<list<int>, list<int>> PKBMain::getAllFollows(Entity type1, Entity type2) {
	pair<list<int>, list<int>> allFollows = followsTable.getAllFollows();
	list<int> bef = allFollows.first;
	list<int> aft = allFollows.second;
	int first;
	int second;

	int listSize = bef.size();
	for (int i = 0; i < listSize; i++) {
		if (type1 == WHILE) {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isWhile(first)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}

		if (type1 == ASSIGN) {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isAssignment(first)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}
	}

	listSize = bef.size();
	for (int i = 0; i < listSize; i++) {
		if (type2 == WHILE) {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isWhile(second)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}

		if (type2 == ASSIGN) {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isAssignment(second)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}
	}

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

list<int> PKBMain::getAfter(int currStmt, Entity type) {
	int after = getAfter(currStmt);
	list<int> stmtList;
	list<int> emptyList;
	if (after == 0) {
		return emptyList;
	}

	stmtList.push_back(after);

	if (type == ASSIGN) {

		if (isAssignment(after)) {
			return stmtList;
		}
		else {
			return emptyList;
		}

	}

	if (type == WHILE) {

		if (isWhile(after)) {
			return stmtList;
		}
		else {
			return emptyList;
		}

	}
	//TODO 1 add if
	return stmtList;
}

list<int> PKBMain::getBefore(int currStmt, Entity type) {
	int before = getBefore(currStmt);
	list<int> stmtList;
	list<int> emptyList;
	if (before == 0) {
		return emptyList;
	}

	stmtList.push_back(before);

	if (type == ASSIGN) {

		if (isAssignment(before)) {
			return stmtList;
		}
		else {
			return emptyList;
		}

	}

	if (type == WHILE) {

		if (isWhile(before)) {
			return stmtList;
		}
		else {
			return emptyList;
		}

	}
	//TODO 1 add if
	return stmtList;
}

list<int> PKBMain::getAllBefore(Entity type) {
	list<int> stmtList;
	stmtList = followsTable.getAllBefore();

	int listSize = stmtList.size();
	int first;
	if (type == ASSIGN) {
		for (int i = 0; i < listSize; i++) {
			first = stmtList.front();
			stmtList.pop_front();
			if (isAssignment(first)) {
				stmtList.push_back(first);
			}
		}
	}

	if (type == WHILE) {
		for (int i = 0; i < listSize; i++) {
			first = stmtList.front();
			stmtList.pop_front();
			if (isWhile(first)) {
				stmtList.push_back(first);
			}
		}
	}
	//add if
	return stmtList;
}

list<int> PKBMain::getAllAfter(Entity type) {
	list<int> stmtList;
	stmtList = followsTable.getAllAfter();

	int listSize = stmtList.size();
	int first;

	if (type == ASSIGN) {
		for (int i = 0; i < listSize; i++) {
			first = stmtList.front();
			stmtList.pop_front();
			if (isAssignment(first)) {
				stmtList.push_back(first);
			}
		}
	}

	if (type == WHILE) {
		for (int i = 0; i < listSize; i++) {
			first = stmtList.front();
			stmtList.pop_front();
			if (isWhile(first)) {
				stmtList.push_back(first);
			}
		}
	}

	return stmtList;
}

bool PKBMain::isFollowsStar(int befStmt, int aftStmt) {
	return followsStarAfter.isAfterStar(befStmt, aftStmt);
}

list<int> PKBMain::getAfterStar(int befStmt, Entity type) {
	list<int> aft = followsStarAfter.getAfterStar(befStmt);
	int first;
	int listSize = aft.size();
	if (type == STMT) {
		return aft;
	}

	for (int i = 0; i < listSize; i++) {
		first = aft.front();
		aft.pop_front();
		if (type == WHILE) {
			if (isWhile(first)) {
				aft.push_back(first);
			}
		}
		if (type == ASSIGN) {
			if (isAssignment(first)) {
				aft.push_back(first);
			}

		}
		//TODO 1 add if
	}
	return aft;
}

list<int> PKBMain::getBeforeStar(int aftStmt, Entity type) {
	list<int> bef = followsStarBefore.getBeforeStar(aftStmt);
	int first;
	int listSize = bef.size();
	if (type == STMT) {
		return bef;
	}

	for (int i = 0; i < listSize; i++) {
		first = bef.front();
		bef.pop_front();
		if (type == WHILE) {
			if (isWhile(first)) {
				bef.push_back(first);
			}
		}
		if (type == ASSIGN) {
			if (isAssignment(first)) {
				bef.push_back(first);
			}
		}
		//TODO 1 add if
	}

	return bef;
}

list<int> PKBMain::getAllBeforeStar(Entity type) {
	list<int> bef = followsStarBefore.getAllBeforeStar();
	int first;
	int listSize = bef.size();
	if (type == STMT) {
		return bef;
	}

	for (int i = 0; i < listSize; i++) {
		first = bef.front();
		bef.pop_front();
		if (type == WHILE) {
			if (isWhile(first)) {
				bef.push_back(first);
			}
		}
		if (type == ASSIGN) {
			if (isAssignment(first)) {
				bef.push_back(first);
			}
		}
		//TODO 1 add if
	}

	return bef;
}

list<int> PKBMain::getAllAfterStar(Entity type) {
	list<int> aft = followsStarAfter.getAllAfterStar();
	int first;
	int listSize = aft.size();
	if (type == STMT) {
		return aft;
	}


	for (int i = 0; i < listSize; i++) {
		first = aft.front();
		aft.pop_front();
		if (type == WHILE) {
			if (isWhile(first)) {
				aft.push_back(first);
			}
		}
		if (type == ASSIGN) {
			if (isAssignment(first)) {
				aft.push_back(first);
			}
		}
		//TODO 1 add if
	}

	return aft;
}

pair<list<int>, list<int>> PKBMain::getAllFollowsStar(Entity type1, Entity type2) {
	pair<list<int>, list<int>> allFollows = followsStarAfter.getAllFollows();
	list<int> bef = allFollows.first;
	list<int> aft = allFollows.second;
	int first;
	int second;

	int listSize = bef.size();
	for (int i = 0; i < listSize; i++) {
		if (type1 == WHILE) {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isWhile(first)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}

		if (type1 == ASSIGN) {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isAssignment(first)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}
	}

	listSize = bef.size();
	for (int i = 0; i < listSize; i++) {
		if (type2 == WHILE) {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isWhile(second)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}

		if (type2 == ASSIGN) {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isAssignment(second)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}
	}

	//TODO 1 add if
	return make_pair(bef, aft);
}

bool PKBMain::startProcessComplexRelations() {
	DesignExtractor de;
	followsTable.setMap(de.computeFollowsTable(followsBeforeMap, followsAfterMap));
	childToParentStarTable.setMap(de.computeChildToParentStarTable(childToParentTable));
	parentToChildStarTable.setMap(de.computeParentToChildStarTable(parentToChildTable));
	followsStarAfter.setMap(de.computeFollowsStarAfterTable(followsTable));
	followsStarBefore.setMap(de.computeFollowsStarBeforeTable(followsTable));
	callsStarTable.setCallsStarMap(de.computeCallsStarTable(callsTable));
	//TODO 2 add calls, perhaps optimise
	return true;
}

bool PKBMain::isPresent(string var)
{
	return varIdxTable.isVarPresent(var);
}

bool PKBMain::isPresent(int stmtNum)
{
	return stmtTypeList.isPresent(stmtNum);
}

bool PKBMain::isAssignment(int stmtNum)
{
	return stmtTypeList.isAssignStmt(stmtNum);
}

bool PKBMain::isWhile(int stmtNum)
{
	return stmtTypeList.isWhileStmt(stmtNum);
}

list<int> PKBMain::getAllWhiles()
{
	return stmtTypeList.getWhileStmtList();
}

list<int> PKBMain::getAllConstants() {
	return constantTable.getAllConstants();
}

list<int> PKBMain::getAllStatements() {
	return stmtTypeList.getAllStatements();
}

list<int> PKBMain::getAllVariables() {
	return varIdxTable.getAllVariablesIndex();
}

list<int> PKBMain::getAllProcedures() {
	return procIdxTable.getAllProceduresIndex();
}
bool PKBMain::setModTableStmtToVar(int stmt, string var)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	bool added = modTableStmtToVar.addModStmtToVarList(stmt, varIdx);
	added = modTableVar.addModVarToStmtList(varIdx, stmt);
	if (stmtTypeList.isAssignStmt(stmt))
	{
		added = modTableVar.addModVarToAssignList(varIdx, stmt);
	}
	else if (stmtTypeList.isWhileStmt(stmt))
	{
		added = modTableVar.addModVarToWhileStmtList(varIdx, stmt);
	}
	return added;
}

bool PKBMain::setModTableProcToVar(string proc, string var)
{
	int procIdx = procIdxTable.getIdxFromProc(proc);
	int varIdx = varIdxTable.getIdxFromVar(var);
	bool added = modTableProcToVar.addModProcToVarList(procIdx, varIdx);
	return added;

}

bool PKBMain::setUseTableStmtToVar(int stmt, string var)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	bool added = usesTableStmtToVar.addUsesStmtToVarList(stmt, varIdx);
	added = usesTableVar.addUsesVarToStmtList(varIdx, stmt);
	if (stmtTypeList.isAssignStmt(stmt))
	{
		added = usesTableVar.addUsesVarToAssignList(varIdx, stmt);
	}
	else if (stmtTypeList.isWhileStmt(stmt))
	{
		added = usesTableVar.addUsesVarToWhileStmtList(varIdx, stmt);
	}
	return added;
}

bool PKBMain::setUseTableProcToVar(string proc, string var)
{
	int procIdx = procIdxTable.getIdxFromProc(proc);
	int varIdx = varIdxTable.getIdxFromVar(var);
	bool added = usesTableProcToVar.addUsesProcToVarList(procIdx, varIdx);
	return added;
}

bool PKBMain::setPatternRelation(int stmt, string var, string expression)
{
	bool added = patternTable.addToPatternTable(stmt, var, expression);
	return added;
}

bool PKBMain::isUses(int stmt, string var)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	return usesTableStmtToVar.isUses(stmt, varIdx);
}

bool PKBMain::isMod(int stmt, string var)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	return modTableStmtToVar.isMod(stmt, varIdx);
}

bool PKBMain::isMod(int stmt, int varIdx)
{
	return modTableStmtToVar.isMod(stmt, varIdx);
}

bool PKBMain::isUsingAnything(int stmt)
{
	return usesTableStmtToVar.isUsingAnything(stmt);
}

bool PKBMain::isModifyingAnything(int stmt)
{
	return modTableStmtToVar.isModifyingAnything(stmt);
}

list<int> PKBMain::getUsesFromStmt(int stmt)
{
	return usesTableStmtToVar.getUsesVariablesFromStmt(stmt);
}

list<int> PKBMain::getModifiesFromStmt(int stmt)
{
	return modTableStmtToVar.getModVariablesFromStmt(stmt);
}

list<int> PKBMain::getUsesFromVar(string var, Entity type)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	if (varIdx == -1) {
		return list<int>();
	}
	if (type == STMT) {
		return usesTableVar.getUsesStmtsFromVar(varIdx);
	}
	else if (type == ASSIGN) {
		return usesTableVar.getUsesAssignsFromVar(varIdx);
	}
	else if (type == WHILE) {
		usesTableVar.getUsesWhileStmtFromVar(varIdx).merge(usesTableVar.getUsesWhileContainersFromVar(varIdx));
		return usesTableVar.getUsesWhileStmtFromVar(varIdx);
	}
	//TODO 1 add if
	else {
		return list<int>();
	}
}

list<int> PKBMain::getModifiesFromVar(string var, Entity type)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	if (varIdx == -1) {
		return list<int>();
	}
	if (type == STMT) {
		return modTableVar.getModStmtsFromVar(varIdx);
	}
	else if (type == ASSIGN) {
		return modTableVar.getModAssignsFromVar(varIdx);
	}
	else if (type == WHILE) {
		modTableVar.getModWhileStmtFromVar(varIdx).merge(modTableVar.getModWhileContainersFromVar(varIdx));
		return modTableVar.getModWhileStmtFromVar(varIdx);
	}
	else {
		return list<int>();
	}
}

list<int> PKBMain::getStmtThatUsesAnything(Entity type)
{
	list<int> stmtList = usesTableStmtToVar.getStmtThatUses();
	return stmtTypeList.getStmtType(stmtList, type);
}

list<int> PKBMain::getStmtThatModifiesAnything(Entity type)
{
	list<int> stmtList = modTableStmtToVar.getStmtThatModifies();
	return stmtTypeList.getStmtType(stmtList, type);
}

pair<list<int>, list<int>> PKBMain::getUsesPairs(Entity type)
{
	pair<list<int>, list<int>> usesPairs = usesTableStmtToVar.getUsesPair();
	return stmtTypeList.getStmtType(usesPairs, type);
}

pair<list<int>, list<int>> PKBMain::getModifiesPairs(Entity type)
{
	pair<list<int>, list<int>> modPairs = modTableStmtToVar.getModPair();
	return stmtTypeList.getStmtType(modPairs, type);
}

pair<list<int>, list<string>> PKBMain::getLeftVariables()
{
	return patternTable.getLeftVariables();
}

pair<list<int>, list<string>> PKBMain::getLeftVariablesThatMatchWith(string expression)
{
	return patternTable.getLeftVariableThatMatchWithString(expression);
}

list<int> PKBMain::getPartialMatchStmt(string expression)
{
	return patternTable.getPartialMatchStmt(expression);
}

list<int> PKBMain::getPartialBothMatches(string var, string expression)
{
	return patternTable.getPartialBothMatches(var, expression);
}

list<int> PKBMain::getExactMatchStmt(string expression)
{
	return patternTable.getExactMatchStmt(expression);
}

list<int> PKBMain::getExactBothMatches(string var, string expression)
{
	return patternTable.getExactBothMatches(var, expression);
}

list<int> PKBMain::getAllAssignments()
{
	return stmtTypeList.getAssignStmtList();
}

list<int> PKBMain::getAllAssignments(string var)
{
	list<int> stmtList = patternTable.getLeftVariableMatchingStmts(var);
	return stmtTypeList.getStmtType(stmtList, ASSIGN);
}

bool PKBMain::addVariable(string var)
{
	bool added = varIdxTable.addToVarIdxTable(var);
	return added;
}

bool PKBMain::addProcedure(string proc)
{
	bool added = procIdxTable.addToProcIdxTable(proc);
	return added;
}

bool PKBMain::addAssignmentStmt(int stmt)
{
	bool added = stmtTypeList.addToAssignStmtList(stmt);
	return added;
}

bool PKBMain::addWhileStmt(int stmt)
{
	bool added = stmtTypeList.addToWhileStmtList(stmt);
	return added;
}

bool PKBMain::addConstant(int stmt, int constant)
{
	bool added = constantTable.addConstantList(stmt, constant);
	return added;
}
