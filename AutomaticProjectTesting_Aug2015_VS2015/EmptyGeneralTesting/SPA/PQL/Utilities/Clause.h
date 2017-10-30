#pragma once

#include <string>
#include <list>

using namespace std;

class Clause
{
public:

    enum ClauseType
    {
        SELECT = 0,
        SUCH_THAT = 1,
        PATTERN = 2,
        WITH = 3
    };

    Clause(ClauseType clauseType);

    list<string> getSynonyms();
    bool setSynonyms(list<string> synonyms);
    bool addSynonym(string synonym);
    ClauseType getClauseType();


private:

    list<string> _synonyms;
    ClauseType _clauseType;

};

