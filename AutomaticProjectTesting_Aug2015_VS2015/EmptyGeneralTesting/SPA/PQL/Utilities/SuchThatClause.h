#pragma once
#include <string>
#include "ClauseObject.h"

using namespace std;

class SuchThatClause : public ClauseObject
{
public:
	SuchThatClause(int rel, int argOneType, string argOne, int argTwoType, string argTwo);
	~SuchThatClause();

	/* Getters */
	int getRel();
	int getArgOneType();
	int getArgTwoType();
	string getArgOne();
	string getArgTwo();

private:
	int _rel;
	int _argOneType;
	int _argTwoType;
	string _argOne;
	string _argTwo;
};

