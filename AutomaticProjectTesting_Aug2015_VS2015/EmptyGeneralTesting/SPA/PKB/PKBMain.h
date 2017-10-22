#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "ChildToParentStarTable.h"
#include "ChildToParentTable.h"
#include "DesignExtractor.h"
#include "ParentToChildStarTable.h"
#include "ParentToChildTable.h"
#include "FollowsTable.h"
#include "FollowsStarAfter.h"
#include "FollowsStarBefore.h"
#include "ConstantTable.h"
#include "ModTableProcToVar.h"
#include "ModTableStmtToVar.h"
#include "ModTableVar.h"
#include "PatternTable.h"
#include "ProcIdxTable.h"
#include "StmtTypeList.h"
#include "UsesTableProcToVar.h"
#include "UsesTableStmtToVar.h"
#include "UsesTableVar.h"
#include "VarIdxTable.h"
#include "CallsTable.h"
#include "CallsStarTable.h"
#include "NextTable.h"
#include <string>
#include "../Entity.h"

using namespace std;

class PKBMain {
public:
	PKBMain();
    static PKBMain* getInstance();
    static void resetInstance();
    static bool deleteInstance();

	bool isSameName(Entity type1, int idx1, Entity type2, int idx2);

	string convertIdxToString(int index, Entity type);

	list<string> convertIdxToString(list<int> indexList, Entity type);

	int convertStringToIdx(string arg, Entity type);

	list<int> convertStringToIdx(list<string> stringList, Entity type);

	list<int> getAllIntOfIntEntity(Entity type);

	list<int> getAllIdxOfStringEntity(Entity type);

	bool isInstanceOf(Entity type, int arg);

	bool isInstanceOf(Entity type, string arg);

	//Parent
    bool isParentChild(int parentStmt, int childStmt);
    bool isParent(int parentStmt);
    list<int> getChildren(int parentStmt, Entity type);
    bool isChild(int childStmt);
    bool hasParentRel();
    list<int> getParent(int childStmt, Entity type);
    list<int> getAllParents(Entity type);
    list<int> getAllChildren(Entity type);
    pair<list<int>, list<int>> getAllParentsRel(Entity type1, Entity type2);
	bool isParentStarChild(int parentStmt, int childStmt);
	list<int> getChildrenStar(int parentStmt, Entity type);
	list<int> getParentStar(int childStmt, Entity type);
	pair<list<int>, list<int>> getAllParentStarRel(Entity type1, Entity type2);

	//Follows
	pair<list<int>, list<int>> getAllFollows(Entity type1, Entity type2);
    bool hasFollows();
    bool isAfter(int stmtAft);
    bool isBefore(int stmtBef);
    bool isFollows(int stmtBef, int stmtAft);
    int getBefore(int currStmt);
    int getAfter(int currStmt);
    list<int> getAfter(int currStmt, Entity type);
    list<int> getBefore(int currStmt, Entity type);
    list<int> getAllBefore(Entity type);
    list<int> getAllAfter(Entity type);
    bool isFollowsStar(int befStmt, int aftStmt);
    list<int> getAfterStar(int befStmt, Entity type);
    list<int> getBeforeStar(int aftStmt, Entity type);
    list<int> getAllBeforeStar(Entity type);
    list<int> getAllAfterStar(Entity type);
    pair<list<int>, list<int>> getAllFollowsStar(Entity type1, Entity type2);
    bool startProcessComplexRelations();

	bool setNext(int stmt, int stmtNext);

	bool isNext(int stmtBef, int stmtAft);

	bool isExecutedBefore(int stmtBef);

	list<int> getExecutedAfter(int stmtBef, Entity type);
	
	bool isExecutedAfter(int stmtAft);

	bool hasNext();

	list<int> getAllExecutedAfter(Entity type);

	list<int> getExecutedBefore(int stmtAft, Entity type);

	list<int> getAllExecutedBefore(Entity type);

	pair<list<int>, list<int>> getAllNext(Entity type1, Entity type2);

	bool isNextStar(int befStmt, int aftStmt);

	list<int> getExecutedAfterStar(int sbefStmt, Entity type);

