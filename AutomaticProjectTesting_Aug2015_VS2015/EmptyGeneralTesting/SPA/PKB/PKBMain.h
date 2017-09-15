#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "ChildToParentStarTable.h"
#include "ChildToParentTable.h"
#include "ParentToChildStarTable.h"
#include "ParentToChildTable.h"
#include "FollowsTable.h"
#include "FollowsStarAfter.h"
#include "FollowsStarBefore.h"

using namespace std;

class PKBMain {
public:
	PKBMain();

	bool setParentChildRel(int parentStmt, int childStmt);

	bool setFollowsRel(int stmtBef, int stmtAft);

	bool isFollows(int stmtBef, int stmtAft);

	int getBefore(int currStmt);

	int getAfter(int currStmt);

	int getAfter(int currStmt, string type);

private:
	ChildToParentStarTable childToParentStarTable;
	ChildToParentTable childToParentTable;
	ParentToChildStarTable parentToChildStarTable;
	ParentToChildTable parentToChildTable;
	FollowsTable followsTable;
	unordered_map<int, int> followsBeforeMap;
	unordered_map<int, int> followsAfterMap;
};