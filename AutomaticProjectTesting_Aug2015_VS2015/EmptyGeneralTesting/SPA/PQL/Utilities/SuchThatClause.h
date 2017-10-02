#pragma once
#include <string>
#include "../../Entity.h"

using namespace std;

class SuchThatClause
{
public:
	SuchThatClause(int rel, ENTITY argOneType, string argOne, ENTITY argTwoType, string argTwo);
	~SuchThatClause();

	/* Getters */
	int getRel();
	ENTITY getArgOneType();
	ENTITY getArgTwoType();
	string getArgOne();
	string getArgTwo();

private:
	int _rel;
	ENTITY _argOneType;
	ENTITY _argTwoType;
	string _argOne;
	string _argTwo;
};

