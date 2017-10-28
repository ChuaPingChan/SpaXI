#pragma once

#include <string>
#include <list>

using namespace std;

class Clause
{
public:
    Clause();

    list<string> getSynonyms();
    bool setSynonyms(list<string> synonyms);
    bool addSynonym(string synonym);

private:

    list<string> _synonyms;

};

