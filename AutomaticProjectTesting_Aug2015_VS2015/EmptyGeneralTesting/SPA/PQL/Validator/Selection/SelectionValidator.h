#pragma once
#include <string>
#include "..\..\QueryTreeStub.h"

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
};