	list<int> getExecutedBeforeStar(int aftStmt, Entity type);

	pair<list<int>, list<int>> getAllNextStar(Entity type1, Entity type2);

	//General Purpose API for query evaluator
    bool isPresent(string var);
    bool isPresent(int stmtNum);
	bool isStatement(int stmtNum);
    bool isAssignment(int stmtNum);
	bool isCall(int stmtNum);
	bool isConstant(int constant);
	bool isProgLine(int progLine);
	bool isProcedure(string procName);
	bool isVariable(string varName);
    bool isWhile(int stmtNum);
    bool isIf(int stmtNum);
    list<int> getAllWhiles();
	list<int> getAllConstants();
	list<int> getAllStatements();
    list<int> getAllIfs();

	list<int> getAllCallsStmt();

	list<int> getAllVariables();
    
    //PKB-Parser
	bool setParentChildRel(int parentStmt, int childStmt);
	bool setFollowsRel(int stmtBef, int stmtAft);
	list<string> getAllCalleeNames();
	list<int> getStmtFromCallee(string callee);
	bool setCallsRel(int stmt, string callerProcName, string calleeProcName);
    bool addVariable(string var);
    bool addProcedure(string proc);
    bool addAssignmentStmt(int stmt);
	bool addWhileStmt(int stmt, string controlVar);
	bool addIfStmt(int stmt, string controlVar);
    bool addConstant(int stmt, int constant);
	bool addStmtToProc(int stmt, string procName);
	int getFirstStmtFromProc(int procIdx);
	int getProcFromStmt(int stmt);
	bool isAffects(int stmt1, int stmt2);
	bool isAffector(int stmt1);
	list<int> getAffectedOf(int stmt1);
	bool isAffected(int stmt2);
	bool hasAffects();
	list<int> getAllAffected();
	list<int> getAffectorOf(int stmt2);
	list<int> getAllAffector();
	pair<list<int>, list<int>> getAllAffects();
	bool isAffectsStar(int stmt1, int stmt2);
	list<int> getAffectedStarOf(int stmt1);
	list<int> getAffectorStarOf(int stmt2);
	pair<list<int>, list<int>> getAllAffectsStar();
	list<string> getAllVariableNames();
	list<int> getAllProcedures();
	list<string> getAllProcNames();
	bool setModTableStmtToVar(int stmt, string var);
    bool setModTableProcToVar(string proc, string var);
    bool setUseTableStmtToVar(int stmt, string var);
    bool setUseTableProcToVar(string proc, string var);
    bool setPatternRelation(int stmt, string var, string expression);


	//PKB query (Calls)
	bool isCalls(string callerProcName, string calleeProcName);
	bool isCalls(int callerProcIdx, int calleeProcIdx);
	bool isCaller(string callerProcName);
	list<int> getCallee(string callerProcName);
	list<int> getCallee(int callerProxIdx);
	bool isCallee(string calleeProcName);
	bool hasCalls();

	list<int> getAllCallees();

	list<int> getCaller(string calleeProcName);

	list<int> getCaller(int calleeProcIdx);

	list<int> getAllCallers();

	pair<list<int>, list<int>> getAllCalls();

	bool isCallsStar(string callerProcName, string calleeProcName);

	bool isCallsStar(int callerProcIdx, int calleeProcIdx);

	list<int> getCalleeStar(string callerProcName);

	list<int> getCalleeStar(int callerProcIdx);

	list<int> getCallerStar(string celleeProcName);

	list<int> getCallerStar(int calleeProcIdx);

	pair<list<int>, list<int>> getAllCallsStar();

