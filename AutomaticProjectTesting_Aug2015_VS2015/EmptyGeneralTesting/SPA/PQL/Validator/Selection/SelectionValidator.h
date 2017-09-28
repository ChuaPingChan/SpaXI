#pragma once
#include <string>
#include <regex>        //TODO:Remove after implementing regex teable
#include "..\..\QueryTreeStub.h"    //TODO: Change to properQueryTree
#include "SuchThat\SuchThatHandler.h"

using namespace std;

class SelectionValidator
{
public:
    SelectionValidator(QueryTreeStub *qtPtrNew);
    ~SelectionValidator();

    bool isValidSelection(string str);
    bool setQueryTreeStub(QueryTreeStub *qtPtrNew);

    

private:
    QueryTreeStub *qtPtr;

    //bool isValidSelectBeginning(string str);    //TODO: Make into a class
    bool isValidSelectOverallRegex(string str);     //TODO: Change to a method call to the regex cpp

    bool isSuchThat(string str);
};
