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
#include <string>

using namespace std;

class PKBMain {
public:
	PKBMain();
	//Parser API
	bool setParentChildRel(int parentStmt, int childStmt);

	bool isParentChild(int parentStmt, int childStmt);

	bool isParent(int parentStmt);

	list<int> getChildren(int parentStmt, string type);

	bool isChild(int childStmt);

	bool hasParentRel();

	list<int> getParent(int childStmt, string type);

	list<int> getAllParents(string type);

	list<int> getAllChildren(string type);

	pair<list<int>, list<int>> getAllParentsRel(string type1, string type2);

	pair<list<int>, list<int>> getAllFollows(string type1, string type2);

	bool hasFollows();

	bool setFollowsRel(int stmtBef, int stmtAft);

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

private:
	ChildToParentStarTable childToParentStarTable;
	ChildToParentTable childToParentTable;
	ParentToChildStarTable parentToChildStarTable;
	ParentToChildTable parentToChildTable;
	FollowsTable followsTable;
	FollowsStarAfter followsStarAfter;
	FollowsStarBefore followsStarBefore;
	unordered_map<int, int> followsBeforeMap;
	unordered_map<int, int> followsAfterMap;
};