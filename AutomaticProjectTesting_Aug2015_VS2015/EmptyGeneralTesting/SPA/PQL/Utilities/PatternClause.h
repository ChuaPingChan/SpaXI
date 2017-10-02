#pragma once
#include <string>

using namespace std;

class PatternClause
{
public:
    PatternClause(int patternType, string patternSyn, int argOneType, string argOne, int argTwoType, string argTwo);                                        //Asssign and While
	PatternClause(int patternType, string patternSyn, int argOneType, string argOne, int argTwoType, string argTwo, int argThreeType, string argThree);    //If
	~PatternClause();

	/* Getters */
	int getPatternType();
	int getArgOneType();
	int getArgTwoType();
	int getArgThreeType();
    string getPatternSynonym();
	string getArgOne();
	string getArgTwo();
	string getArgThree();

private:
	int _patternType;
	int _argOneType;
	int _argTwoType;
	int _argThreeType;
    string _patternSyn;
	string _argOne;
	string _argTwo;
	string _argThree;
};
