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
    _isNew = true;
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

Pre-condition: The list of synonym names given cannot be empty.
*/
list<list<int>> ClauseResult::getSynonymResults(list<string> synNames)
{
    assert(!(synNames.empty()));
    list<list<int>> result;

    list<int> synIndices;
    synIndices.clear();
    for (string synName : synNames) {
        synIndices.push_back(_synToIdxMap.at(synName));
    }

    // For each combinations, filter the selected synonyms only.
    for (vector<int> existingComb : _results) {
        list<int> selectedSynCombinations;
        selectedSynCombinations.clear();

        for (int synIndex : synIndices)
        {
            selectedSynCombinations.push_back(existingComb.at(synIndex));
        }
        result.push_back(selectedSynCombinations);
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
    // Construct a list with only one synonym name
    list<string> synNameVec;
    synNameVec.clear();
    synNameVec.push_back(synName);

    list<list<int>> resultVerticalList = getSynonymResults(synNameVec);

    // Put resutls into a single list for the convenience of evaluators
    list<int> resultHorizontalList;
    resultHorizontalList.clear();
    for (list<int> oneResult : resultVerticalList)
    {
        assert(oneResult.size() == 1);
        resultHorizontalList.push_back(oneResult.front());
    }

    return resultHorizontalList;
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

    _isNew = false;
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

bool ClauseResult::mergeClauseResult(ClauseResult clauseResultToMerge, unordered_set<string> selectedSyns)
{
    // Get all selected synonyms in the other clause result
    list<string> synsInClauseResult = clauseResultToMerge.getAllSynonyms();
    list<string> synsToMerge;
    for (string synName : synsInClauseResult) {
        if (selectedSyns.find(synName) != selectedSyns.end())
            synsToMerge.push_back(synName);
    }
    // Get the results of only the synonyms to merge and remove duplicates
    list<list<int>> resultsToMerge = clauseResultToMerge.getSynonymResults(synsToMerge);
    resultsToMerge.unique();

    for (string newSynName : synsToMerge)
    {
        assert(_synToIdxMap.find(newSynName) == _synToIdxMap.end());

        // Add to _synList
        _synList.push_back(newSynName);
        int newSynIdx = _synList.size() - 1;

        // Add to _synToIdxMap
        _synToIdxMap.insert({ newSynName, newSynIdx });
    }

    // Merge with _result - Cartesian product
    if (_results.empty()) {
        for (list<int> newComb : resultsToMerge) {
            vector<int> newCombToMerge = convertListToVector(newComb);
            _results.push_back(newCombToMerge);
        }
        return true;
    }

    int repeatNumber = resultsToMerge.size();
    list<vector<int>> outdatedResult = _results;
    _results.clear();

    for (vector<int> currComb : outdatedResult) {
        for (list<int> newSynsResList : resultsToMerge) {
            vector<int> newSynsResVec = convertListToVector(newSynsResList);
            vector<int> newComb = joinTwoVectors(currComb, newSynsResVec);
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

    _isNew = false;

    // Add to _synList and _synToIdxMap
    _synList.push_back(syn1Name);
    int syn1Idx = _synList.size() - 1;
    _synList.push_back(syn2Name);
    int syn2Idx = _synList.size() - 1;
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

    list<vector<int>> updatedResults;
    updatedResults.clear();

    for (vector<int> existingComb : _results)
    {
        for (vector<int> pairResult : pairResults)
        {
            vector<int> newComb = existingComb;
            newComb = ClauseResult::joinTwoVectors(newComb, pairResult);
            updatedResults.push_back(newComb);
        }
    }
    _results = updatedResults;

    return true;
}

bool ClauseResult::addNewSynPairResults(string syn1Name, list<int> syn1Results, string syn2Name, list<int> syn2Results)
{
    list<vector<int>> pairResults = ClauseResult::pairUpListsResults(syn1Results, syn2Results);
    return addNewSynPairResults(syn1Name, syn2Name, pairResults);
}

/*
Helper method:
Converts two lists of results of two synonyms into a list of results pair. Each result pair
is stored as a vector with 2 elements.

Pre-condition: The two lists given should be of the same length and each element of a list
should form a pair of valid result with the element with the same order in the other list.
*/
list<vector<int>> ClauseResult::pairUpListsResults(list<int>& syn1Results, list<int>& syn2Results)
{
    assert(syn1Results.size() == syn2Results.size());

    list<vector<int>> pairResults;
    pairResults.clear();

    // Simulate zip iterator
    list<int>::iterator iter1 = syn1Results.begin();
    list<int>::iterator iter2 = syn2Results.begin();
    for (; iter1 != syn1Results.end() && iter2 != syn2Results.end(); iter1++, iter2++) {
        vector<int> pairResult;
        pairResult.clear();
        pairResult.push_back(*iter1);
        pairResult.push_back(*iter2);
        pairResults.push_back(pairResult);
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

    assert(ClauseResult::synonymPresent(synName));

    int synIdx = _synToIdxMap.at(synName);
    list<vector<int>>::iterator existingResultsIter = _results.begin();
    while (existingResultsIter != _results.end())
    {
        if ((*existingResultsIter).at(synIdx) == value)
            existingResultsIter = _results.erase(existingResultsIter);
        else
            existingResultsIter++;
    }

    /*
    list<vector<int>> updatedResult;    // To be assigned to _results at the end of this method
    updatedResult.clear();

    for (vector<int> existingComb : _results)
    {
        if (existingComb.at(synIdx) != value)
            updatedResult.push_back(existingComb);
    }
    _results = updatedResult;
    */
    return true;
}

bool ClauseResult::removeCombinations(string syn1Name, int syn1Value, string syn2Name, int syn2Value)
{
    assert(ClauseResult::synonymPresent(syn1Name));
    assert(ClauseResult::synonymPresent(syn2Name));

    if (syn1Name == syn2Name) {
        assert(syn1Value == syn2Value);
        return removeCombinations(syn1Name, syn1Value);
    }

    int syn1Idx = _synToIdxMap.at(syn1Name);
    int syn2Idx = _synToIdxMap.at(syn2Name);
    list<vector<int>>::iterator existingResultsIter = _results.begin();
    while (existingResultsIter != _results.end())
    {
        if (((*existingResultsIter).at(syn1Idx) == syn1Value) && ((*existingResultsIter).at(syn2Idx) == syn2Value))
            existingResultsIter = _results.erase(existingResultsIter);
        else
            existingResultsIter++;
    }
    return true;
}

/*
Merges the results of a new synonym to that of an existing synonym.
*/
bool ClauseResult::pairWithOldSyn(string oldSyn, string newSyn, list<pair<int, int>> resultPairs)
{
    assert(ClauseResult::synonymPresent(oldSyn));
    assert(!(ClauseResult::synonymPresent(newSyn)));
    assert(!_isNew);

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

/*
Returns true if there are results in the ClauseResult Object.
Also returns true if ClauseResult is new and have not been
populated before.
*/
bool ClauseResult::hasResults()
{
    if (_isNew) {
        return true;
    } else {
        return !(_results.empty());
    }
}

