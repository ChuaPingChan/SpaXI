#pragma once
#include <string>
#include <vector>
#include <utility>
#include <list>
#include "..\Selectionship.h"

using namespace std;

class SelectClause
{
public:
	SelectClause();
	SelectClause(int selectionType);
	SelectClause(int selectionType, vector<int> argTypes, vector<string> args);
	~SelectClause();

	/* Getters */
    int getSelectionType();
    int getArgTypeAt(int index);
	vector<int> getArgTypes();
	string getArgAt(int index);
	vector<string> getArgs();

private:
	int selectionType;
	vector<int> argTypes;
	vector<string> args;
};

