#pragma once
#include <string>
#include "../../Entity.h"

using namespace std;

class PatternClause
{
public:
<<<<<<< HEAD
	PatternClause(int patternType, ENTITY argOneType, string argOne, ENTITY argTwoType, string argTwo, ENTITY argThreeType, string argThree);
=======
    PatternClause(int patternType, string patternSyn, int argOneType, string argOne, int argTwoType, string argTwo);                                        //Asssign and While
	PatternClause(int patternType, string patternSyn, int argOneType, string argOne, int argTwoType, string argTwo, int argThreeType, string argThree);    //If
>>>>>>> 928dd00390e3106ff06de11ce5d174abcf1e0e8b
	~PatternClause();

	/* Getters */
	int getPatternType();
<<<<<<< HEAD
	ENTITY getArgOneType();
	ENTITY getArgTwoType();
	ENTITY getArgThreeType();
=======
	int getArgOneType();
	int getArgTwoType();
	int getArgThreeType();
    string getPatternSynonym();
>>>>>>> 928dd00390e3106ff06de11ce5d174abcf1e0e8b
	string getArgOne();
	string getArgTwo();
	string getArgThree();

private:
	int _patternType;
<<<<<<< HEAD
	ENTITY _argOneType;
	ENTITY _argTwoType;
	ENTITY _argThreeType;
=======
	int _argOneType;
	int _argTwoType;
	int _argThreeType;
    string _patternSyn;
>>>>>>> 928dd00390e3106ff06de11ce5d174abcf1e0e8b
	string _argOne;
	string _argTwo;
	string _argThree;
};
