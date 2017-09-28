#include "SuchThatHandler.h"

SuchThatHandler::SuchThatHandler(QueryTreeStub *qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}


SuchThatHandler::~SuchThatHandler()
{
}

bool SuchThatHandler::isValidSuchThat(string str)
{
    SuchThatValidator modifiesValidator = ModifiesValidator(qtPtr);
    SuchThatValidator usesValidator = UsesValidator(qtPtr);

    modifiesValidator.setNextValidator(usesValidator);

    string processedStr = removeAllSpaces(str);



    return false;
}

string SuchThatHandler::removeAllSpaces(string str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}
