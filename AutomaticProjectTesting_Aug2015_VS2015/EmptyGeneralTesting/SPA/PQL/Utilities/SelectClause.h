#pragma once
#include <string>
#include <vector>
#include <utility>
#include <list>
<<<<<<< HEAD
#include "../../Entity.h"
=======
#include "..\Selectionship.h"
>>>>>>> 928dd00390e3106ff06de11ce5d174abcf1e0e8b

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
<<<<<<< HEAD
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
=======
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
>>>>>>> 928dd00390e3106ff06de11ce5d174abcf1e0e8b
};

