#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <regex>

using namespace std;

class QueryValidator
{
public:
    QueryValidator();
    ~QueryValidator();

    bool isValidQuery(vector<string> inputVector);

    /*--------------- For Unit Testing ---------------*/
    void stubMethod();  //Just a placeholder
    bool isValidDeclarationTest(string str);
    bool isValidEntityTest(string str);
    bool isValidSynonymTest(string str);


private: 
    unordered_set<string> _synonymBank;   //Contains list of used synonyms
    vector<string> _unvalidatedQueryVector;  //Holds unvalidated stmts retreived from query tree

    /*--------------- Validation of Declaration ---------------*/
    bool isValidDeclaration(string str);
    
    bool isValidEntity(string str);
    bool isValidSynonym(string str);

    /*--------------- Validation of Select ---------------*/
    bool isValidSelect(string str);

};

