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
	int getSelectionType();
	int getSelectionType(int index);
	vector<int> getSelectionTypes();
	string getSelectionArg();
	string getSelectionArg(int index);
	vector<string> getSelectionArgs();

private:
	bool tuple;
	int selectionType;
	string selectionArg;
	vector<int> selectionTypes;
	vector<string> selectionArgs;
};

