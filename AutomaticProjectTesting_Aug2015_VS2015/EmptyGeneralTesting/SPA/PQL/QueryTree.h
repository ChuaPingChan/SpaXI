#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <list>

using namespace std;

class QueryTree
{
public:
	QueryTree();
	~QueryTree();

	static QueryTree* getInstance();

	void init();
	void storeUnvalidatedStmts(vector<string> splitted);
	void insertSelect(array<string, 2> arr);
	void insertVariable(string type, string var);
	void insertFollows(array<string, 4> arr);
	void insertFollowsStar(array<string, 4> arr);
	void insertParent(array<string, 4> arr);
	void insertParentStar(array<string, 4> arr);
	void insertUses(array<string, 4> arr);
	void insertModifies(array<string, 4> arr);
	void insertPattern(array<string, 6> arr);
	
	vector<string> getUnvalidatedStmts();
	vector<string> getStmts();
	vector<string> getAssigns();
	vector<string> getWhiles();
	vector<string> getVars();
	vector<string> getConsts();
	vector<string> getProgLines();

	array<string, 2> getSelect();
	vector<array<string, 4>> getFollows();
	vector<array<string, 4>> getFollowsT();
	vector<array<string, 4>> getParent();
	vector<array<string, 4>> getParentT();
	vector<array<string, 4>> getUses();
	vector<array<string, 4>> getModifies();
	vector<array<string, 6>> getPatterns();

	bool varExists(string var);

private:

	static QueryTree* instance;

	vector<string> unvalidatedStmts;
	vector<string> stmts;
	vector<string> assigns;
	vector<string> whiles;
	vector<string> vars;
	vector<string> consts;
	vector<string> progLines; 

	array<string, 2> selectStmt;
	vector<string> suchThatClauses;
	vector<array<string, 4>> followsClauses;
	vector<array<string, 4>> followsStarClauses;
	vector<array<string, 4>> parentClauses;
	vector<array<string, 4>> parentStarClauses;
	vector<array<string, 4>> usesClauses;
	vector<array<string, 4>> modifiesClauses;
	vector<array<string, 6>> patternClauses;

	list<string> finalResult;
};

