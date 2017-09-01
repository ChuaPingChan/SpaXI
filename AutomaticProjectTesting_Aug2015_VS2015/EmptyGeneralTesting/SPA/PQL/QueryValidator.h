#pragma once
#include <string>
#include <vector>
#include <list>
#include <regex>

using namespace std;

class QueryValidator
{
public:
    QueryValidator();
    ~QueryValidator();

    bool isValidQuery();

    //For Testing Private Methods
    bool isValidEntityTest(string input);
    bool isValidSynonymTest(string input);

private: 
    list<string> _synonymNameBank;

    vector<string> getQueryToBeValidated();

    //Validation of Declaration
    bool isValidDeclaration();
    
    bool isValidEnitity(string input);
    bool isValidSynonym(string input);


    //Validation of Select
    bool isValidSelect();
};

