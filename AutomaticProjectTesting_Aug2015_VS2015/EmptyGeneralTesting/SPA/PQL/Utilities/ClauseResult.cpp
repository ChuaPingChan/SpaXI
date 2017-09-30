#include <cassert>

#include "ClauseResult.h"

using namespace std;

ClauseResult::ClauseResult()
{
    _synToIdxMap = unordered_map<string, int>();
    _synList = vector<string>();
    _result = vector<vector<int>>();
}

vector<string> ClauseResult::getAllSynonyms()
{
    return _synList;
}

/*
Returns the possible results of the all synonyms that satisfy a PQL query.
If a synonym has no possible values that satisfies the query, an empty vector
will be returned.
*/
vector<vector<int>> ClauseResult::getSynonymsResults(vector<string> synNames)
{
    vector<vector<int>> result;

    if (synNames.empty()) {
        result.clear();
        return result;
    }

    for (vector<string>::iterator iter = synNames.begin();
        iter != synNames.end(); iter++) {       // For each synonym selected
        vector<int> synResults = getSynonymResults(*iter);
        result.push_back(synResults);
    }
    return result;
}

/*
Returns the possible results of the given synonym that satisfies a PQL query.
If the synonym has no possible values that satisfies the query, an empty vector
will be given.
*/
vector<int> ClauseResult::getSynonymResults(string synName)
{
    vector<int> result;
    result.clear();     // Most likely redundant. Just to be sure.

    if (_synToIdxMap.count(synName) != 0) {
        int synIdx = _synToIdxMap.at(synName);
        result = _result[synIdx];
    }
    return result;
}

bool ClauseResult::synonymPresent(string synName)
{
    return _synToIdxMap.count(synName) > 0;
}

/*
Adds the results of a new synonym (not present in previous clauses) to all the combinations of existing synonyms.

Pre-conditions:
- Ensure synonym is not an existing synonym. This can be checked using the synonymPresent() method.
- Ensure new synonym has non-empty results.

Note: This method involves computing Catesian product - computationally expensive.
*/
bool ClauseResult::addNewSynResults(string newSynName, vector<int> newSynResults)
{
    if (newSynResults.size() == 0) {
        return true;
    }

    assert(_synToIdxMap.count(newSynName) == 0);    // Must be new synonym
    
    // Add to _synList
    _synList.push_back(newSynName);
    int newSynIdx = _synList.size() - 1;

    // Add to _synToIdxMap
    _synToIdxMap.insert({ newSynName, newSynIdx });

    // Add to _intResult
    int repeatNumber = newSynResults.size() - 1;
    int numCombinations = _result.at(0).size();

    // Catesian product
    for (vector<vector<int>>::iterator iter = _result.begin();
         iter != _result.end();
         iter++) {
        vector<int> initialState = *iter;
        ClauseResult::appendToVector(*iter, initialState, repeatNumber);
    }
    vector<int> modNewSynResults;
    modNewSynResults.clear();
    for (vector<int>::iterator iter = newSynResults.begin();
         iter != newSynResults.end();
         iter++) {
        for (int i = 0; i < numCombinations; i++) {
            modNewSynResults.push_back(*iter);
        }
    }
    _result.push_back(modNewSynResults);

    return true;
}

bool ClauseResult::removeCombinations(string synName, int value)
{
    return false;
}

bool ClauseResult::pairWithOldSyn(string oldSyn, int oldSynValue, string newSyn, vector<int> newSynResults)
{
    return false;
}
