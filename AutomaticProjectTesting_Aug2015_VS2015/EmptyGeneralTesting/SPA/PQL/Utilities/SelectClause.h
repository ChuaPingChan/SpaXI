#pragma once
#include <string>
#include <vector>
#include <utility>
#include <list>

using namespace std;

class SelectClause
{
public:
	SelectClause();
	SelectClause(int type, string arg);
	SelectClause(vector<int> types, vector<string> args);
	~SelectClause();

	/* Getters */
	bool isTuple();
	int getType();
	int getType(int index);
	vector<int> getTypes();
	string getArg();
	string getArg(int index);
	vector<string> getArgs();

private:
	bool tuple;
	int type;
	string arg;
	vector<int> types;
	vector<string> args;
};

