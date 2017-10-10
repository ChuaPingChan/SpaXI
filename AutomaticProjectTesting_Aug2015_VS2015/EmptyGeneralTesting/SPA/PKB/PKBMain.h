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
#include <string>
#include "../Entity.h"

using namespace std;

class PKBMain {
public:
	PKBMain();
    static PKBMain* getInstance();
    static void resetInstance();

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
	
	//General Purpose API for query evaluator
    bool isPresent(string var);
    bool isPresent(int stmtNum);
    bool isAssignment(int stmtNum);
    bool isWhile(int stmtNum);
    list<int> getAllWhiles();
	list<int> getAllConstants();
	list<int> getAllStatements();

	list<string> getAllVariables();
    
    //PKB-Parser
	bool setParentChildRel(int parentStmt, int childStmt);
	bool setFollowsRel(int stmtBef, int stmtAft);
	bool setCallsRel(int stmt, string callerProcName, string calleeProcName);
    bool addVariable(string var);
    bool addProcedure(string proc);
    bool addAssignmentStmt(int stmt);
    bool addWhileStmt(int stmt);
    bool addConstant(int stmt, int constant);
    bool setModTableStmtToVar(int stmt, string var);
    bool setModTableProcToVar(string proc, string var);
    bool setUseTableStmtToVar(int stmt, string var);
    bool setUseTableProcToVar(string proc, string var);
    bool setPatternRelation(int stmt, string var, string expression);

	//PKB query (Calls)
	bool isCalls(string callerProcName, string calleeProcName);
	bool isCaller(string callerProcName);
	list<int> getCallee(string callerProcName);
	bool isCallee(string calleeProcName);
	bool hasCalls();

	list<int> getAllCallees();

	list<int> getCaller(string calleeProcName);

	list<int> getAllCallers();

	pair<list<int>, list<int>> getAllCalls();

    //PKB query evaluator (Uses, Modifies)
    bool isUses(int stmt, string var);
    bool isMod(int stmt, string var);
	bool isMod(int stmt, int varIdx);
    bool isUsingAnything(int stmt);
    bool isModifyingAnything(int stmt);
    list<string> getUsesFromStmt(int stmt);
    list<string> getModifiesFromStmt(int stmt);
    list<int> getUsesFromVar(string var, Entity type);
    list<int> getModifiesFromVar(string var, Entity type);
    list<int> getStmtThatUsesAnything(Entity type);
    list<int> getStmtThatModifiesAnything(Entity type);
    pair<list<int>, list<string>> getUsesPairs(Entity type);
    pair<list<int>, list<string>> getModifiesPairs(Entity type);

    //PKB query evaluator (Pattern)
    pair<list<int>, list<string>> getLeftVariables();
    pair<list<int>, list<string>> getLeftVariablesThatMatchWith(string expression);
    list<int> getPartialMatchStmt(string expression);
    list<int> getPartialBothMatches(string var, string expression);
    list<int> getExactMatchStmt(string expression);
    list<int> getExactBothMatches(string var, string expression);
    list<int> getAllAssignments();
    list<int> getAllAssignments(string var);

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
};