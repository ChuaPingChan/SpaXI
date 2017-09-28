#pragma once
#include <string>

using namespace std;

class SuchThatClause
{
public:
	SuchThatClause(int rel, int type_one, string arg_one, int type_two, string arg_two);
	~SuchThatClause();

	int getRel();
	int getTypeOne();
	int getTypeTwo();
	string getArgOne();
	string getArgTwo();

private:
	int rel;
	int type_one;
	int type_two;
	string arg_one;
	string arg_two;
};

