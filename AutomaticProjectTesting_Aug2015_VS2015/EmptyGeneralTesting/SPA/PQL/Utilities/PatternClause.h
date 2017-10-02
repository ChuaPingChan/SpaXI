#pragma once
#include <string>
#include "../../Entity.h"

using namespace std;

class PatternClause
{
public:
	PatternClause(int patternType, ENTITY argOneType, string argOne, ENTITY argTwoType, string argTwo, ENTITY argThreeType, string argThree);
	~PatternClause();

	/* Getters */
	int getPatternType();
	ENTITY getArgOneType();
	ENTITY getArgTwoType();
	ENTITY getArgThreeType();
	string getArgOne();
	string getArgTwo();
	string getArgThree();

private:
	int _patternType;
	ENTITY _argOneType;
	ENTITY _argTwoType;
	ENTITY _argThreeType;
	string _argOne;
	string _argTwo;
	string _argThree;
};

