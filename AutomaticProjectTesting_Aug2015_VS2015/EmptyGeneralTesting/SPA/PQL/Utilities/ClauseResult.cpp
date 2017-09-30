#include <cassert>

#include "ClauseResult.h"

using namespace std;

ClauseResult::ClauseResult()
{
    _synToIdxMap = unordered_map<string, int>();
    _synList = vector<string>();
    _intResult = vector<vector<int>>();
    _strResult = vector<vector<string>>();
}

vector<string> ClauseResult::getAllSynonyms()
{
    return _synList;
}

/*
Get the possible results of the given synonym that satisfies a PQL query.
If synonym has no possible values that satisfies the query, an empty vector
will be given.
*/
void ClauseResult::getSynonymResults(string synName, vector<string> &results)
{
    results.clear();

    if (_synToIdxMap.count(synName) == 0) {
        return;
    }

    int synIdx = _synToIdxMap.at(synName);
    results = _strResult[synIdx];
}

/*
Get the possible results of the given synonym that satisfies a PQL query.
If synonym has no possible values that satisfies the query, an empty vector
will be given.
*/
void ClauseResult::getSynonymResults(string synName, vector<int> &results)
{
    results.clear();

    if (_synToIdxMap.count(synName) == 0) {
        return;
    }

    int synIdx = _synToIdxMap.at(synName);
    results = _intResult[synIdx];
}

bool ClauseResult::synonymPresent(string synName)
{
    return _synToIdxMap.count(synName) > 0;
}

/*
Adds the results of a new synonym (not present in previous clauses) to all the combinations of existing synonyms.
Pre-condition: Ensure synonym is not an existing synonym. This can be checked using the synonymPresent() method.
Note: This method involves computing Catesian product - computationally expensive.
*/
bool ClauseResult::addNewSynResults(string newSynName, vector<int> newSynResults)
{
    assert(_synToIdxMap.count(newSynName) == 0);

    int repeatNumber = newSynResults.size() - 1;

    // For each synonyms with integer results
    for (vector<vector<int>>::iterator iter = _intResult.begin();
        iter != _intResult.end(); iter++) {
        vector<int> initialState = *iter;
        ClauseResult::appendToVector(*iter, initialState, repeatNumber);
    }
    // For each synonyms with string results (e.g. procedure, variable)
    for (vector<vector<string>>::iterator iter = _strResult.begin();
        iter != _strResult.end(); iter++) {
        vector<string> initialState = *iter;
        ClauseResult::appendToVector(*iter, initialState, repeatNumber);
    }

    return false;
}

bool ClauseResult::removeCombinations(string synName, int value)
{
    return false;
}

bool ClauseResult::removeCombinations(string synName, string value)
{
    return false;
}

bool ClauseResult::pairWithOldSyn(string oldSyn, string oldSynValue, string newSyn, vector<string> newSynResults)
{
    return false;
}

bool ClauseResult::pairWithOldSyn(string oldSyn, int oldSynValue, string newSyn, vector<int> newSynResults)
{
    return false;
}
