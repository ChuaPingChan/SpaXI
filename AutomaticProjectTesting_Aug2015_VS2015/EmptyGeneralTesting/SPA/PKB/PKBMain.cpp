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
bool PKBMain::isSameName(Entity type1, int idx1, Entity type2, int idx2) {
	string arg1 = convertIdxToString(idx1, type1);
	string arg2 = convertIdxToString(idx2, type2);

	return arg1 == arg2;
}

string PKBMain::convertIdxToString(int index, Entity type) {
	string result;
	if (type == PROCEDURE || type == CALL) {
		result = procIdxTable.getProcFromIdx(index);
	}

	if (type == VARIABLE) {
		result = varIdxTable.getVarFromIdx(index);
	}

	return result;
}

list<string> PKBMain::convertIdxToString(list<int> indexList, Entity type) {
	list<string> resultList;
	string result;
	if (type == PROCEDURE || type == CALL)
    {
		for (int i : indexList) 
        {
			result = procIdxTable.getProcFromIdx(i);
			if (result == "") 
            {
				continue;
			}

			resultList.push_back(result);
		}
	}

	if (type == VARIABLE) {
		for (int i : indexList) {
			result = varIdxTable.getVarFromIdx(i);
			if (result == "") {
				continue;
			}

			resultList.push_back(result);
		}
	}
		return resultList;
}

int PKBMain::convertStringToIdx(string arg, Entity type) {
	int result = -1;
	if (type == PROCEDURE || type == CALL) {
		result = procIdxTable.getIdxFromProc(arg);
	}

	if (type == VARIABLE) {
		result = varIdxTable.getIdxFromVar(arg);
	}

	return result;
}

list<int> PKBMain::convertStringToIdx(list<string> stringList, Entity type) {
	list<int> resultList;
	int result;
	if (type == PROCEDURE || type == CALL) {
		for (string s : stringList) {
			result = procIdxTable.getIdxFromProc(s);
			if (result == -1) {
				continue;
			}

			resultList.push_back(result);
		}
	}

	if (type == VARIABLE) {
		for (string s : stringList) {
			result = varIdxTable.getIdxFromVar(s);
			if (result == -1) {
				continue;
			}

			resultList.push_back(result);
		}
	}

	return resultList;
}

list<int> PKBMain::getAllIntOfIntEntity(Entity type) {
	if (type == STMT) {
		return getAllStatements();
	}

	else if (type == ASSIGN) {
		return getAllAssignments();
	}

	else if (type == WHILE) {
		return getAllWhiles();
	}

	else if (type == CALL) {
		return getAllCallsStmt();
	}

	else if (type == IF) {
		return getAllConstants();
	}

	else if (type == PROG_LINE) {
		return getAllStatements();
	}

	else {
		return list<int>();
	}
}

list<int> PKBMain::getAllIdxOfStringEntity(Entity type) {
	if (type == PROCEDURE) {
		return getAllProcedures();
	}

	else if (type == CALL) {
		return getAllCallees();
	}

	else if (type == VARIABLE) {
		return getAllVariables();
	}

	else {
		return list<int>();
	}
}

bool PKBMain::isInstanceOf(Entity type, int arg) {
	if (type == STMT) {
		return isStatement(arg);
	}

	else if (type == ASSIGN) {
		return isAssignment(arg);
	}

	else if (type == WHILE) {
		return isWhile(arg);
	}

	else if (type == CALL) {
		return isCall(arg);
	}

	else if (type == IF) {
		return isIf(arg);
	}

	else if (type == CONSTANT) {
		return isConstant(arg);
	}

	else if (type == PROG_LINE) {
		return isProgLine(arg);
	}

	else {
		return false;
	}
}

bool PKBMain::isInstanceOf(Entity type, string arg) {
	if (type == PROCEDURE) {
		return isProcedure(arg);
	}

	else if (type == CALL) {
		return isCallee(arg);
	}

	else if (type == VARIABLE) {
		return isVariable(arg);
	}

	else {
		return false;
	}
}

//CALLS
list<string> PKBMain::getAllCalleeNames() {
	return stmtTypeList.getAllCalleeNames();
}

