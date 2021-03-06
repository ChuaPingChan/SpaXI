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

bool PKBMain::deleteInstance()
{
    delete singleton;
    singleton = NULL;
    return true;
}

void PKBMain::resetInstance()
{
    if (singleton != NULL) {
        PKBMain::deleteInstance();
    }
    singleton = new PKBMain();
}

void PKBMain::clearCache()
{
    cache = Cache();
}

//Utility functions
/*
Return true if all procedured called exists
*/
bool PKBMain::calledProceduresExist() {
    return allCalledProceduresExist;
}

/*
Return true if the code has recursive calls
*/
bool PKBMain::hasRecursion() {
    return hasRecursiveCalls;
}
/*
This method checks if the name of the entity given its index is the same as
the other entity given its index
*/
bool PKBMain::isSameName(Entity type1, int idx1, Entity type2, int idx2) {
    string arg1 = convertIdxToString(idx1, type1);
    string arg2 = convertIdxToString(idx2, type2);

    return arg1 == arg2;
}

/*
This method converts the index of the entity to its string name
*/
string PKBMain::convertIdxToString(int index, Entity type) {
    string result;
    if (type == PROCEDURE) {
        result = procIdxTable.getProcFromIdx(index);
    }

    if (type == CALL) {
        result = stmtTypeList.getCalleeProcNameFromStmt(index);
    }

    if (type == VARIABLE) {
        result = varIdxTable.getVarFromIdx(index);
    }

    return result;
}

