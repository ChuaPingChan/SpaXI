#pragma once
#include <string>

using namespace std;

class PatternClause
{
public:
	PatternClause(int type, int type_one, string arg_one, int type_two, string arg_two, int type_three, string arg_three);
	~PatternClause();

	/* Getters */
	int getType();
	int getTypeOne();
	int getTypeTwo();
	int getTypeThree();
	string getArgOne();
	string getArgTwo();
	string getArgThree();

private:
	int type;
	int type_one;
	int type_two;
	int type_three;
	string arg_one;
	string arg_two;
	string arg_three;
};

