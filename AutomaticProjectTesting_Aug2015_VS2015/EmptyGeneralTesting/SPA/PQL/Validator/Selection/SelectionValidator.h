#pragma once
#include <string>

using namespace std;

class SelectionValidator
{
public:
    SelectionValidator();
    ~SelectionValidator();

    bool isValidSelection(string str);
};

