#pragma once
#include <vector>
#include <string>

using namespace std;

class QueryTree
{
public:
	QueryTree();
	~QueryTree();

	void init();
	void storeUnvalidatedStmts(vector<string> splitted);
	void insertVariable(string type, string var);
	void insertSuchThat(string clause);
	void insertSelect(string stmt);
	void insertPattern(string pattern);
	
	vector<string> getUnvalidatedStmts();
	vector<string> getStmts();
	vector<string> getAssigns();
	vector<string> getWhiles();
	vector<string> getVars();
	vector<string> getConsts();
	vector<string> getProgLines();
	
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
	vector<string> unvalidatedStmts;
	vector<string> stmts;
	vector<string> assigns;
	vector<string> whiles;
	vector<string> vars;
	vector<string> consts;
	vector<string> progLines; 

	string selectStmt;
	string patternStmt;
	vector<string> suchThatClauses;

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

