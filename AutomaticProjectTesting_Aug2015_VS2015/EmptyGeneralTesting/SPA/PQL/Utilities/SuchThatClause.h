#pragma once
#include <string>

using namespace std;

class SuchThatClause
{
public:
	SuchThatClause(int rel, int argOneType, string argOne, int argTwoType, string argTwo);
	~SuchThatClause();

	int getRel();
	int getTypeOne();
	int getTypeTwo();
	string getArgOne();
	string getArgTwo();

private:
	int rel;
	int _argOneType;
	int _argTwoType;
	string _argOne;
	string _argTwo;
};

