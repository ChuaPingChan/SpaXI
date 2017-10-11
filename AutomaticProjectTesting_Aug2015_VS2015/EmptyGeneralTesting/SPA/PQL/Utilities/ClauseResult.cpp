#include <cassert>
#include <unordered_set>
#include <set>

#include "ClauseResult.h"

using namespace std;

ClauseResult::ClauseResult()
{
    _synToIdxMap = unordered_map<string, int>();
    _synList = vector<string>();
    _results = list<vector<int>>();
}

list<string> ClauseResult::getAllSynonyms()
{
    return ClauseResult::convertVectorToList(_synList);
}

/*
Returns the possible results of the all synonyms that satisfy a PQL query
in the same order.
The inner list returned represents a combination of the synonyms given. For example,
if the synonyms 'a', 'b' and 'c' are given as parameters, an inner list of {2, 3, 4}
means {a=2, b=3, c=4}.
*/
list<list<int>> ClauseResult::getSynonymResults(list<string> synNames)
{
    list<list<int>> result;

    if (synNames.empty()) {
        result.clear();
        return result;
    }

    list<int> synIndices;
    synIndices.clear();
    for (list<string>::iterator synNamePtr = synNames.begin();
        synNamePtr != synNames.end();
        synNamePtr++) {
        synIndices.push_back(_synToIdxMap.at(*synNamePtr));
    }

    // For each combinations, filter the selected synonyms only.
    for (list<vector<int>>::iterator combPtr = _results.begin();
        combPtr != _results.end();
        combPtr++) {

        list<int> selectedSynCombination;
        selectedSynCombination.clear();
        
        for (list<int>::iterator synIndexPtr = synIndices.begin();
            synIndexPtr != synIndices.end();
            synIndexPtr++)
        {
            selectedSynCombination.push_back((*combPtr).at(*synIndexPtr));
        }
        result.push_back(selectedSynCombination);
    }

    result = ClauseResult::getUniqueListElements(result);
    return result;
}

/*
Returns the possible results of the synonyms that satisfy a PQL query.
If a synonym has no possible values that satisfies the query, 
an empty list will be returned.
*/
list<int> ClauseResult::getSynonymResults(string synName)
{
    list<string> synNameVec;
    synNameVec.clear();
    synNameVec.push_back(synName);

    list<list<int>> result = getSynonymResults(synNameVec);
    assert(result.size() == 1);

    return *(result.begin());
}

list<pair<int, int>> ClauseResult::getSynonymPairResults(string syn1Name, string syn2Name)
{
    /*
    This method is a wrapper over the more more general getSynonymResults which
    takes in a list of synonym names.
    */
    list<string> synNameList;
    synNameList.clear();
    synNameList.push_back(syn1Name);
    synNameList.push_back(syn2Name);

    list<list<int>> synPairResultList = getSynonymResults(synNameList);

    list<pair<int, int>> synPairResult;
    synPairResult.clear();
    // Convert inner lists to pairs
    // TODO: Can consider refactoring, but not for now, not reused by others.
    for (list<list<int>>::iterator synPairResultInnerListPtr = synPairResultList.begin();
        synPairResultInnerListPtr != synPairResultList.end();
        synPairResultInnerListPtr++)
    {
        assert((*synPairResultInnerListPtr).size() == 2);

        int first = (*synPairResultInnerListPtr).front();
        (*synPairResultInnerListPtr).pop_front();
        int second = (*synPairResultInnerListPtr).front();

        pair<int, int> pairResult(first, second);
        synPairResult.push_back(pairResult);
    }

    return synPairResult;
}

list<list<int>> ClauseResult::getAllResults()
{
    return ClauseResult::convertListOfVectorsToListOfLists(_results);
}

bool ClauseResult::synonymPresent(string synName)
{
    return _synToIdxMap.count(synName) > 0;
}

