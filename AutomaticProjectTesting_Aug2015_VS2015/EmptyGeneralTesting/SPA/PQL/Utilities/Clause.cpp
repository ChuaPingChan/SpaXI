#include "Clause.h"

Clause::Clause()
{
}

list<string> Clause::getSynonyms()
{
    return _synonyms;
}

bool Clause::setSynonyms(list<string> synonyms)
{
    _synonyms = synonyms;
    return true;
}

bool Clause::addSynonym(string synonym)
{
    _synonyms.push_back(synonym);
    return true;
}
