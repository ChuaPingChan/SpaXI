#include <cassert>
#include <unordered_set>

#include "ClauseResult.h"

using namespace std;

ClauseResult::ClauseResult()
{
    _synToIdxMap = unordered_map<string, int>();
    _synList = vector<string>();
    _results = vector<vector<int>>();
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
vector<vector<int>> ClauseResult::getSynonymResults(vector<string> synNames)
{
    vector<vector<int>> result;

    if (synNames.empty()) {
        result.clear();
        return result;
    }

    vector<int> synIndices;
    synIndices.clear();
    for (vector<string>::iterator synNamePtr = synNames.begin();
        synNamePtr != synNames.end();
        synNamePtr++) {
        synIndices.push_back(_synToIdxMap.at(*synNamePtr));
    }

    // For each combinations, filter the selected synonyms only.
    for (vector<vector<int>>::iterator combPtr = _results.begin();
        combPtr != _results.end();
        combPtr++) {

        vector<int> filteredCombination;
        filteredCombination.clear();
        
        for (vector<int>::iterator synIndexPtr = synIndices.begin();
            synIndexPtr != synIndices.end();
            synIndexPtr++) {
            filteredCombination.push_back((*combPtr).at(*synIndexPtr));
        }
        result.push_back(filteredCombination);
    }
    return result;
}

vector<vector<int>> ClauseResult::getAllResults()
{
    return _results;
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
    assert(newSynResults.size() > 0);
    assert(_synToIdxMap.count(newSynName) == 0);    // Must be new synonym
    
    // Add to _synList
    _synList.push_back(newSynName);
    int newSynIdx = _synList.size() - 1;

    // Add to _synToIdxMap
    _synToIdxMap.insert({ newSynName, newSynIdx });

    // Update _result - Cartesian product
    if (_results.empty()) {
        for (vector<int>::iterator newSynResPtr = newSynResults.begin();
            newSynResPtr != newSynResults.end();
            newSynResPtr++)
        {
            vector<int> newComb;
            newComb.push_back(*newSynResPtr);
            _results.push_back(newComb);
        }
        return true;
    }

    int repeatNumber = newSynResults.size();
    vector<vector<int>> outdatedResult = _results;
    _results.clear();

    for (vector<vector<int>>::iterator combPtr = outdatedResult.begin();
        combPtr != outdatedResult.end();
        combPtr++)
    {
        for (vector<int>::iterator newSynResPtr = newSynResults.begin();
            newSynResPtr != newSynResults.end();
            newSynResPtr++)
        {
            vector<int> newComb = *combPtr;
            newComb.push_back(*newSynResPtr);
            _results.push_back(newComb);
        }
    }

    return true;
}

bool ClauseResult::addNewSynPairResults(string syn1Name, int syn2Result, vector<vector<int>> pairResults)
{
    return false;
}

bool ClauseResult::addNewSynPairResults(string syn1Name, list<int> syn1Results, string syn2Name, list<int> syn2Results)
{
    return false;
}

/*
bool ClauseResult::overlapExistingSynResults(string synName, vector<int> synResultsToOverlap)
{
    int synIdx = _synToIdxMap.at(synName);
    unordered_set<int> resultsSetToOverlap(synResultsToOverlap.begin(), synResultsToOverlap.end());
    vector<vector<int>> updatedResults = _results;

    for (vector<vector<int>>::iterator combPtr = _results.begin();
        combPtr != _results.end();
        combPtr++)
    {
        int valueInComb = (*combPtr).at(synIdx);
        if (resultsSetToOverlap.count(valueInComb) == 1) {
            updatedResults.push_back(*combPtr);
        }
    }
    _results = updatedResults;
    return true;
}
*/

bool ClauseResult::removeCombinations(string synName, int value)
{
    int synIdx = _synToIdxMap.at(synName);
    vector<vector<int>> updatedResult;
    updatedResult.clear();

    for (vector<vector<int>>::iterator combPtr = _results.begin();
        combPtr != _results.end();
        combPtr++)
    {
        if ((*combPtr).at(synIdx) != value) {
            updatedResult.push_back(*combPtr);
        }
    }
    _results = updatedResult;
    return true;
}

bool ClauseResult::pairWithOldSyn(string oldSyn, int oldSynValue,
                                  string newSyn, vector<int> newSynResults)
{
    assert(newSynResults.size() > 0);
    assert(_synToIdxMap.count(newSyn) == 0);    // Must be new synonym

    int oldSynIdx = _synToIdxMap.at(oldSyn);

    vector<vector<int>> updatedResult;
    updatedResult.clear();

    // Add to _synList
    _synList.push_back(newSyn);
    int newSynIdx = _synList.size() - 1;

    // Add to _synToIdxMap
    _synToIdxMap.insert({ newSyn, newSynIdx });

    // Update _result - Cartesian product
    int repeatNumber = newSynResults.size();

    for (vector<vector<int>>::iterator combPtr = _results.begin();
        combPtr != _results.end();
        combPtr++)
    {
        if ((*combPtr).at(oldSynIdx) == oldSynValue)
        {
            for (vector<int>::iterator newSynResPtr = newSynResults.begin();
                newSynResPtr != newSynResults.end();
                newSynResPtr++)
            {
                vector<int> newComb = *combPtr;
                newComb.push_back(*newSynResPtr);
                updatedResult.push_back(newComb);
            }
        }
    }
    _results = updatedResult;

    return true;
}