/*
Updates the result of a new or an existing synonym.
Pre-condition: Ensure new synonym has non-empty results.
Note: This may method involve computing Catesian product - computationally expensive.
*/
bool ClauseResult::updateSynResults(string newSynName, list<int> newSynResultsList)
{
    assert(newSynResultsList.size() > 0);       // TODO: Can consider clearing everything if this happens
    if (_synToIdxMap.count(newSynName) == 1)
    {
        return overlapExistingSynResults(newSynName, newSynResultsList);
    }

    vector<int> newSynResults = convertListToVector(newSynResultsList);
    
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
    list<vector<int>> outdatedResult = _results;
    _results.clear();

    for (list<vector<int>>::iterator combPtr = outdatedResult.begin();
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

bool ClauseResult::addNewSynPairResults(string syn1Name, string syn2Name, list<vector<int>> pairResults)
{
    assert(pairResults.size() > 0);
    assert(_synToIdxMap.count(syn1Name) == 0);    // syn1 must be new synonym
    assert(_synToIdxMap.count(syn2Name) == 0);    // syn2 must be new synonym

    // Add to _synList
    _synList.push_back(syn1Name);
    int syn1Idx = _synList.size() - 1;
    _synList.push_back(syn2Name);
    int syn2Idx = _synList.size() - 1;

    // Add to _synToIdxMap
    _synToIdxMap.insert({ syn1Name, syn1Idx });
    _synToIdxMap.insert({ syn2Name, syn2Idx });

    // Update _result - Cartesian product
    if (_results.empty()) {
        for (list<vector<int>>::iterator pairResultPtr = pairResults.begin();
            pairResultPtr != pairResults.end();
            pairResultPtr++)
        {
            _results.push_back(*pairResultPtr);
        }
        return true;
    }

    int repeatNumber = pairResults.size();
    list<vector<int>> outdatedResult = _results;
    _results.clear();

    for (list<vector<int>>::iterator combPtr = outdatedResult.begin();
        combPtr != outdatedResult.end();
        combPtr++)
    {
        for (list<vector<int>>::iterator pairResultPtr = pairResults.begin();
            pairResultPtr != pairResults.end();
            pairResultPtr++)
        {
            vector<int> newComb = *combPtr;
            *combPtr = ClauseResult::joinTwoVectors(*combPtr, *pairResultPtr);
            _results.push_back(newComb);
        }
    }

    return true;
}

bool ClauseResult::addNewSynPairResults(string syn1Name, list<int> syn1Results, string syn2Name, list<int> syn2Results)
{
    list<vector<int>> pairResults = ClauseResult::convertTwoListsToListOfPairResultVector(syn1Results, syn2Results);
    return addNewSynPairResults(syn1Name, syn2Name, pairResults);
}

/*
Helper method:
Converts two lists of results of two synonyms into a list of results pair. Each result pair
is stored as a vector with 2 elements.

Pre-condition: The two lists given should be of the same length and each element of a list
should form a pair of valid result with the element with the same order in the other list.
*/
list<vector<int>> ClauseResult::convertTwoListsToListOfPairResultVector(list<int>& syn1Results, list<int>& syn2Results)
{
    list<vector<int>> pairResults;
    pairResults.clear();

    for (list<int>::iterator syn1ResultPtr = syn1Results.begin();
        syn1ResultPtr != syn1Results.end();
        syn1ResultPtr++) {
        for (list<int>::iterator syn2ResultPtr = syn2Results.begin();
            syn2ResultPtr != syn2Results.end();
            syn2ResultPtr++) {
            vector<int> pairResult;
            pairResult.clear();
            pairResult.push_back(*syn1ResultPtr);
            pairResult.push_back(*syn2ResultPtr);
        }
    }
    return pairResults;
}

bool ClauseResult::overlapExistingSynResults(string synName, list<int> synResultsToOverlap)
{
    assert(synonymPresent(synName));

    int synIdx = _synToIdxMap.at(synName);
    unordered_set<int> resultsSetToOverlap(synResultsToOverlap.begin(), synResultsToOverlap.end());
    
    list<vector<int>> updatedResults;   // to overwrite _results at the end of this method

    for (list<vector<int>>::iterator combPtr = _results.begin();
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

bool ClauseResult::removeCombinations(string synName, int value)
{
    /*
    Note:
    There's no need to remove anything from _synList and _synToIdxMap
    because once a synonym is introduced into the intermetiate result,
    it MUST always have at least 1 possible result.
    */

    int synIdx = _synToIdxMap.at(synName);
    
    list<vector<int>> updatedResult;    // To be assigned to _results at the end of this method
    updatedResult.clear();
    for (list<vector<int>>::iterator combPtr = _results.begin();
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

bool ClauseResult::removeCombinations(string syn1Name, int syn1Value, string syn2Name, int syn2Value)
{
    return removeCombinations(syn1Name, syn1Value) && removeCombinations(syn2Name, syn2Value);
}

/*
Merges the results of a new synonym to that of an existing synonym.
*/
bool ClauseResult::pairWithOldSyn(string oldSyn, string newSyn, list<pair<int, int>> resultPairs)
{
    assert(ClauseResult::synonymPresent(oldSyn));
    assert(!(ClauseResult::synonymPresent(newSyn)));

    // Add to _synList and _synToIdxMap
    _synList.push_back(newSyn);
    int newSynIdx = _synList.size() - 1;
    assert(_synToIdxMap.count(newSyn) == 0);
    _synToIdxMap.insert({ newSyn, newSynIdx });

    // Create hash map to hasten merging with existing results
    unordered_map<int, vector<int>> oldSynValToNewSynResultMap;
    oldSynValToNewSynResultMap.clear();

    // Populate oldSynValToNewSynResultMap
    for (pair<int, int> resultPair : resultPairs)
    {   // Convert pair to vector so that it can be appended to existing vector easily
        oldSynValToNewSynResultMap[resultPair.first].push_back(resultPair.second);
    }

    // Merging with existing combinations
    int oldSynIdx = _synToIdxMap.at(oldSyn);
    list<vector<int>> updatedResults;
    updatedResults.clear();
    for (vector<int> existingCombination : _results)
    {
        const int oldSynVal = existingCombination[oldSynIdx];
        // TODO: Consider refactoring to avoid arrowhead code.
        if (oldSynValToNewSynResultMap.count(oldSynVal) == 1)
        {
            vector<int> newSynResults = oldSynValToNewSynResultMap.at(oldSynVal);
            for (int newSynResult : newSynResults)
            {
                vector<int> newComb = existingCombination;
                newComb.push_back(newSynResult);
                updatedResults.push_back(newComb);
            }
        }
    }
    _results = updatedResults;

    return true;
}

bool ClauseResult::hasResults()
{
    return _results.empty();
}
