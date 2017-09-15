#pragma once
#include<stdio.h>
#include<string>
#include<vector>
#include<map>
#include<utility>
#include<unordered_map>

using namespace std;

class FollowsTable {
	public:
		FollowsTable();

		//adds follows relation with stmt2 being the statment before and stmt3 being after
		bool addFollows(int stmt1, int stmt2, int stmt3);

		int getStmtBef(int stmt);

		int getStmtAft(int stmt);

		unordered_map<int, pair<int, int>> getMap();

		bool hasBefore(int afterStmt);

		bool hasAfter(int beforeStmt);
	
	private:
		unordered_map<int, pair<int, int>> followsMap;
};