#pragma once

#include <string>
#include <list>
#include <memory>

using namespace std;

/*
    This is a superclass for all clauses.
*/
class Clause
{
public:

    enum ClauseType
    {
        SELECT = 1,
        SUCH_THAT = 2,
        PATTERN = 3,
        WITH = 4
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

typedef shared_ptr<Clause> ClausePtr;
