#pragma once
#include <string>

using namespace std;

class DeclarationValidator
{
public:
    DeclarationValidator();
    ~DeclarationValidator();

    bool isValidDeclaration(string str);
};

