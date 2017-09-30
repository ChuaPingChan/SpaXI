#pragma once
#include <string>

using namespace std;

class PatternClause
{
public:
	PatternClause(int patternType, int argOneType, string argOne, int argTwoType, string argTwo, int argThreeType, string argThree);
	~PatternClause();

	/* Getters */
	int getPatternType();
	int getArgOneType();
	int getArgTwoType();
	int getArgThreeType();
	string getArgOne();
	string getArgTwo();
	string getArgThree();

private:
	int _patternType;
	int _argOneType;
	int _argTwoType;
	int _argThreeType;
	string _argOne;
	string _argTwo;
	string _argThree;
};

