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
    SelectClause(int selectionType, int singleArgType, string singleArg);
	SelectClause(int selectionType, vector<int> tupleArgTypes, vector<string> tupleArgs);
	~SelectClause();

	/* Getters */
    int getSelectionType();

    int getSingleArgType();
    string getSingleArg();

    vector<int> getTupleArgTypes();
    int getTupleArgTypeAt(int index);
	
    vector<string> getTupleArgs();
    string getTupleArgAt(int index);
	

private:
	int selectionType;
    int singleArgType;
    string singleArg;
	vector<int> tupleArgTypes;
	vector<string> tupleArgs;
};