    //PKB query evaluator (Uses, Modifies)
    bool isUses(int stmt, int varIdx);
	bool isUsesProc(int procIdx, int varIdx);
	bool isUsesProc(string procName, string varName);
	bool isModProc(string procName, string var);
	bool isModProc(int procIdx, int varIdx);
	bool isMod(int stmt, int varIdx);
    bool isUses(int stmt, string var);
    bool isMod(int stmt, string var);
    bool isUsingAnything(int stmt);
	bool isUsingAnythingProc(string procName);
    bool isModifyingAnything(int stmt);
	bool isModifyingAnythingProc(string procName);
    list<int> getUsesFromStmt(int stmt);
	list<int> getUsesFromProc(string procName);
	list<int> getUsesFromProc(int procIdx);
    list<int> getModifiesFromStmt(int stmt);
	list<int> getModifiesFromProc(string procIdx);
	list<int> getModifiesFromProc(int procIdx);
    list<int> getUsesFromVar(string var, Entity type);
	list<int> getUsesFromVar(int varIdx, Entity type);
	list<int> getProcUsesFromVar(string var);
	list<int> getProcUsesFromVar(int varIdx);
	list<int> getModifiesFromVar(string var, Entity type);
	list<int> getModifiesFromVar(int varIdx, Entity type);
	list<int> getProcModifiesFromVar(string var);
	list<int> getProcModifiesFromVar(int varIdx);
	list<int> getStmtThatUsesAnything(Entity type);
	list<int> getProcThatUsesAnything();
	list<int> getProcThatModifiesAnything();
    list<int> getStmtThatModifiesAnything(Entity type);
	list<int> getStmtThatModifiesAnything();
    pair<list<int>, list<int>> getUsesPairs(Entity type);
	pair<list<int>, list<int>> getProcUsesPair();
    pair<list<int>, list<int>> getModifiesPairs(Entity type);

	pair<list<int>, list<int>> getProcModifiesPair();

    //PKB query evaluator (Pattern)
    pair<list<int>, list<int>> getLeftVariables();
	list<int> getWhilesWithControlVariable(string var);
	list<int> getIfsWithControlVariable(string var);
	pair<list<int>, list<int>> getLeftVariablesThatPartialMatchWith(string expression);
	pair<list<int>, list<int>> getLeftVariablesThatExactMatchWith(string expression);
	bool isWhileControlVar(int stmt, int varIdx);
	bool isIfControlVar(int stmt, int varIdx);
	pair<list<int>, list<int>> getControlVariablesInWhile();
	list<int> getControlVariablesInIf(int stmt);
	list<int> getControlVariablesInWhile(int stmt);
	pair<list<int>, list<int>> getControlVariablesInIf();
	list<int> getWhileFromControlVar(int varIdx);
	list<int> getIfFromControlVar(int varIdx);
    list<int> getPartialMatchStmt(string expression);
	list<int> getPartialMatchVar(int stmt, string expression);
	list<int> getExactMatchVar(int stmt, string expression);
    list<int> getPartialBothMatches(string var, string expression);
	list<int> getPartialBothMatches(int varIdx, string expression);
    list<int> getExactMatchStmt(string expression);
    list<int> getExactBothMatches(string var, string expression);
	list<int> getExactBothMatches(int varIdx, string expression);
	bool isExactMatch(int stmt, int varIdx, string expression);
	bool isPartialMatch(int stmt, int varIdx, string expression);
    list<int> getAllAssignments();
    list<int> getAllAssignments(string var);

	list<int> getAllAssignments(int varIdx);

private:
    static PKBMain* singleton;

	ChildToParentStarTable childToParentStarTable;
	ChildToParentTable childToParentTable;
	ParentToChildStarTable parentToChildStarTable;
	ParentToChildTable parentToChildTable;
	FollowsTable followsTable;
	FollowsStarAfter followsStarAfter;
	FollowsStarBefore followsStarBefore;
	unordered_map<int, int> followsBeforeMap;
	unordered_map<int, int> followsAfterMap;
	CallsTable callsTable;
//	CallsStarTable callsStarTable;
	
	ConstantTable constantTable;
    ModTableProcToVar modTableProcToVar;
    ModTableStmtToVar modTableStmtToVar;
    ModTableVar modTableVar;
    PatternTable patternTable;
    ProcIdxTable procIdxTable;
    StmtTypeList stmtTypeList;
    UsesTableProcToVar usesTableProcToVar;
    UsesTableStmtToVar usesTableStmtToVar;
    UsesTableVar usesTableVar;
    VarIdxTable varIdxTable;
	CallsStarTable callsStarTable;
	DesignExtractor de;
	NextTable nextTable;
};