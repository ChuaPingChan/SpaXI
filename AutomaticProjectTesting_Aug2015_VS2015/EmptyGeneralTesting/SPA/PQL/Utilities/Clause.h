#pragma once

#include <string>
#include <list>

using namespace std;

/*
    This is a superclass for all clauses.
*/
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

    virtual list<string> getSynonyms();
    virtual ClauseType getClauseType();

    // API for optimizer
    bool setSynonyms(list<string> synonyms);
    bool addSynonym(string synonym);

protected:

    list<string> _synonyms;
    ClauseType _clauseType;

};

