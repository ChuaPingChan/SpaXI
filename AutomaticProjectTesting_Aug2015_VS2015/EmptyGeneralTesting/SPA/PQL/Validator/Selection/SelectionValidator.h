#pragma once
#include <string>
#include <regex>        //TODO:Remove after implementing regex teable
#include "..\..\QueryTree.h"    //TODO: Change to properQueryTree
#include "SuchThat\SuchThatHandler.h"

using namespace std;

class SelectionValidator
{
public:
    SelectionValidator(QueryTree *qtPtrNew);
    ~SelectionValidator();

    bool isValidSelection(string str);
    bool setQueryTree(QueryTree *qtPtrNew);

    

private:
    QueryTree *qtPtr;

    //bool isValidSelectBeginning(string str);    //TODO: Make into a class
    bool isValidSelectOverallRegex(string str);     //TODO: Change to a method call to the regex cpp

    bool isSuchThat(string str);
};
