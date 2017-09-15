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

	bool startProcessComplexRelations();

private:
	ChildToParentStarTable childToParentStarTable;
	ChildToParentTable childToParentTable;
	ParentToChildStarTable parentToChildStarTable;
	ParentToChildTable parentToChildTable;
	FollowsTable followsTable;
	unordered_map<int, int> followsBeforeMap;
	unordered_map<int, int> followsAfterMap;
};