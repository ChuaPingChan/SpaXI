#pragma once
#include <string>

using namespace std;

class SuchThatClause
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

