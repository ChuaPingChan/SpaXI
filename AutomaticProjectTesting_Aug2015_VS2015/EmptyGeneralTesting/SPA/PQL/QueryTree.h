#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <array>

using namespace std;

class QueryTree
{
public:
	QueryTree();
	~QueryTree();

	static QueryTree* getInstance();

	void init();
	void storeUnvalidatedStmts(vector<string> splitted);
	void insertVariable(string type, string var);
	void insertFollows(array<string, 4> arr);
	void insertFollowsStar(array<string, 4> arr);
	void insertParent(array<string, 4> arr);
	void insertParentStar(array<string, 4> arr);
	void insertUses(array<string, 4> arr);
	void insertModifies(array<string, 4> arr);
	void insertPattern(array<string, 6> arr);
	void insertSelect(string stmt);
	
	vector<string> getUnvalidatedStmts();
	vector<string> getStmts();
	vector<string> getAssigns();
	vector<string> getWhiles();
	vector<string> getVars();
	vector<string> getConsts();
	vector<string> getProgLines();

	vector<array<string, 4>> getFollows();
	vector<array<string, 4>> getFollowsStar();
	vector<array<string, 4>> getParent();
	vector<array<string, 4>> getParentStar();
	vector<array<string, 4>> getUses();
	vector<array<string, 4>> getModifies();
	vector<array<string, 6>> getPatterns();
	
	int getNumVar();
	int getNumSuchThat();

	bool isInit();
	bool isSplitted();
	bool isValidated();
	bool isEvaluated();

	void setValidatedTrue();
	void setEvaluatedTrue();

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

	string selectStmt;
	vector<string> suchThatClauses;
	vector<array<string, 4>> followsClauses;
	vector<array<string, 4>> followsStarClauses;
	vector<array<string, 4>> parentClauses;
	vector<array<string, 4>> parentStarClauses;
	vector<array<string, 4>> usesClauses;
	vector<array<string, 4>> modifiesClauses;
	vector<array<string, 6>> patternClauses;

	int numVar = 0;

	bool inited;
	bool splitted;
	bool validated;
	bool evaluated;

	void setInited(bool b);
	void setSplitted(bool b);
	void setValidated(bool b);
	void setEvaluated(bool b);
};

