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
	list<string> resultList;
	string result;
	int index;
	if (type == PROCEDURE) {
		for (int i = 0; i < indexList.size(); i++) {
			index = indexList.front();
			indexList.pop_front();
			result = procIdxTable.getProcFromIdx(index);
			if (result == "") {
				continue;
			}

			resultList.push_back(result);
		}
	}

	if (type == VARIABLE) {
		for (int i = 0; i < indexList.size(); i++) {
			index = indexList.front();
			indexList.pop_front();
			result = varIdxTable.getVarFromIdx(index);
			if (result == "") {
				continue;
			}

			resultList.push_back(result);
		}
	}
		return resultList;
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
	list<int> resultList = stmtTypeList.getStmtType(parentToChildTable.getChildren(parentStmt), type);
	return resultList;
}

bool PKBMain::isChild(int childStmt) {
	return childToParentTable.isChild(childStmt);
}

bool PKBMain::hasParentRel() {
	return !parentToChildTable.empty();
}

list<int> PKBMain::getParent(int childStmt, Entity type) {
	list<int> resultList;
	int parentStmt = childToParentTable.getParent(childStmt);
	resultList = stmtTypeList.getStmtType(parentStmt, type);
	return resultList;
}

list<int> PKBMain::getAllParents(Entity type) {
	list<int> resultList = stmtTypeList.getStmtType(parentToChildTable.getAllParents(), type);
	return resultList;
}

list<int> PKBMain::getAllChildren(Entity type) {
	list<int> resultList = stmtTypeList.getStmtType(childToParentTable.getAllChildren(), type);
	return resultList;
}


bool PKBMain::isParentStarChild(int parentStmt, int childStmt) {
	return parentToChildStarTable.isParentStarChild(parentStmt, childStmt);
}

list<int> PKBMain::getChildrenStar(int parentStmt, Entity type) {
	list<int> resultList = stmtTypeList.getStmtType(parentToChildStarTable.getChildren(parentStmt), type);
	return resultList;
}

list<int> PKBMain::getParentStar(int childStmt, Entity type) {
	list<int> resultList = stmtTypeList.getStmtType(childToParentStarTable.getParentStar(childStmt), type);
	return resultList;
}


pair<list<int>, list<int>> PKBMain::getAllParentsRel(Entity type1, Entity type2) {
	pair<list<int>, list<int>> allParentsRel = parentToChildTable.getAllParentsRel();
	pair<list<int>, list<int>> resultPair = stmtTypeList.getStmtType(allParentsRel, type1, type2);
	return resultPair;
}

pair<list<int>, list<int>> PKBMain::getAllParentStarRel(Entity type1, Entity type2) {
	pair<list<int>, list<int>> allParentStarRel = parentToChildStarTable.getAllParentStarRel();
	pair<list<int>, list<int>> resultPair = stmtTypeList.getStmtType(allParentStarRel, type1, type2);
	return resultPair;
}

//
//FOLLOWS
pair<list<int>, list<int>> PKBMain::getAllFollows(Entity type1, Entity type2) {
	pair<list<int>, list<int>> allFollows = followsTable.getAllFollows();
	pair<list<int>, list<int>> resultPair = stmtTypeList.getStmtType(allFollows, type1, type2);
	return resultPair;
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
	if (after == 0) {
		return list<int>();
	}

	list<int> resultList = stmtTypeList.getStmtType(after, type);
	return resultList;
}

list<int> PKBMain::getBefore(int currStmt, Entity type) {
	int before = getBefore(currStmt);
	if (before == 0) {
		return list<int>();
	}

	list<int> resultList = stmtTypeList.getStmtType(before, type);
	return resultList;
}

list<int> PKBMain::getAllBefore(Entity type) {
	list<int> resultList = stmtTypeList.getStmtType(followsTable.getAllBefore(), type);
	return resultList;
}

list<int> PKBMain::getAllAfter(Entity type) {
	list<int> resultList = stmtTypeList.getStmtType(followsTable.getAllAfter(), type);
	return resultList;
}

bool PKBMain::isFollowsStar(int befStmt, int aftStmt) {
	return followsStarAfter.isAfterStar(befStmt, aftStmt);
}

list<int> PKBMain::getAfterStar(int befStmt, Entity type) {
	list<int> resultList = stmtTypeList.getStmtType(followsStarAfter.getAfterStar(befStmt), type);
	return resultList;
}

list<int> PKBMain::getBeforeStar(int aftStmt, Entity type) {
	list<int> resultList = stmtTypeList.getStmtType(followsStarBefore.getBeforeStar(aftStmt), type);
	return resultList;
}

list<int> PKBMain::getAllBeforeStar(Entity type) {
	list<int> resultList = stmtTypeList.getStmtType(followsStarBefore.getAllBeforeStar(), type);
	return resultList;
}

list<int> PKBMain::getAllAfterStar(Entity type) {
	list<int> resultList = stmtTypeList.getStmtType(followsStarAfter.getAllAfterStar(), type);
	return resultList;
}

pair<list<int>, list<int>> PKBMain::getAllFollowsStar(Entity type1, Entity type2) {
	pair<list<int>, list<int>> resultPair = stmtTypeList.getStmtType(followsStarAfter.getAllFollows(), type1, type2);
	return resultPair;
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

bool PKBMain::isIf(int stmtNum)
{
    return stmtTypeList.isIfStmt(stmtNum);
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

list<int> PKBMain::getAllIfs()
{
    return stmtTypeList.getIfStmtList();
}

list<int> PKBMain::getAllCallsStmt() {
	return stmtTypeList.getCallsStmtList();
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

bool PKBMain::isUses(int stmt, int varIdx)
{
    return usesTableStmtToVar.isUses(stmt, varIdx);
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
    else if (type == IF) {
        return usesTableVar.getUsesIfFromVar(varIdx);
    }
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
    else if (type == IF) {
        modTableVar.getModIfFromVar(varIdx);
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

bool PKBMain::addIfStmt(int stmt)
{
    bool added = stmtTypeList.addToIfStmtList(stmt);
    return added;
}

bool PKBMain::addConstant(int stmt, int constant)
{
	bool added = constantTable.addConstantList(stmt, constant);
	return added;
}