bool PKBMain::setCallsRel(int stmt, string callerProcName, string calleeProcName) {
	int callerProcIdx = procIdxTable.getIdxFromProc(callerProcName);

	if (procIdxTable.getIdxFromProc(calleeProcName) == -1) {
		procIdxTable.addToProcIdxTable(calleeProcName);
	}

	int calleeProcIdx = procIdxTable.getIdxFromProc(calleeProcName);
	stmtTypeList.addToCallsStmtList(stmt, calleeProcIdx, calleeProcName);
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

bool PKBMain::isCalls(int callerProcIdx, int calleeProcIdx) {
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

list<int> PKBMain::getCallee(int callerProcIdx) {
	return callsTable.getCallee(callerProcIdx);
}

bool PKBMain::isCallee(string calleeProcName) {
	int calleeProcIdx = procIdxTable.getIdxFromProc(calleeProcName);
	return callsTable.isCallee(calleeProcIdx);
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

list<int> PKBMain::getCaller(int calleeProcIdx) {
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

bool PKBMain::isCallsStar(int callerProcIdx, int calleeProcIdx) {
	return callsStarTable.isCallsStar(callerProcIdx, calleeProcIdx);
}

list<int> PKBMain::getCalleeStar(string callerProcName) {
	int callerProcIdx = procIdxTable.getIdxFromProc(callerProcName);
	return callsStarTable.getCalleeStar(callerProcIdx);
}

list<int> PKBMain::getCalleeStar(int callerProcIdx) {
	return callsStarTable.getCalleeStar(callerProcIdx);
}

list<int> PKBMain::getCallerStar(string calleeProcName) {
	int calleeProcIdx = procIdxTable.getIdxFromProc(calleeProcName);
	return callsStarTable.getCallerStar(calleeProcIdx);
}

list<int> PKBMain::getCallerStar(int calleeProcIdx) {
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
	if (parentStmt == 0) {
		return resultList;
	}
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
	followsTable.setMap(de.computeFollowsTable(followsBeforeMap, followsAfterMap));
	childToParentStarTable.setMap(de.computeChildToParentStarTable(childToParentTable));
	parentToChildStarTable.setMap(de.computeParentToChildStarTable(parentToChildTable));
	followsStarAfter.setMap(de.computeFollowsStarAfterTable(followsTable));
	followsStarBefore.setMap(de.computeFollowsStarBeforeTable(followsTable));
	callsStarTable.setCallsStarMap(de.computeCallsStarTable(callsTable));
	usesTableProcToVar.setMap(de.computeUsesTable(usesTableProcToVar, callsStarTable));
	modTableProcToVar.setMap(de.computeModifiesTable(modTableProcToVar, callsStarTable));
	//TODO test this
	usesTableStmtToVar.setMap(de.computeUsesTable(usesTableStmtToVar, stmtTypeList, usesTableProcToVar, childToParentStarTable));
	modTableStmtToVar.setMap(de.computeModifiesTable(modTableStmtToVar, stmtTypeList, modTableProcToVar, childToParentStarTable));
	usesTableVar.setStmtMap(de.computeUsesTableStmt(usesTableStmtToVar));
	usesTableVar.setProcMap(de.computeUsesTableProc(usesTableProcToVar));
	modTableVar.setStmtMap(de.computeModTableStmt(modTableStmtToVar));
	modTableVar.setProcMap(de.computeModTableProc(modTableProcToVar));
	return true;
}

bool PKBMain::setNext(int stmt, int stmtNext) {
	nextTable.setNextRel(stmt, stmtNext);
	return true;
}

bool PKBMain::isNext(int stmtBef, int stmtAft) {
	return nextTable.isNext(stmtBef, stmtAft);
}

bool PKBMain::isExecutedBefore(int stmtBef) {
	return nextTable.isExecutedBefore(stmtBef);
}

list<int> PKBMain::getExecutedAfter(int stmtBef, Entity type) {
	list<int> stmtList;

	stmtList = nextTable.getExecutedAfter(stmtBef);
	stmtList = stmtTypeList.getStmtType(stmtList, type);

	return stmtList;
}

bool PKBMain::isExecutedAfter(int stmtAft) {
	return nextTable.isExecutedAfter(stmtAft);
}

bool PKBMain::hasNext() {
	return nextTable.hasNext();
}

list<int> PKBMain::getAllExecutedAfter(Entity type) {
	list<int> stmtList;

	stmtList = nextTable.getAllExecutedAfter();
	stmtList = stmtTypeList.getStmtType(stmtList, type);

	return stmtList;
}

list<int> PKBMain::getExecutedBefore(int stmtAft, Entity type) {
	list<int> stmtList;

	stmtList = nextTable.getExecutedBefore(stmtAft);
	stmtList = stmtTypeList.getStmtType(stmtList, type);
	
	return stmtList;
}

list<int> PKBMain::getAllExecutedBefore(Entity type) {
	list<int> stmtList;

	stmtList = nextTable.getAllExecutedBefore();
	stmtList = stmtTypeList.getStmtType(stmtList, type);
	
	return stmtList;
}

pair<list<int>, list<int>> PKBMain::getAllNext(Entity type1, Entity type2) {
	pair<list<int>, list<int>>  resultPair = nextTable.getAllNext();

	return stmtTypeList.getStmtType(resultPair, type1, type2);
}

bool PKBMain::isPresent(string var)
{
	return varIdxTable.isVarPresent(var);
}

bool PKBMain::isPresent(int stmtNum)
{
	return stmtTypeList.isPresent(stmtNum);
}

bool PKBMain::isStatement(int stmtNum) {
	return stmtTypeList.isStatement(stmtNum);
}

bool PKBMain::isAssignment(int stmtNum)
{
	return stmtTypeList.isAssignStmt(stmtNum);
}

bool PKBMain::isCall(int stmtNum) {
	return stmtTypeList.isCallsStmt(stmtNum);
}

bool PKBMain::isConstant(int constant) {
	return constantTable.isConstant(constant);
}

bool PKBMain::isProgLine(int progLine) {
	return isStatement(progLine);
}

bool PKBMain::isProcedure(string procName) {
	return procIdxTable.isProcedure(procName);
}

bool PKBMain::isVariable(string varName) {
	if (varIdxTable.getIdxFromVar(varName) == -1) {
		return false;
	}
	return true;
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

list<string> PKBMain::getAllVariableNames() {
	return varIdxTable.getAllVariables();
}
list<int> PKBMain::getAllProcedures() {
	return procIdxTable.getAllProceduresIndex();
}

list<string> PKBMain::getAllProcNames() {
	return procIdxTable.getAllProceduresName();
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
	int varIdx = varIdxTable.getIdxFromVar(var);
	bool added = patternTable.addToPatternTable(stmt, varIdx, expression);
	return added;
}

bool PKBMain::isUses(int stmt, int varIdx)
{
    return usesTableStmtToVar.isUses(stmt, varIdx);
}

bool PKBMain::isUsesProc(int procIdx, int varIdx) {
	return usesTableProcToVar.isUses(procIdx, varIdx);
}

bool PKBMain::isUsesProc(string procName, string varName) {
	int procIdx = procIdxTable.getIdxFromProc(procName);
	int varIdx = varIdxTable.getIdxFromVar(varName);

	if (procIdx == -1 || varIdx == -1) {
		return false;
	}

	return usesTableProcToVar.isUses(procIdx, varIdx);
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

bool PKBMain::isModProc(string procName, string varName) {
	int procIdx = procIdxTable.getIdxFromProc(procName);
	int varIdx = varIdxTable.getIdxFromVar(varName);

	if (procIdx == -1 || varIdx == -1) {
		return false;
	}

	return modTableProcToVar.isMod(procIdx, varIdx);
}

bool PKBMain::isModProc(int procIdx, int varIdx) {
	return modTableProcToVar.isMod(procIdx, varIdx);
}

bool PKBMain::isMod(int stmt, int varIdx)
{
	return modTableStmtToVar.isMod(stmt, varIdx);
}

bool PKBMain::isUsingAnything(int stmt)
{
	return usesTableStmtToVar.isUsingAnything(stmt);
}

bool PKBMain::isUsingAnythingProc(string procName) {
	int procIdx = procIdxTable.getIdxFromProc(procName);
	if (procIdx == -1) {
		return false;
	}

	return usesTableProcToVar.isUsingAnything(procIdx);
}

bool PKBMain::isModifyingAnything(int stmt)
{
	return modTableStmtToVar.isModifyingAnything(stmt);
}

bool PKBMain::isModifyingAnythingProc(string procName) {
	int procIdx = procIdxTable.getIdxFromProc(procName);
	if (procIdx == -1) {
		return false;
	}

	return modTableProcToVar.isModifyingAnything(procIdx);
}

list<int> PKBMain::getUsesFromStmt(int stmt)
{
	return usesTableStmtToVar.getUsesVariablesFromStmt(stmt);
}

list<int> PKBMain::getUsesFromProc(string procName) {
	int procIdx = procIdxTable.getIdxFromProc(procName);
	if (procIdx == -1) {
		return list<int>();
	}
	
	return usesTableProcToVar.getUsesVariablesFromProc(procIdx);
}

list<int> PKBMain::getUsesFromProc(int procIdx) {
	return usesTableProcToVar.getUsesVariablesFromProc(procIdx);
}

list<int> PKBMain::getModifiesFromStmt(int stmt)
{
	return modTableStmtToVar.getModVariablesFromStmt(stmt);
}

list<int> PKBMain::getModifiesFromProc(string procName) {
	int procIdx = procIdxTable.getIdxFromProc(procName);
	if (procIdx == -1) {
		return list<int>();
	}

	return modTableProcToVar.getModVariablesFromProc(procIdx);
}

list<int> PKBMain::getModifiesFromProc(int procIdx) {
	return modTableProcToVar.getModVariablesFromProc(procIdx);
}

list<int> PKBMain::getUsesFromVar(string var, Entity type)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	if (varIdx == -1) {
		return list<int>();
	}
	list<int> resultList = stmtTypeList.getStmtType(usesTableVar.getUsesStmtsFromVar(varIdx), type);
	return resultList;
}

list<int> PKBMain::getUsesFromVar(int varIdx, Entity type) {
	list<int> resultList = stmtTypeList.getStmtType(usesTableVar.getUsesStmtsFromVar(varIdx), type);
	return resultList;
}

list<int> PKBMain::getProcUsesFromVar(string var) {
	int varIdx = varIdxTable.getIdxFromVar(var);
	if (varIdx == -1) {
		return list<int>();
	}
	list<int> resultList = usesTableVar.getUsesProcsFromVar(varIdx);
	return resultList;
}

list<int> PKBMain::getProcUsesFromVar(int varIdx) {
	return usesTableVar.getUsesProcsFromVar(varIdx);
}

list<int> PKBMain::getModifiesFromVar(string var, Entity type)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	if (varIdx == -1) {
		return list<int>();
	}
	list<int> resultList = stmtTypeList.getStmtType(modTableVar.getModStmtsFromVar(varIdx), type);
	return resultList;
}

list<int> PKBMain::getModifiesFromVar(int varIdx, Entity type) {
	list<int> resultList = stmtTypeList.getStmtType(modTableVar.getModStmtsFromVar(varIdx), type);
	return resultList;
}

list<int> PKBMain::getProcModifiesFromVar(string var) {
	int varIdx = varIdxTable.getIdxFromVar(var);
	if (varIdx == -1) {
		return list<int>();
	}
	list<int> resultList = modTableVar.getModProcsFromVar(varIdx);
	return resultList;
}

list<int> PKBMain::getProcModifiesFromVar(int varIdx) {
	return modTableVar.getModProcsFromVar(varIdx);
}

list<int> PKBMain::getStmtThatUsesAnything(Entity type)
{
	list<int> stmtList = usesTableStmtToVar.getStmtThatUses();
	return stmtTypeList.getStmtType(stmtList, type);
}

list<int> PKBMain::getProcThatUsesAnything()
{
	list<int> procList = usesTableProcToVar.getProcThatUses();
	return procList;
}

list<int> PKBMain::getProcThatModifiesAnything() {
	list<int> procList = modTableProcToVar.getProcThatModifies();
	return procList;
}

list<int> PKBMain::getStmtThatModifiesAnything(Entity type)
{
	list<int> stmtList = modTableStmtToVar.getStmtThatModifies();
	return stmtTypeList.getStmtType(stmtList, type);
}

list<int> PKBMain::getStmtThatModifiesAnything() {
	list<int> procList = modTableProcToVar.getProcThatModifies();
	return procList;
}

pair<list<int>, list<int>> PKBMain::getUsesPairs(Entity type)
{
	pair<list<int>, list<int>> usesPairs = usesTableStmtToVar.getUsesPair();
	return stmtTypeList.getStmtType(usesPairs, type);
}

pair<list<int>, list<int>> PKBMain::getProcUsesPair() {
	pair<list<int>, list<int>> procUsesPair = usesTableProcToVar.getProcPair();
	return procUsesPair;
}

pair<list<int>, list<int>> PKBMain::getModifiesPairs(Entity type)
{
	pair<list<int>, list<int>> modPairs = modTableStmtToVar.getModPair();
	return stmtTypeList.getStmtType(modPairs, type);
}

pair<list<int>, list<int>> PKBMain::getProcModifiesPair() {
	pair<list<int>, list<int>> procModPair = modTableProcToVar.getProcPair();
	return procModPair;
}

pair<list<int>, list<int>> PKBMain::getLeftVariables()
{
	return patternTable.getLeftVariables();
}

list<int> PKBMain::getWhilesWithControlVariable(string var) {
	int varIdx = varIdxTable.getIdxFromVar(var);
	return patternTable.getWhileWithControlVariable(varIdx);
}

list<int> PKBMain::getIfsWithControlVariable(string var) {
	int varIdx = varIdxTable.getIdxFromVar(var);
	return patternTable.getIfWithControlVariable(varIdx);
}
pair<list<int>, list<int>> PKBMain::getLeftVariablesThatPartialMatchWith(string expression)
{
	return patternTable.getLeftVariableThatPartialMatchWithString(expression);
}

pair<list<int>, list<int>> PKBMain::getLeftVariablesThatExactMatchWith(string expression) {
	return patternTable.getLeftVariableThatExactMatchWithString(expression);
}

bool PKBMain::isWhileControlVar(int stmt, int varIdx) {
	return patternTable.isWhileControlVar(stmt, varIdx);
}

bool PKBMain::isIfControlVar(int stmt, int varIdx) {
	return patternTable.isIfControlVar(stmt, varIdx);
}

pair<list<int>, list<int>> PKBMain::getControlVariablesInWhile() {
	return patternTable.getControlVariablesInWhile();
}

list<int> PKBMain::getControlVariablesInIf(int stmt) {
	return patternTable.getControlVariablesInIf(stmt);
}

list<int> PKBMain::getControlVariablesInWhile(int stmt) {
	return patternTable.getControlVariablesInWhile(stmt);
}

pair<list<int>, list<int>> PKBMain::getControlVariablesInIf() {
	return patternTable.getControlVariablesInIf();
}

list<int> PKBMain::getWhileFromControlVar(int varIdx) {
	return patternTable.getWhileFromControlVar(varIdx);
}

list<int> PKBMain::getIfFromControlVar(int varIdx) {
	return patternTable.getIfFromControlVar(varIdx);
}

list<int> PKBMain::getPartialMatchStmt(string expression)
{
	return patternTable.getPartialMatchStmt(expression);
}

list<int> PKBMain::getPartialMatchVar(int stmt, string expression) {
	return patternTable.getPartialMatchVar(stmt, expression);
}

list<int> PKBMain::getExactMatchVar(int stmt, string expression) {
	return patternTable.getExactMatchVar(stmt, expression);
}

list<int> PKBMain::getPartialBothMatches(string var, string expression)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	return patternTable.getPartialBothMatches(varIdx, expression);
}

list<int> PKBMain::getPartialBothMatches(int varIdx, string expression) {
	return patternTable.getPartialBothMatches(varIdx, expression);
}

list<int> PKBMain::getExactMatchStmt(string expression)
{
	return patternTable.getExactMatchStmt(expression);
}

list<int> PKBMain::getExactBothMatches(string var, string expression)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	return patternTable.getExactBothMatches(varIdx, expression);
}

list<int> PKBMain::getExactBothMatches(int varIdx, string expression) {
	return patternTable.getExactBothMatches(varIdx, expression);
}

bool PKBMain::isExactMatch(int stmt, int varIdx, string expression) {
	return patternTable.isExactMatch(stmt, varIdx, expression);
}

bool PKBMain::isPartialMatch(int stmt, int varIdx, string expression) {
	return patternTable.isPartialMatch(stmt, varIdx, expression);
}

list<int> PKBMain::getAllAssignments()
{
	return stmtTypeList.getAssignStmtList();
}

list<int> PKBMain::getAllAssignments(string var)
{
	int varIdx = varIdxTable.getIdxFromVar(var);
	list<int> stmtList = patternTable.getLeftVariableMatchingStmts(varIdx);
	return stmtTypeList.getStmtType(stmtList, ASSIGN);
}

list<int> PKBMain::getAllAssignments(int varIdx) {

	list<int> stmtList = patternTable.getLeftVariableMatchingStmts(varIdx);
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

bool PKBMain::addWhileStmt(int stmt, string controlVar) {
	addVariable(controlVar);
	int varIdx = varIdxTable.getIdxFromVar(controlVar);
	bool added = stmtTypeList.addToWhileStmtList(stmt);
	patternTable.addWhile(stmt, varIdx);
	return true;
}

bool PKBMain::addIfStmt(int stmt, string controlVar)
{
	addVariable(controlVar);
    bool added = stmtTypeList.addToIfStmtList(stmt);
	int varIdx = varIdxTable.getIdxFromVar(controlVar);
	patternTable.addIf(stmt, varIdx);
    return added;
}

bool PKBMain::addConstant(int stmt, int constant)
{
	bool added = constantTable.addConstantList(stmt, constant);
	return added;
}
