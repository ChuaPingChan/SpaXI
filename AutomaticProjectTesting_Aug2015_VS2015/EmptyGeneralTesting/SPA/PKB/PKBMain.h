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
#include <string>

using namespace std;

class PKBMain {
public:
	PKBMain();
    static PKBMain* getInstance();
    static void resetInstance();

	//Parent
    bool isParentChild(int parentStmt, int childStmt);
    bool isParent(int parentStmt);
    list<int> getChildren(int parentStmt, string type);
    bool isChild(int childStmt);
    bool hasParentRel();
    list<int> getParent(int childStmt, string type);
    list<int> getAllParents(string type);
    list<int> getAllChildren(string type);
    pair<list<int>, list<int>> getAllParentsRel(string type1, string type2);
	bool isParentStarChild(int parentStmt, int childStmt);
	list<int> getChildrenStar(int parentStmt, string type);
	list<int> getParentStar(int childStmt, string type);
	pair<list<int>, list<int>> getAllParentStarRel(string type1, string type2);

	//Follows
	pair<list<int>, list<int>> getAllFollows(string type1, string type2);
    bool hasFollows();
    bool isAfter(int stmtAft);
    bool isBefore(int stmtBef);
    bool isFollows(int stmtBef, int stmtAft);
    int getBefore(int currStmt);
    int getAfter(int currStmt);
    list<int> getAfter(int currStmt, string type);
    list<int> getBefore(int currStmt, string type);
    list<int> getAllBefore(string type);
    list<int> getAllAfter(string type);
    bool isFollowsStar(int befStmt, int aftStmt);
    list<int> getAfterStar(int befStmt, string type);
    list<int> getBeforeStar(int aftStmt, string type);
    list<int> getAllBeforeStar(string type);
    list<int> getAllAfterStar(string type);
    pair<list<int>, list<int>> getAllFollowsStar(string type1, string type2);
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
    bool addVariable(string var);
    bool addProcedure(string proc);
    bool addAssignmentStmt(int stmt);
    bool addWhileStmt(int stmt);
	bool addCallStmt(int stmt, string proc);
    bool addConstant(int stmt, int constant);
    bool setModTableStmtToVar(int stmt, string var);
    bool setModTableProcToVar(string proc, string var);
    bool setUseTableStmtToVar(int stmt, string var);
    bool setUseTableProcToVar(string proc, string var);
    bool setPatternRelation(int stmt, string var, string expression);

    //PKB query evaluator (Uses, Modifies)
    bool isUses(int stmt, string var);
    bool isMod(int stmt, string var);
    bool isUsingAnything(int stmt);
    bool isModifyingAnything(int stmt);
    list<string> getUsesFromStmt(int stmt);
    list<string> getModifiesFromStmt(int stmt);
    list<int> getUsesFromVar(string var, string type);
    list<int> getModifiesFromVar(string var, string type);
    list<int> getStmtThatUsesAnything(string type);
    list<int> getStmtThatModifiesAnything(string type);
    pair<list<int>, list<string>> getUsesPairs(string type);
    pair<list<int>, list<string>> getModifiesPairs(string type);

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