/*
This method converst the list of index of a given entity to
a list of string name
*/
list<string> PKBMain::convertIdxToString(list<int> indexList, Entity type) {
    list<string> resultList;
    string result;
    if (type == PROCEDURE)
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

    if (type == CALL) {
        for (int i : indexList)
        {
            result = stmtTypeList.getCalleeProcNameFromStmt(i);
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

/*
This method converts a string of its given entity
to its index
*/
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

/*
This method converts a list of string of a given entity
to its list of indexes
*/
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

/*
This method returns the list of all entities of integer type
*/
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

    else if (type == CONSTANT) {
        return getAllConstants();
    }

    else if (type == IF) {
        return getAllIfs();
    }

    else if (type == PROG_LINE) {
        return getAllStatements();
    }

    else {
        return list<int>();
    }
}

/*
This method returns alls the index of string entities
*/
list<int> PKBMain::getAllIdxOfStringEntity(Entity type) {
    if (type == PROCEDURE) {
        return getAllProcedures();
    }

    else if (type == CALL) {
        return getAllCallsStmt();
    }

    else if (type == VARIABLE) {
        return getAllVariables();
    }

    else {
        return list<int>();
    }
}

/*
This method checks if the given arguments is of a
certain entity type
*/
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

/*
This method checks if the string is of a certain entity type
*/
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

//STMTLST
bool PKBMain::addStmtList(int stmt) {
    return stmtTypeList.addToStmtList(stmt);
}

list<int> PKBMain::getStmtList() {
    return stmtTypeList.getStmtList();
}

//CALLS
/*
Returns names of called procedures
*/
list<string> PKBMain::getAllCalleeNames() {
    return stmtTypeList.getAllCalleeNames();
}

/*
Returns the call statement which calls the given procedure
*/
list<int> PKBMain::getStmtFromCallee(string callee) {
    return stmtTypeList.getStmtFromCalleeProcName(callee);
}

/*
Set the calls relation and populate PKB accordingly
*/
bool PKBMain::setCallsRel(int stmt, string callerProcName, string calleeProcName) {
    int callerProcIdx = procIdxTable.getIdxFromProc(callerProcName);
    calledProcedures.insert(calleeProcName);
    if (procIdxTable.getIdxFromProc(calleeProcName) == -1) {
        procIdxTable.addToProcIdxTable(calleeProcName);
    }

    int calleeProcIdx = procIdxTable.getIdxFromProc(calleeProcName);
    stmtTypeList.addToCallsStmtList(stmt, calleeProcIdx, calleeProcName);
    return callsTable.addCallsRel(callerProcIdx, calleeProcIdx) && callsTable.addCallsStmt(stmt, calleeProcIdx);
}

/*
Checks if calls relationship is true
*/
bool PKBMain::isCalls(string callerProcName, string calleeProcName) {
    int callerProcIdx = procIdxTable.getIdxFromProc(callerProcName);
    int calleeProcIdx = procIdxTable.getIdxFromProc(calleeProcName);

    if (callerProcIdx == -1 || calleeProcIdx == -1) {
        return false;
    }

    return callsTable.isCalls(callerProcIdx, calleeProcIdx);
}

/*
Checks if calls relationship is true given procedure index
*/
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

/*
Get callers of given procedure
*/
list<int> PKBMain::getCaller(string calleeProcName) {
    int calleeProcIdx = procIdxTable.getIdxFromProc(calleeProcName);
    return callsTable.getCaller(calleeProcIdx);
}

/*
Get callers of given procedure index
*/
list<int> PKBMain::getCaller(int calleeProcIdx) {
    return callsTable.getCaller(calleeProcIdx);
}

list<int> PKBMain::getAllCallers() {
    return callsTable.getAllCallers();
}

/*
Returns a pair of list of calls relations
*/
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
/*
Set the given parent child relationship
*/
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

/*
Gets parent statements of specified entity type
*/
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

//FOLLOWS
pair<list<int>, list<int>> PKBMain::getAllFollows(Entity type1, Entity type2) {
    pair<list<int>, list<int>> allFollows = followsTable.getAllFollows();
    pair<list<int>, list<int>> resultPair = stmtTypeList.getStmtType(allFollows, type1, type2);
    return resultPair;
}

bool PKBMain::hasFollows() {
    return followsTable.hasFollows();
}

bool PKBMain::setFollowsRel(int stmtBef, int stmtCurr) {
    if (stmtBef != 0) {
        followsTable.addFollows(stmtBef, stmtCurr);
    }
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
    return followsTable.getStmtBef(currStmt);
}

int PKBMain::getAfter(int currStmt) {
    return followsTable.getStmtAft(currStmt);
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

/*
Processes the complex relations with help from design extractor
*/
bool PKBMain::startProcessComplexRelations() {
    allCalledProceduresExist = checkAllCalledProceduresExist();
    childToParentStarTable.setMap(de.computeChildToParentStarTable(childToParentTable));
    parentToChildStarTable.setMap(de.computeParentToChildStarTable(parentToChildTable));
    followsStarAfter.setMap(de.computeFollowsStarAfterTable(followsTable));
    followsStarBefore.setMap(de.computeFollowsStarBeforeTable(followsTable));
    callsStarTable.setCallsStarMap(de.computeCallsStarTable(callsTable));
    hasRecursiveCalls = checkHasRecursiveCalls();
    usesTableProcToVar.setMap(de.computeUsesTable(usesTableProcToVar, callsStarTable));
    modTableProcToVar.setMap(de.computeModifiesTable(modTableProcToVar, callsStarTable));
    usesTableStmtToVar.setMap(de.computeUsesTable(usesTableStmtToVar, stmtTypeList, usesTableProcToVar, childToParentStarTable));
    modTableStmtToVar.setMap(de.computeModifiesTable(modTableStmtToVar, stmtTypeList, modTableProcToVar, childToParentStarTable));
    usesTableVar.setStmtMap(de.computeUsesTableStmt(usesTableStmtToVar));
    usesTableVar.setProcMap(de.computeUsesTableProc(usesTableProcToVar));
    modTableVar.setStmtMap(de.computeModTableStmt(modTableStmtToVar));
    modTableVar.setProcMap(de.computeModTableProc(modTableProcToVar));
    return true;
}

bool PKBMain::checkAllCalledProceduresExist() {
    for (string callee : calledProcedures) {
        if (existingProcedures.find(callee) == existingProcedures.end()) {
            return false;
        }
    }
    return true;
}

bool PKBMain::checkHasRecursiveCalls() {
    list<int> callers = getAllCallers();
    for (int caller : callers) {
        if (isCallsStar(caller, caller)) {
            return true;
        }
    }

    return false;
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

bool PKBMain::isNextStar(int befStmt, int aftStmt) {
    return nextTable.isNextStar(befStmt, aftStmt);
}

list<int> PKBMain::getExecutedAfterStar(int befStmt, Entity type) {
    list<int> stmtList;
    if (cache.containsAllNextStar(STMT, STMT)) { // If all next* has been computed before
        unordered_map<int, list<int>> nextStarMap = cache.getNextStarMap();
        if (nextStarMap.find(befStmt) != nextStarMap.end()) {
            stmtList = nextStarMap[befStmt];
        }
    }
    else {
        stmtList = nextTable.getExecutedAfterStar(befStmt);
    }

    stmtList = stmtTypeList.getStmtType(stmtList, type);
    return stmtList;
}

list<int> PKBMain::getExecutedBeforeStar(int aftStmt, Entity type) {
    list<int> stmtList;
    if (cache.containsAllNextStar(STMT, STMT)) {
        unordered_map<int, list<int>> nextStarMapReverse = cache.getNextStarMapReverse();
        if (nextStarMapReverse.find(aftStmt) != nextStarMapReverse.end()) {
            stmtList = nextStarMapReverse[aftStmt];
        }
    }
    else {
        stmtList = nextTable.getExecutedBeforeStar(aftStmt);
    }

    stmtList = stmtTypeList.getStmtType(stmtList, type);
    return stmtList;
}

list<int> PKBMain::getAllNextStarSameSyn(Entity type) {
    list<int> entityTypeList = getAllIntOfIntEntity(type);
    list<int> resultList;

    for (int stmt : entityTypeList) {
        if (isNextStar(stmt, stmt)) {
            resultList.push_back(stmt);
        }
    }

    return resultList;
}

pair<list<int>, list<int>> PKBMain::getAllNextStar(Entity type1, Entity type2) {
    pair<list<int>, list<int>> resultPair;
    if (cache.containsAllNextStar(type1, type2)) {
        return cache.getAllNextStar(type1, type2);
    }

    else if (cache.containsAllNextStar(STMT, STMT)) {
        resultPair = stmtTypeList.getStmtType(cache.getAllNextStar(STMT, STMT), type1, type2);
        cache.putAllNextStar(resultPair, type1, type2);
        return resultPair;
    }

    else {
        // Compute all next star relations and store them in the cache
        unordered_map<int, list<int>> nextStarMap;
        unordered_map<int, list<int>> nextStarMapReverse;
        unordered_map<int, unordered_set<int>> nextStarRelMap;
        pair<list<int>, list<int>> resultPair = nextTable.getAllNextStar(nextStarMap, nextStarMapReverse, nextStarRelMap);
        cache.putAllNextStar(resultPair, STMT, STMT);
        resultPair = stmtTypeList.getStmtType(resultPair, type1, type2);
        cache.putAllNextStar(nextStarMap, nextStarMapReverse, nextStarRelMap);
        cache.putAllNextStar(resultPair, type1, type2);
        return resultPair;
    }
}

/*
Checks if var exists
*/
bool PKBMain::isPresent(string var)
{
    return varIdxTable.isVarPresent(var);
}

/*
Checks if statement exists
*/
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

//USES AND MODIFIES

bool PKBMain::setModTableStmtToVar(int stmt, string var)
{
    int varIdx = varIdxTable.getIdxFromVar(var);
    bool added = modTableStmtToVar.addModStmtToVarList(stmt, varIdx);
    added = modTableVar.addModVarToStmtList(varIdx, stmt);
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

/*
Checks if procedure uses given variable
*/
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

/*
Check if procedure modifies given variable
*/
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
    if (procIdx == -1) { //check if procedure exists
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
    if (procIdx == -1) { //check if procedure exists
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
    return stmtTypeList.getStmtType(usesPairs, type); //Sieve through
}

pair<list<int>, list<int>> PKBMain::getProcUsesPair() {
    pair<list<int>, list<int>> procUsesPair = usesTableProcToVar.getProcPair();
    return procUsesPair;
}

pair<list<int>, list<int>> PKBMain::getModifiesPairs(Entity type)
{
    pair<list<int>, list<int>> modPairs = modTableStmtToVar.getModPair();
    return stmtTypeList.getStmtType(modPairs, type); //Sieve through
}

pair<list<int>, list<int>> PKBMain::getProcModifiesPair() {
    pair<list<int>, list<int>> procModPair = modTableProcToVar.getProcPair();
    return procModPair;
}

//PATTERN
/*
This method gets variables that are on the left side of a pattern clause
i.e.
pattern a (v, _) this will get all v
*/
pair<list<int>, list<int>> PKBMain::getLeftVariables()
{
    return patternTable.getLeftVariables();
}

/*
Returns the while statements with the given control variable
Returns empty list of theres is no while with such control variable
*/
list<int> PKBMain::getWhilesWithControlVariable(string var) {
    int varIdx = varIdxTable.getIdxFromVar(var);
    return patternTable.getWhileWithControlVariable(varIdx);
}

/*
Returns the if statements that has the given control var
*/
list<int> PKBMain::getIfsWithControlVariable(string var) {
    int varIdx = varIdxTable.getIdxFromVar(var);
    return patternTable.getIfWithControlVariable(varIdx);
}

/*
Get variables on the left of pattern clause that match partially with the given
substring expression
*/
pair<list<int>, list<int>> PKBMain::getLeftVariablesThatPartialMatchWith(string expression)
{
    return patternTable.getLeftVariableThatPartialMatchWithString(expression);
}

/*
Get variables on the left of the pattern clause that match exactly with the given
expression
*/
pair<list<int>, list<int>> PKBMain::getLeftVariablesThatExactMatchWith(string expression) {
    return patternTable.getLeftVariableThatExactMatchWithString(expression);
}

bool PKBMain::isWhileControlVar(int stmt, int varIdx) {
    return patternTable.isWhileControlVar(stmt, varIdx);
}

bool PKBMain::isIfControlVar(int stmt, int varIdx) {
    return patternTable.isIfControlVar(stmt, varIdx);
}

/*
Gets a pair of all while and their respective control variables
*/
pair<list<int>, list<int>> PKBMain::getControlVariablesInWhile() {
    return patternTable.getControlVariablesInWhile();
}

list<int> PKBMain::getControlVariablesInIf(int stmt) {
    return patternTable.getControlVariablesInIf(stmt);
}

list<int> PKBMain::getControlVariablesInWhile(int stmt) {
    return patternTable.getControlVariablesInWhile(stmt);
}

/*
Gets a pair of all if and their respective control variables
*/
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

/*
Gets all statements that exact match with the variable and the subtring expression
*/
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

/*
Returns all assignment statements
*/
list<int> PKBMain::getAllAssignments()
{
    return stmtTypeList.getAssignStmtList();
}

/*
Returns all assignment statements that modifies the given variable
*/
list<int> PKBMain::getAllAssignments(string var)
{
    int varIdx = varIdxTable.getIdxFromVar(var);
    list<int> stmtList = patternTable.getLeftVariableMatchingStmts(varIdx);
    return stmtTypeList.getStmtType(stmtList, ASSIGN);
}

/*
Returns all assignment statements taht modifies the given variable index
*/
list<int> PKBMain::getAllAssignments(int varIdx) {

    list<int> stmtList = patternTable.getLeftVariableMatchingStmts(varIdx);
    return stmtTypeList.getStmtType(stmtList, ASSIGN);
}

/*
Add variable to PKB
*/
bool PKBMain::addVariable(string var)
{
    bool added = varIdxTable.addToVarIdxTable(var);
    return added;
}

/*
Add procedure to PKB
*/
bool PKBMain::addProcedure(string proc)
{
    bool added = procIdxTable.addToProcIdxTable(proc);
    existingProcedures.insert(proc); // For use later to check that all called procedures exists
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

bool PKBMain::addConstant(int constant)
{
    bool added = constantTable.addConstantList(constant);
    return added;
}

bool PKBMain::addStmtToProc(int stmt, string procName) {
    int procIdx = procIdxTable.getIdxFromProc(procName);
    if (procIdx == -1) {
        return false;
    }

    if (procIdxTable.getProcIdxFromStmt(stmt) != -1) {
        return false;
    }

    return procIdxTable.addStmtToProc(stmt, procIdx);
}

int PKBMain::getFirstStmtFromProc(int procIdx) {
    int firstStmt = procIdxTable.getFirstStmtFromProc(procIdx);
    return firstStmt;
}

int PKBMain::getProcFromStmt(int stmt) {
    return procIdxTable.getProcIdxFromStmt(stmt);
}

/*
This method checks if the affects relation is true for two statements
*/
bool PKBMain::isAffects(int stmt1, int stmt2) {
    // check if both are assignment first
    if (!isAssignment(stmt1) || !isAssignment(stmt2)) {
        return false;
    }

    // check if both in the same procedure
    if (getProcFromStmt(stmt1) != getProcFromStmt(stmt2)) {
        return false;
    }

    list<int> varModified = getModifiesFromStmt(stmt1);
    list<int> varUsed = getUsesFromStmt(stmt2);

    int varMod = varModified.front();
    if (find(varUsed.begin(), varUsed.end(), varMod) == varUsed.end()) { // if stmt2 doesnt used what stmt1 modifies
        return false;
    }

    queue<int> path;
    unordered_map<int, int> visit;
    visit[stmt1] = -1;
    path.push(stmt1);

    while (!path.empty()) {
        int currStmt = path.front();
        path.pop();

        if (currStmt == stmt2 && visit[currStmt] != -1) { //
            return true;
        }

        else if (visit[currStmt] == 1) {
            //visited
            continue;
        }

        else if (isWhile(currStmt)) { // push nodes to visit from while loop
            visit[currStmt] = 1;
            list<int> currChildrenStar = getChildrenStar(currStmt, STMT);
            currChildrenStar.sort();
            if (stmt2 >= currChildrenStar.front() && stmt2 <= currChildrenStar.back()) {
                path.push(currStmt + 1);
            }
            else {
                list<int> currNext = getExecutedAfter(currStmt, STMT);
                for (int tempNext : currNext) {
                    if (tempNext != currStmt + 1) {
                        path.push(tempNext);
                    }
                }
            }
        }

        else if (isIf(currStmt)) {
            visit[currStmt] = 1;
            list<int> currNext = getExecutedAfter(currStmt, STMT);
            for (int tempNext : currNext) {
                path.push(tempNext);
            }
        }

        else {
            list<int> currModifies = getModifiesFromStmt(currStmt); // check if statement modifies the var in our orig stmt
            if (visit[currStmt] == -1 || find(currModifies.begin(), currModifies.end(), varMod) == currModifies.end()) {
                list<int> currNext = getExecutedAfter(currStmt, STMT);
                for (int tempNext : currNext) {
                    path.push(tempNext);
                }
            }
            visit[currStmt] = 1;
        }
    }

    return false;

}

/*
Check if statement is one that affects a statement
*/
bool PKBMain::isAffector(int stmt1) {
    list<int> nextStarList = getExecutedAfterStar(stmt1, STMT);
    for (int next : nextStarList) {
        if (isAffects(stmt1, next)) {
            return true;
        }
    }
    return false;
}

/*
Gets all statement affected by given statement
*/
list<int> PKBMain::getAffectedOf(int stmt1) {
    list<int> affectedList;
    list<int> nextStarList = getExecutedAfterStar(stmt1, STMT);
    for (int next : nextStarList) {
        if (isAffects(stmt1, next)) {
            affectedList.push_back(next);
            affectedList.sort();
            affectedList.unique();
        }
    }
    return affectedList;
}

bool PKBMain::isAffected(int stmt2) {
    list<int> prevStarList = getExecutedBeforeStar(stmt2, STMT);
    for (int prev : prevStarList) {
        if (isAffects(prev, stmt2)) {
            return true;
        }
    }
    return false;
}

/*
Checks if there exists any affects relation
*/
bool PKBMain::hasAffects() {
    list<int> allStmts = getAllAssignments();
    for (int stmt : allStmts) {
        list<int> nextStarList = getExecutedAfterStar(stmt, STMT);
        for (int next : nextStarList) {
            if (isAffects(stmt, next)) {
                return true;
            }
        }
    }
    return false;
}

/*
Get all statements that are somehow affected by given statement
*/
list<int> PKBMain::getAllAffected() {
    list<int> affectedList;
    list<int> allStmts = getAllAssignments();
    for (int stmt : allStmts) {
        list<int> nextStarList = getExecutedAfterStar(stmt, STMT);
        for (int next : nextStarList) {
            if (isAffects(stmt, next)) {
                affectedList.push_back(next);
                affectedList.sort();
                affectedList.unique();
            }
        }
    }
    return affectedList;
}

list<int> PKBMain::getAffectorOf(int stmt2) {
    list<int> affectorList;
    list<int> prevStarList = getExecutedBeforeStar(stmt2, STMT);
    for (int prev : prevStarList) {
        if (isAffects(prev, stmt2)) {
            affectorList.push_back(prev);
            affectorList.sort();
            affectorList.unique();
        }
    }
    return affectorList;
}

list<int> PKBMain::getAllAffector() {
    list<int> affectorList;
    list<int> allStmts = getAllAssignments();
    for (int stmt : allStmts) {
        list<int> prevStarList = getExecutedBeforeStar(stmt, STMT);
        if (prevStarList.size() == 0) {
            continue;
        }
        for (int prev : prevStarList) {
            if (isAffects(prev, stmt)) {
                affectorList.push_back(prev);
                affectorList.sort();
                affectorList.unique();
            }
        }
    }
    return affectorList;
}

list<int> PKBMain::getAllFirstStmtOfProc() {
    list<int> allProcIdx = getAllProcedures();
    list<int> allFirstStmt;
    for (int proc : allProcIdx) {
        allFirstStmt.push_back(procIdxTable.getFirstStmtFromProc(proc));
    }

    return allFirstStmt;
}

/*
Algorithm to extract all affects relation in a procedure given its first statement
*/
pair<list<int>, list<int>> PKBMain::getAllAffects(int stmt, unordered_map<int, unordered_set<int>> &affectsRelMap) {
    int curr = stmt; // Initialise curr as first statement
    list<int> prevList;
    list<int> nextList;
    unordered_map<int, unordered_set<int>> latestMod; //varIdx to stmt where its directly modified
    stack<pair<int, unordered_map<int, unordered_set<int>>>> whileMapStack;
    stack<IfStmt> ifMapStack;
    while (curr != 0) {
        if (AbstractWrapper::GlobalStop) {
            break;
        }
        if (isAssignment(curr)) {
            list<int> usedVarList = getUsesFromStmt(curr);
            for (int usedVar : usedVarList) {
                if (latestMod.find(usedVar) != latestMod.end()) { // If the used variable has a statement that directly modifies it
                    unordered_set<int> lastModStmtSet = latestMod[usedVar];
                    for (auto &lastModStmt : lastModStmtSet) {
                        if (!isCall(lastModStmt)) { // Make sure its not call statement as affects is only between assignments
                            if ((affectsRelMap.find(lastModStmt) != affectsRelMap.end() &&
                                affectsRelMap[lastModStmt].find(curr) == affectsRelMap[lastModStmt].end()) ||
                                affectsRelMap.find(lastModStmt) == affectsRelMap.end()) { //Make sure relation is not already inside the map
                                prevList.push_back(lastModStmt);
                                nextList.push_back(curr);
                                affectsRelMap[lastModStmt].insert(curr);
                            }
                        }
                    }
                }
            }

            int modifiedVar = getModifiesFromStmt(curr).front(); // Get the modified variable in curr statement
            latestMod[modifiedVar].clear(); // Clear the map from before as the current path does not allow this
            latestMod[modifiedVar].insert(curr); // Reinsert current statement to the map
            list<int> nextStmtList = getExecutedAfter(curr, STMT);

            if (getParent(curr, IF).size() != 0) { // If it is a child of an if statement
                IfStmt ifStmt = ifMapStack.top();
                if (ifStmt.isEndIf(curr)) {
                    curr = processBranchIf(ifMapStack, latestMod);
                }

                else if (ifStmt.isEndElse(curr)) {
                    if (nextStmtList.size() == 0) { // no next after else i.e. pt to dummy
                        curr = processBranchElseWithNoNext(ifMapStack, latestMod);
                    }

                    else { // got next
                        curr = processBranchElseWithNext(ifMapStack, latestMod, nextStmtList.front());
                    }
                }

                else {
                    if (nextStmtList.size() == 0) { // If no other statements after
                        curr = 0; // Flag that curr = 0 to exit loop
                    }

                    else {
                        curr = nextStmtList.front();
                    }
                }
            }

            else { // If not a direct child of if statement, proceed as normal
                if (nextStmtList.size() == 0) {
                    curr = 0;
                }

                else {
                    curr = nextStmtList.front();
                }
            }
        }

        else if (isCall(curr)) { //Call statement doesnt have to both with relation, but need clear modified map
            list<int> modifiedVarList = getModifiesFromStmt(curr);
            for (int modifiedVar : modifiedVarList) {
                latestMod.erase(modifiedVar); // Erase modifies variable
            }

            list<int> nextStmtList = getExecutedAfter(curr, STMT);

            if (getParent(curr, IF).size() != 0) { //is in an if
                IfStmt ifStmt = ifMapStack.top();
                if (ifStmt.isEndIf(curr)) {
                    curr = processBranchIf(ifMapStack, latestMod);
                }

                else if (ifStmt.isEndElse(curr)) {
                    if (nextStmtList.size() == 0) { // no next after else i.e. pt to dummy
                        curr = processBranchElseWithNoNext(ifMapStack, latestMod);
                    }

                    else { // got next
                        curr = processBranchElseWithNext(ifMapStack, latestMod, nextStmtList.front());
                    }
                }

                else {
                    if (nextStmtList.size() == 0) {
                        curr = 0;
                    }

                    else {
                        curr = nextStmtList.front();
                    }
                }
            }

            else {
                if (nextStmtList.size() == 0) {
                    curr = 0;
                }

                else {
                    curr = nextStmtList.front();
                }
            }
        }

        else if (isWhile(curr)) {
            list<int> nextStmtList = getExecutedAfter(curr, STMT);
            int insideLoop = nextStmtList.front();
            int afterLoop = 0;

            if (nextStmtList.size() == 2) {
                afterLoop = nextStmtList.back();
            }

            // First time entering this while loop
            if (whileMapStack.empty() || whileMapStack.top().first != curr) {
                whileMapStack.push(make_pair(curr, latestMod));
                curr = insideLoop;
            }

            // Else have to check if we need to reiterate the loop or not
            else {
                pair<int, unordered_map<int, unordered_set<int>>> oldWhileMap = whileMapStack.top();
                int currWhile = oldWhileMap.first;
                unordered_map<int, unordered_set<int>> oldMod = oldWhileMap.second;
                if (oldMod == latestMod) { //If the modified maps are they same, means all relations have been captured
                    whileMapStack.pop();
                    // pop and merge
                    while (!whileMapStack.empty() && whileMapStack.top().first == currWhile) {
                        pair<int, unordered_map<int, unordered_set<int>>> prevWhile = whileMapStack.top();
                        whileMapStack.pop();
                        latestMod = joinMap(prevWhile.second, latestMod);
                    }

                    if (ifMapStack.empty()) {
                        curr = afterLoop;
                    }

                    else {
                        if (ifMapStack.top().isEndIf(curr)) { // Update if
                            curr = processBranchIf(ifMapStack, latestMod);
                        }

                        else {
                            if (ifMapStack.top().isEndElse(curr)) {
                                list<int> nextStmtList = getExecutedAfter(curr, STMT);
                                if (nextStmtList.size() != 0) { //has next
                                    curr = processBranchElseWithNext(ifMapStack, latestMod, afterLoop);
                                }

                                else {
                                    curr = processBranchElseWithNoNext(ifMapStack, latestMod);
                                }
                            }

                            else {
                                curr = afterLoop;
                            }
                        }
                    }

                }

                else {
                    whileMapStack.push(make_pair(curr, latestMod));
                    curr = insideLoop;
                }
            }


        }

        else { // if statement
            list<int> next = getExecutedAfter(curr, STMT);
            next.sort();
            int nextIf = next.front();
            int nextElse = next.back();
            list<int> followsIf = getAfterStar(nextIf, STMT);
            followsIf.sort();
            int endIf;
            if (followsIf.size() == 0) {
                endIf = 0;
            }
            else {
                endIf = followsIf.back();
            }
            if (endIf == 0) {
                endIf = nextIf;
            }
            list<int> children = getChildren(curr, STMT);
            children.sort();
            int endElse = children.back();
            list<int> afterIfList = getAfter(curr, STMT);
            int afterIf;
            if (afterIfList.size() == 0) {
                afterIf = 0;
            }

            else {
                afterIfList.sort();
                afterIf = afterIfList.front();
            }

            bool visitedElse = false;
            // updates if stack with the given if statements which contains all the required information when we work with if statements later
            IfStmt currIfStmt = IfStmt(curr, nextIf, endIf, nextElse, endElse, visitedElse, afterIf, latestMod, latestMod);
            ifMapStack.push(currIfStmt);
            curr = nextIf;
        }

    }

    return make_pair(prevList, nextList);
}

/*
This method returns the next statement required for us to enter when we are at end of an if block
*/
int PKBMain::processBranchIf(stack<IfStmt> &ifMapStack, unordered_map<int, unordered_set<int>> &latestMod) {
    IfStmt ifStmt = ifMapStack.top();
    ifMapStack.pop();
    ifStmt.setIfMap(latestMod);
    latestMod = ifStmt.getElseMap();
    int curr = ifStmt.getBranchElse();
    ifStmt.visitElse();
    ifMapStack.push(ifStmt);
    return curr;
}

/*
This returns the next statement we have to go into when we are at the end of an else block
with no next, such that its pointed to dummy node
*/
int PKBMain::processBranchElseWithNoNext(stack<IfStmt> &ifMapStack, unordered_map<int, unordered_set<int>> &latestMod) {
    int curr;
    IfStmt ifStmt = ifMapStack.top();
    latestMod = joinMap(ifStmt.getIfMap(), latestMod);
    ifMapStack.pop();
    if (ifMapStack.empty()) {
        curr = 0;
    }

    else {
        IfStmt parentIf = ifMapStack.top();
        if (parentIf.hasVisitedElse()) {
            // continue processing until we are no longer at else with no next
            curr = processBranchElseWithNoNext(ifMapStack, latestMod);
        }

        else {
            curr = processBranchIf(ifMapStack, latestMod);
        }
    }

    return curr;
}

/*
This returns the next statement we hav to go into when we are at the end of an else block
with next
*/
int PKBMain::processBranchElseWithNext(stack<IfStmt> &ifMapStack, unordered_map<int, unordered_set<int>> &latestMod, int next) {
    IfStmt ifStmt = ifMapStack.top();
    latestMod = joinMap(latestMod, ifStmt.getIfMap());
    int firstIfStmt = ifStmt.getStmtNum();
    int afterIf = ifStmt.getAfterIf();
    ifMapStack.pop();
    if (next == afterIf) {
        return next;
    }

    else {
        if (ifMapStack.empty()) {
            if (afterIf == 0) {
                return next;
            }
            return afterIf;
        }
        else if (isWhile(next)) {
            if (isParentChild(next, firstIfStmt)) {
                return next;
            }
            else {
                if (ifMapStack.top().hasVisitedElse()) {
                    return processBranchElseWithNext(ifMapStack, latestMod, next);
                }
                else {
                    return processBranchIf(ifMapStack, latestMod);
                }
            }
        }

        else {
            if (ifMapStack.top().isEndIf(firstIfStmt)) {
                return processBranchIf(ifMapStack, latestMod);
            }
            else {
                return processBranchElseWithNext(ifMapStack, latestMod, next);
            }
        }
    }
}

/*
This joins two maps and their key/values together
*/
unordered_map<int, unordered_set<int>> PKBMain::joinMap(unordered_map<int, unordered_set<int>> firstMap,
    unordered_map<int, unordered_set<int>> secondMap) {

    for (auto &key : firstMap) {
        if (secondMap.find(key.first) != secondMap.end()) {
            firstMap[key.first].insert(secondMap[key.first].begin(), secondMap[key.first].end());
        }
    }

    for (auto &key : secondMap) {
        if (firstMap.find(key.first) == firstMap.end()) {
            firstMap[key.first] = secondMap[key.first];
        }
    }

    return firstMap;
}

/*
Get all assignments that affects itself
*/
list<int> PKBMain::getAllAffectsSameSyn() {
    list<int> result;

    if (cache.containsAllAffectsSameSyn()) {
        return cache.getAllAffectsSameSyn();
    }

    if (!cache.containsAllAffects()) {
        getAllAffects();
    }

    unordered_map<int, unordered_set<int>> affectsRelMap = cache.getAllAffectsRelMap();

    for (auto &affectsRel : affectsRelMap) {
        if (affectsRel.second.find(affectsRel.first) != affectsRel.second.end()) {
            result.push_back(affectsRel.first);
        }
    }

    cache.putAllAffectsSameSyn(result);

    return result;
}

/*
This method iterates through each procedure and extract all affects relations for each of them
*/
pair<list<int>, list<int>> PKBMain::getAllAffects() {
    list<int> prevList;
    list<int> nextList;
    unordered_map<int, unordered_set<int>> affectsRelMap;
    if (cache.containsAllAffects()) {
        return cache.getAllAffects();
    }

    list<int> allFirstStmt = getAllFirstStmtOfProc();
    for (int stmt : allFirstStmt) { // Run the algorithm for each procedure
        if (AbstractWrapper::GlobalStop) {
            return make_pair(prevList, nextList);
        }
        pair<list<int>, list<int>> allPairsInStmtList = getAllAffects(stmt, affectsRelMap);
        prevList.insert(prevList.end(), allPairsInStmtList.first.begin(), allPairsInStmtList.first.end());
        nextList.insert(nextList.end(), allPairsInStmtList.second.begin(), allPairsInStmtList.second.end());
    }

    cache.putAllAffects(make_pair(prevList, nextList), affectsRelMap);

    return make_pair(prevList, nextList);
}

bool PKBMain::isAffectsStar(int stmt1, int stmt2) {
    if (!cache.containsAllAffectsStar()) { // Check if cache has already precomputed, if not precompute it now
        getAllAffectsStar();
    }

    unordered_map<int, unordered_set<int>> affectsStarRelMap = cache.getAllAffectsStarRelMap();
    if (affectsStarRelMap.find(stmt1) != affectsStarRelMap.end() &&
        affectsStarRelMap[stmt1].find(stmt2) != affectsStarRelMap[stmt1].end()) { // If affects relation exists
        return true;
    }

    return false;
}

list<int> PKBMain::getAffectedStarOf(int stmt1) {
    if (!cache.containsAllAffectsStar()) {
        getAllAffectsStar(); //Precompute if not already cached
    }

    unordered_map<int, list<int>> affectsStarMap = cache.getAffectsStarMap();
    list<int> result;

    if (affectsStarMap.find(stmt1) != affectsStarMap.end()) {
        result = affectsStarMap[stmt1];
    }
    return result;
}

list<int> PKBMain::getAffectorStarOf(int stmt2) {
    if (!cache.containsAllAffectsStar()) {
        getAllAffectsStar();
    }

    unordered_map<int, list<int>> affectsStarMapReverse = cache.getAffectsStarMapReverse();
    list<int> result;

    if (affectsStarMapReverse.find(stmt2) != affectsStarMapReverse.end()) {
        result = affectsStarMapReverse[stmt2];
    }

    return result;
}

list<int> PKBMain::getAllAffectsStarSameSyn() {
    if (cache.containsAllAffectsStarSameSyn()) {
        return cache.getAllAffectsStarSameSyn();
    }

    if (!cache.containsAllAffectsStar()) {
        getAllAffectsStar();
    }

    list<int> result;

    unordered_map<int, unordered_set<int>> affectsStarRelMap = cache.getAllAffectsStarRelMap();

    for (auto &affectsStarRel : affectsStarRelMap) {
        if (affectsStarRel.second.find(affectsStarRel.first) != affectsStarRel.second.end()) {
            result.push_back(affectsStarRel.first);
        }
    }

    cache.putAllAffectsStarSameSyn(result);
    return result;
}

/*
Extract all affects star relations given first statement of each procedure
*/
pair<list<int>, list<int>> PKBMain::getAllAffectsStar() {
    list<int> prevList;
    list<int> nextList;
    unordered_map<int, unordered_set<int>> affectsStarRelMap;
    unordered_map<int, list<int>> affectsStarMap;
    unordered_map<int, list<int>> affectsStarMapReverse;
    if (cache.containsAllAffectsStar()) {
        return cache.getAllAffectsStar();
    }

    list<int> allFirstStmt = getAllFirstStmtOfProc();
    for (int stmt : allFirstStmt) { // Iterate through all procedures and get their affects* relation
        if (AbstractWrapper::GlobalStop) { // In case times out
            return make_pair(prevList, nextList);
        }
        pair<list<int>, list<int>> allPairsInStmtList = getAllAffectsStar(stmt, affectsStarRelMap, affectsStarMap, affectsStarMapReverse);
        prevList.insert(prevList.end(), allPairsInStmtList.first.begin(), allPairsInStmtList.first.end());
        nextList.insert(nextList.end(), allPairsInStmtList.second.begin(), allPairsInStmtList.second.end());
    }

    cache.putAllAffectsStar(make_pair(prevList, nextList), affectsStarRelMap, affectsStarMap, affectsStarMapReverse);

    return make_pair(prevList, nextList);
}

/*
Extracts all affects star relation in the procedure given its first statement
*/
pair<list<int>, list<int>> PKBMain::getAllAffectsStar(int stmt, unordered_map<int, unordered_set<int>> &affectsStarRelMap,
    unordered_map<int, list<int>> &affectsStarMap, unordered_map<int, list<int>> &affectsStarMapReverse) {
    int curr = stmt;
    list<int> prevList;
    list<int> nextList;
    unordered_map<int, unordered_set<int>> latestMod; //varIdx to stmt where it was indirectly/directly modified
    stack<pair<int, unordered_map<int, unordered_set<int>>>> whileMapStack;
    stack<IfStmt> ifMapStack;
    while (curr != 0) {
        if (AbstractWrapper::GlobalStop) { // Check if timeout
            break;
        }
        if (isAssignment(curr)) {
            list<int> usedVarList = getUsesFromStmt(curr);
            int modifiedVar = getModifiesFromStmt(curr).front(); // current modified variable in the statement
            bool existedBefore = (latestMod.find(modifiedVar) != latestMod.end()); // If it exists in the graph before
            if (find(usedVarList.begin(), usedVarList.end(), modifiedVar) == usedVarList.end() && existedBefore) {
                // If it doesn't use itself, we have to clear its latestModifiedMap
                latestMod[modifiedVar].clear();
            }

            // Similar to extraction all affects relations
            // Iterate through all the used variables and get the statements where they were
            // indirectly/directly modified in to populate the affects* relations
            for (int usedVar : usedVarList) {
                if (latestMod.find(usedVar) != latestMod.end()) {
                    unordered_set<int> lastModStmtSet = latestMod[usedVar];
                    for (auto &lastModStmt : lastModStmtSet) {
                        if (!isCall(lastModStmt)) {
                            if ((affectsStarRelMap.find(lastModStmt) != affectsStarRelMap.end() &&
                                affectsStarRelMap[lastModStmt].find(curr) == affectsStarRelMap[lastModStmt].end()) ||
                                affectsStarRelMap.find(lastModStmt) == affectsStarRelMap.end()) {
                                prevList.push_back(lastModStmt);
                                nextList.push_back(curr);
                                affectsStarMap[lastModStmt].push_back(curr);
                                affectsStarMapReverse[curr].push_back(lastModStmt);
                                affectsStarRelMap[lastModStmt].insert(curr);
                                latestMod[modifiedVar].insert(lastModStmt);
                            }
                        }
                    }
                }
            }



            latestMod[modifiedVar].insert(curr);

            list<int> nextStmtList = getExecutedAfter(curr, STMT);

            if (getParent(curr, IF).size() != 0) { // if is a child of if statement (means current if is the top of stack)
                IfStmt ifStmt = ifMapStack.top();
                if (ifStmt.isEndIf(curr)) { //If its the end of an if block
                    curr = processBranchIf(ifMapStack, latestMod);
                }

                else if (ifStmt.isEndElse(curr)) { //If its the end of an else block
                    if (nextStmtList.size() == 0) { // no next after else i.e. pt to dummy
                        curr = processBranchElseWithNoNext(ifMapStack, latestMod);
                    }

                    else { // got next
                        curr = processBranchElseWithNext(ifMapStack, latestMod, nextStmtList.front());
                    }
                }

                else {
                    if (nextStmtList.size() == 0) {
                        curr = 0;
                    }

                    else {
                        curr = nextStmtList.front();
                    }
                }
            }

            else {
                if (nextStmtList.size() == 0) {
                    curr = 0;
                }

                else {
                    curr = nextStmtList.front();
                }
            }
        }

        else if (isCall(curr)) {
            list<int> modifiedVarList = getModifiesFromStmt(curr);
            for (int modifiedVar : modifiedVarList) {
                latestMod.erase(modifiedVar);
            }

            list<int> nextStmtList = getExecutedAfter(curr, STMT);

            if (getParent(curr, IF).size() != 0) { //is in an if
                IfStmt ifStmt = ifMapStack.top();
                if (ifStmt.isEndIf(curr)) {
                    curr = processBranchIf(ifMapStack, latestMod);
                }

                else if (ifStmt.isEndElse(curr)) {
                    if (nextStmtList.size() == 0) { // no next after else i.e. pt to dummy
                        curr = processBranchElseWithNoNext(ifMapStack, latestMod);
                    }

                    else { // got next
                        curr = processBranchElseWithNext(ifMapStack, latestMod, nextStmtList.front());
                    }
                }

                else {
                    if (nextStmtList.size() == 0) {
                        curr = 0;
                    }

                    else {
                        curr = nextStmtList.front();
                    }
                }
            }

            else {
                if (nextStmtList.size() == 0) {
                    curr = 0;
                }

                else {
                    curr = nextStmtList.front();
                }
            }
        }

        else if (isWhile(curr)) {
            list<int> nextStmtList = getExecutedAfter(curr, STMT);
            int insideLoop = nextStmtList.front();
            int afterLoop = 0;

            if (nextStmtList.size() == 2) {
                afterLoop = nextStmtList.back();
            }

            if (whileMapStack.empty() || whileMapStack.top().first != curr) {
                whileMapStack.push(make_pair(curr, latestMod));
                curr = insideLoop;
            }

            else {
                pair<int, unordered_map<int, unordered_set<int>>> oldWhileMap = whileMapStack.top();
                int currWhile = oldWhileMap.first;
                unordered_map<int, unordered_set<int>> oldMod = oldWhileMap.second;
                if (oldMod == latestMod) { // If the maps are the same, means all affects* relations have been captured
                    whileMapStack.pop();
                    // pop and merge
                    while (!whileMapStack.empty() && whileMapStack.top().first == currWhile) {
                        pair<int, unordered_map<int, unordered_set<int>>> prevWhile = whileMapStack.top();
                        whileMapStack.pop();
                        latestMod = joinMap(prevWhile.second, latestMod);
                    }

                    if (ifMapStack.empty()) {
                        curr = afterLoop;
                    }

                    else {
                        if (ifMapStack.top().isEndIf(curr)) {
                            curr = processBranchIf(ifMapStack, latestMod);
                        }

                        else {
                            if (ifMapStack.top().isEndElse(curr)) { //if is end else
                                list<int> nextStmtList = getExecutedAfter(curr, STMT);
                                if (nextStmtList.size() != 0) { //has next
                                    curr = processBranchElseWithNext(ifMapStack, latestMod, afterLoop);
                                }

                                else {
                                    curr = processBranchElseWithNoNext(ifMapStack, latestMod);
                                }
                            }

                            else {
                                curr = afterLoop;
                            }
                        }
                    }

                }

                else {
                    whileMapStack.push(make_pair(curr, latestMod));
                    curr = insideLoop;
                }
            }


        }

        else { // if statement
            list<int> next = getExecutedAfter(curr, STMT);
            next.sort();
            int nextIf = next.front();
            int nextElse = next.back();
            list<int> followsIf = getAfterStar(nextIf, STMT);
            followsIf.sort();
            int endIf;
            if (followsIf.size() == 0) {
                endIf = 0;
            }
            else {
                endIf = followsIf.back();
            }
            if (endIf == 0) {
                endIf = nextIf;
            }
            list<int> children = getChildren(curr, STMT);
            children.sort();
            int endElse = children.back();
            list<int> afterIfList = getAfter(curr, STMT);
            int afterIf;
            if (afterIfList.size() == 0) {
                afterIf = 0;
            }

            else {
                afterIfList.sort();
                afterIf = afterIfList.front();
            }

            bool visitedElse = false;
            IfStmt currIfStmt = IfStmt(curr, nextIf, endIf, nextElse, endElse, visitedElse, afterIf, latestMod, latestMod);
            ifMapStack.push(currIfStmt);
            curr = nextIf;
        }

    }



    return make_pair(prevList, nextList);
}