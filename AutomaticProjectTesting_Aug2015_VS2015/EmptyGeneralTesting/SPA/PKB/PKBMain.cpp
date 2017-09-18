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

	if (type == "assign") {
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

	if (type == "assign") {
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

list<int> PKBMain::getChildrenStar(int parentStmt, string type) {
	list<int> childStmt = parentToChildStarTable.getChildren(parentStmt);
	if (type == "stmt") {
		return childStmt;
	}
	int listSize = childStmt.size();
	int first;
	if (type == "while") {
		for (int i = 0; i < listSize; i++) {
			first = childStmt.front();
			childStmt.pop_front();
			if (isWhile(first)) {
				childStmt.push_back(first);
			}
		}
	}

	if (type == "assign") {
		for (int i = 0; i < listSize; i++) {
			first = childStmt.front();
			childStmt.pop_front();
			if (isAssignment(first)) {
				childStmt.push_back(first);
			}
		}
	}

	return childStmt;
}

list<int> PKBMain::getParentStar(int childStmt, string type) {
	list<int> parentStmt = childToParentStarTable.getParentStar(childStmt);
	if (type == "stmt") {
		return parentStmt;
	}
	int listSize = parentStmt.size();
	int first;
	if (type == "while") {
		for (int i = 0; i < listSize; i++) {
			first = parentStmt.front();
			parentStmt.pop_front();
			if (isWhile(first)) {
				parentStmt.push_back(first);
			}
		}
	}

	if (type == "assign") {
		for (int i = 0; i < listSize; i++) {
			first = parentStmt.front();
			parentStmt.pop_front();
			if (isAssignment(first)) {
				parentStmt.push_back(first);
			}
		}
	}

	return parentStmt;
}


pair<list<int>, list<int>> PKBMain::getAllParentsRel(string type1, string type2) {
	pair<list<int>, list<int>> allParentRel = parentToChildTable.getAllParentsRel();
	list<int> parent = allParentRel.first;
	list<int> children = allParentRel.second;
	int first;
	int second;

	int listSize = parent.size();
	for (int i = 0; i < listSize; i++) {
		if (type1 == "while") {
			first = parent.front();
			parent.pop_front();
			second = children.front();
			children.pop_front();
			if (isWhile(first)) {
				parent.push_back(first);
				children.push_back(second);
			}
		}


		if (type1 == "assign") {
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
		if (type2 == "while") {
			first = parent.front();
			parent.pop_front();
			second = children.front();
			children.pop_front();
			if (isWhile(second)) {
				parent.push_back(first);
				children.push_back(second);
			}
		}

		if (type2 == "assign") {
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

pair<list<int>, list<int>> PKBMain::getAllParentStarRel(string type1, string type2) {
	pair<list<int>, list<int>> allParentStarRel = parentToChildStarTable.getAllParentStarRel();
	list<int> parent = allParentStarRel.first;
	list<int> children = allParentStarRel.second;
	int first;
	int second;

	int listSize = parent.size();
	for (int i = 0; i < listSize; i++) {
		if (type1 == "while") {
			first = parent.front();
			parent.pop_front();
			second = children.front();
			children.pop_front();
			if (isWhile(first)) {
				parent.push_back(first);
				children.push_back(second);
			}
		}

		if (type1 == "assign") {
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
		if (type2 == "while") {
			first = parent.front();
			parent.pop_front();
			second = children.front();
			children.pop_front();
			if (isWhile(second)) {
				parent.push_back(first);
				children.push_back(second);
			}
		}

		if (type2 == "assign") {
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
pair<list<int>, list<int>> PKBMain::getAllFollows(string type1, string type2) {
	pair<list<int>, list<int>> allFollows = followsTable.getAllFollows();
	list<int> bef = allFollows.first;
	list<int> aft = allFollows.second;
	int first;
	int second;

	int listSize = bef.size();
	for (int i = 0; i < listSize; i++) {
		if (type1 == "while") {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isWhile(first)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}

		if (type1 == "assign") {
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
		if (type2 == "while") {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isWhile(second)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}

		if (type2 == "assign") {
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

list<int> PKBMain::getAfter(int currStmt, string type) {
	int after = getAfter(currStmt);
	list<int> stmtList;
	list<int> emptyList;
	if (after == 0) {
		return emptyList;
	}

	stmtList.push_back(after);

	if (type == "assign") {

		if (isAssignment(after)) {
			return stmtList;
		}
		else {
			return emptyList;
		}

	}

	if (type == "while") {

		if (isWhile(after)) {
			return stmtList;
		}
		else {
			return emptyList;
		}

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

	if (type == "assign") {

		if (isAssignment(before)) {
			return stmtList;
		}
		else {
			return emptyList;
		}

	}

	if (type == "while") {

		if (isWhile(before)) {
			return stmtList;
		}
		else {
			return emptyList;
		}

	}

	return stmtList;
}

list<int> PKBMain::getAllBefore(string type) {
	list<int> stmtList;
	stmtList = followsTable.getAllBefore();

	int listSize = stmtList.size();
	int first;
	if (type == "assign") {
		for (int i = 0; i < listSize; i++) {
			first = stmtList.front();
			stmtList.pop_front();
			if (isAssignment(first)) {
				stmtList.push_back(first);
			}
		}
	}

	if (type == "while") {
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

list<int> PKBMain::getAllAfter(string type) {
	list<int> stmtList;
	stmtList = followsTable.getAllAfter();

	int listSize = stmtList.size();
	int first;

	if (type == "assign") {
		for (int i = 0; i < listSize; i++) {
			first = stmtList.front();
			stmtList.pop_front();
			if (isAssignment(first)) {
				stmtList.push_back(first);
			}
		}
	}

	if (type == "while") {
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

list<int> PKBMain::getAfterStar(int befStmt, string type) {
	list<int> aft = followsStarAfter.getAfterStar(befStmt);
	int first;
	int listSize = aft.size();
	if (type == "stmt") {
		return aft;
	}

	for (int i = 0; i < listSize; i++) {
		first = aft.front();
		aft.pop_front();
		if (type == "while") {
			if (isWhile(first)) {
				aft.push_back(first);
			}
		}
		if (type == "assign") {
			if (isAssignment(first)) {
				aft.push_back(first);
			}

		}
	}
	return aft;
}

list<int> PKBMain::getBeforeStar(int aftStmt, string type) {
	list<int> bef = followsStarBefore.getBeforeStar(aftStmt);
	int first;
	int listSize = bef.size();
	if (type == "stmt") {
		return bef;
	}

	for (int i = 0; i < listSize; i++) {
		first = bef.front();
		bef.pop_front();
		if (type == "while") {
			if (isWhile(first)) {
				bef.push_back(first);
			}
		}
		if (type == "assign") {
			if (isAssignment(first)) {
				bef.push_back(first);
			}
		}
	}

	return bef;
}

list<int> PKBMain::getAllBeforeStar(string type) {
	list<int> bef = followsStarBefore.getAllBeforeStar();
	int first;
	int listSize = bef.size();
	if (type == "stmt") {
		return bef;
	}

	for (int i = 0; i < listSize; i++) {
		first = bef.front();
		bef.pop_front();
		if (type == "while") {
			if (isWhile(first)) {
				bef.push_back(first);
			}
		}
		if (type == "assign") {
			if (isAssignment(first)) {
				bef.push_back(first);
			}
		}
	}

	return bef;
}

list<int> PKBMain::getAllAfterStar(string type) {
	list<int> aft = followsStarAfter.getAllAfterStar();
	int first;
	int listSize = aft.size();
	if (type == "stmt") {
		return aft;
	}


	for (int i = 0; i < listSize; i++) {
		first = aft.front();
		aft.pop_front();
		if (type == "while") {
			if (isWhile(first)) {
				aft.push_back(first);
			}
		}
		if (type == "assign") {
			if (isAssignment(first)) {
				aft.push_back(first);
			}
		}
	}

	return aft;
}

pair<list<int>, list<int>> PKBMain::getAllFollowsStar(string type1, string type2) {
	pair<list<int>, list<int>> allFollows = followsStarAfter.getAllFollows();
	list<int> bef = allFollows.first;
	list<int> aft = allFollows.second;
	int first;
	int second;

	int listSize = bef.size();
	for (int i = 0; i < listSize; i++) {
		if (type1 == "while") {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isWhile(first)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}

		if (type1 == "assign") {
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
		if (type2 == "while") {
			first = bef.front();
			bef.pop_front();
			second = aft.front();
			aft.pop_front();
			if (isWhile(second)) {
				bef.push_back(first);
				aft.push_back(second);
			}
		}

		if (type2 == "assign") {
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

bool PKBMain::startProcessComplexRelations() {
	DesignExtractor de;
	followsTable.setMap(de.computeFollowsTable(followsBeforeMap, followsAfterMap));
	childToParentStarTable.setMap(de.computeChildToParentStarTable(childToParentTable));
	parentToChildStarTable.setMap(de.computeParentToChildStarTable(parentToChildTable));
	followsStarAfter.setMap(de.computeFollowsStarAfterTable(followsTable));
	followsStarBefore.setMap(de.computeFollowsStarBeforeTable(followsTable));
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

list<string> PKBMain::getAllVariables() {
	return varIdxTable.getAllVariables();
}

bool PKBMain::setModTableStmtToVar(int stmt, string var)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	bool added = modTableStmtToVar.addModStmtToVarList(stmt, var);
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
	bool added = modTableProcToVar.addModProcToVarList(procIdx, var);
	return added;

}

bool PKBMain::setUseTableStmtToVar(int stmt, string var)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	bool added = usesTableStmtToVar.addUsesStmtToVarList(stmt, var);
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
	bool added = usesTableProcToVar.addUsesProcToVarList(procIdx, var);
	return added;
}

bool PKBMain::setPatternRelation(int stmt, string var, string expression)
{
	bool added = patternTable.addToPatternTable(stmt, var, expression);
	return added;
}

bool PKBMain::isUses(int stmt, string var)
{
	return usesTableStmtToVar.isUses(stmt, var);
}

bool PKBMain::isMod(int stmt, string var)
{
	return modTableStmtToVar.isMod(stmt, var);
}

bool PKBMain::isUsingAnything(int stmt)
{
	return usesTableStmtToVar.isUsingAnything(stmt);
}

bool PKBMain::isModifyingAnything(int stmt)
{
	return modTableStmtToVar.isModifyingAnything(stmt);
}

list<string> PKBMain::getUsesFromStmt(int stmt)
{
	return usesTableStmtToVar.getUsesVariablesFromStmt(stmt);
}

list<string> PKBMain::getModifiesFromStmt(int stmt)
{
	return modTableStmtToVar.getModVariablesFromStmt(stmt);
}

list<int> PKBMain::getUsesFromVar(string var, string type)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	if (varIdx == -1) {
		return list<int>();
	}
	if (type.compare("stmt") == 0) {
		return usesTableVar.getUsesStmtsFromVar(varIdx);
	}
	else if (type.compare("assign") == 0) {
		return usesTableVar.getUsesAssignsFromVar(varIdx);
	}
	else if (type.compare("while") == 0) {
		usesTableVar.getUsesWhileStmtFromVar(varIdx).merge(usesTableVar.getUsesWhileContainersFromVar(varIdx));
		return usesTableVar.getUsesWhileStmtFromVar(varIdx);
	}
	else {
		return list<int>();
	}
}

list<int> PKBMain::getModifiesFromVar(string var, string type)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	if (varIdx == -1) {
		return list<int>();
	}
	if (type.compare("stmt") == 0) {
		return modTableVar.getModStmtsFromVar(varIdx);
	}
	else if (type.compare("assign") == 0) {
		return modTableVar.getModAssignsFromVar(varIdx);
	}
	else if (type.compare("while") == 0) {
		modTableVar.getModWhileStmtFromVar(varIdx).merge(modTableVar.getModWhileContainersFromVar(varIdx));
		return modTableVar.getModWhileStmtFromVar(varIdx);
	}
	else {
		return list<int>();
	}
}

list<int> PKBMain::getStmtThatUsesAnything(string type)
{
	list<int> stmtList = usesTableStmtToVar.getStmtThatUses();
	return stmtTypeList.getStmtType(stmtList, type);
}

list<int> PKBMain::getStmtThatModifiesAnything(string type)
{
	list<int> stmtList = modTableStmtToVar.getStmtThatModifies();
	return stmtTypeList.getStmtType(stmtList, type);
}

pair<list<int>, list<string>> PKBMain::getUsesPairs(string type)
{
	pair<list<int>, list<string>> usesPairs = usesTableStmtToVar.getUsesPair();
	return stmtTypeList.getStmtType(usesPairs, type);
}

pair<list<int>, list<string>> PKBMain::getModifiesPairs(string type)
{
	pair<list<int>, list<string>> modPairs = modTableStmtToVar.getModPair();
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
	return stmtTypeList.getStmtType(stmtList, "assign");
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
