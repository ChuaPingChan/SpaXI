#include <cassert>
#include <unordered_set>
#include <set>

#include "ClauseResult.h"
#include "AbstractWrapper.h"

using namespace std;

ClauseResult::ClauseResult()
{
    _synToIdxMap = unordered_map<string, int>();
    _synList = vector<string>();
    _resultsPtr = ResultsPtr(new list<vector<int>>());
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
    for (string synName : synNames) {
        synIndices.push_back(_synToIdxMap.at(synName));
    }

    // For each combinations, filter the selected synonyms only.
    for (vector<int> existingComb : *_resultsPtr) {
        list<int> selectedSynCombinations;

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
    synNameVec.push_back(synName);

    list<list<int>> resultVerticalList = getSynonymResults(synNameVec);

    // Put resutls into a single list for the convenience of evaluators
    list<int> resultHorizontalList;
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
    synNameList.push_back(syn1Name);
    synNameList.push_back(syn2Name);

    list<list<int>> synPairResultList = getSynonymResults(synNameList);

    list<pair<int, int>> synPairResult;
    // Convert inner lists to pairs
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
    return ClauseResult::convertListOfVectorsToListOfLists(*_resultsPtr);
}

bool ClauseResult::synonymPresent(string synName)
{
    return _synToIdxMap.find(synName) != _synToIdxMap.end();
}

/*
    Updates the result of a new or an existing synonym.
    Pre-condition: Ensure new synonym has non-empty results.
    Note: This may method involve computing Catesian product - computationally expensive.
*/
bool ClauseResult::updateSynResults(string newSynName, list<int> newSynResultsList)
{
    //assert(newSynResultsList.size() > 0); // Comment out during release. For debugging only

    _isNew = false;
    if (_synToIdxMap.find(newSynName) != _synToIdxMap.end())
    {
        return overlapExistingSynResults(newSynName, newSynResultsList);
    }

    vector<int> newSynResults = convertListToVector(newSynResultsList);

    // Add to _synList
    _synList.push_back(newSynName);
    int newSynIdx = _synList.size() - 1;

    // Add to _synToIdxMap
    _synToIdxMap.insert({ newSynName, newSynIdx });

    if (_resultsPtr->empty()) {
        for (vector<int>::iterator newSynResPtr = newSynResults.begin();
            newSynResPtr != newSynResults.end();
            newSynResPtr++)
        {
            vector<int> newComb;
            newComb.push_back(*newSynResPtr);
            _resultsPtr->push_back(newComb);
        }
        return true;
    }

    // Update _result - Cartesian product
    int repeatNumber = newSynResults.size();
    ResultsPtr outdatedResult = _resultsPtr;
    _resultsPtr = ResultsPtr(new Result());

    for (vector<int> comb : *outdatedResult) {
        for (int newSynRes : newSynResults) {
            vector<int> newComb = comb;
            newComb.push_back(newSynRes);
            _resultsPtr->push_back(newComb);
        }

        if (AbstractWrapper::GlobalStop) {
            return true;
        }
    }

    return true;
}

/*
    Merges this ClauseResult with clauseResultToMerge. Only the selectedSyns
    of clauseResultsToMerge will be extracted and merged into this.
*/
bool ClauseResult::mergeClauseResult(ClauseResult clauseResultToMerge, unordered_set<string> selectedSyns)
{
    // Get all selected synonyms in the other clause result
    list<string> synsInClauseResult = clauseResultToMerge.getAllSynonyms();
    list<string> synsToMerge;
    for (string synName : synsInClauseResult) {
        if (selectedSyns.find(synName) != selectedSyns.end())
            synsToMerge.push_back(synName);
    }

    if (synsToMerge.size() == 0)
        return true;    // No merging takes place if no synonyms in the new clause result is "selected" in the query

    // Get the results of only the synonyms to merge and remove duplicates
    list<list<int>> resultsToMerge = clauseResultToMerge.getSynonymResults(synsToMerge);
    resultsToMerge.sort();
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
    if (_resultsPtr->empty()) {
        for (list<int> newComb : resultsToMerge) {
            vector<int> newCombToMerge = convertListToVector(newComb);
            _resultsPtr->push_back(newCombToMerge);
        }
        return true;
    }

    int repeatNumber = resultsToMerge.size();
    ResultsPtr outdatedResult = _resultsPtr;
    _resultsPtr = ResultsPtr(new Result());

    for (vector<int> currComb : *outdatedResult) {
        for (list<int> newSynsResList : resultsToMerge) {
            vector<int> newSynsResVec = convertListToVector(newSynsResList);
            vector<int> newComb = joinTwoVectors(currComb, newSynsResVec);

            _resultsPtr->push_back(newComb);
        }

        if (AbstractWrapper::GlobalStop) {
            return true;
        }
    }

    return true;
}

/*
    Adds the results of syn1Name and syn2Name to the intermediate result, where
    both syn1Name and syn2Name are new (not existing in the ClauseResult yet).
*/
bool ClauseResult::addNewSynPairResults(string syn1Name, string syn2Name, list<vector<int>> pairResults)
{
    assert(pairResults.size() > 0);
    assert(_synToIdxMap.find(syn1Name) == _synToIdxMap.end());    // syn1 must be new synonym
    assert(_synToIdxMap.find(syn2Name) == _synToIdxMap.end());    // syn2 must be new synonym

    _isNew = false;

    // Add to _synList and _synToIdxMap
    _synList.push_back(syn1Name);
    int syn1Idx = _synList.size() - 1;
    _synList.push_back(syn2Name);
    int syn2Idx = _synList.size() - 1;
    _synToIdxMap.insert({ syn1Name, syn1Idx });
    _synToIdxMap.insert({ syn2Name, syn2Idx });

    // Update _result - Cartesian product
    if (_resultsPtr->empty()) {
        for (list<vector<int>>::iterator pairResultPtr = pairResults.begin();
            pairResultPtr != pairResults.end();
            pairResultPtr++)
        {
            _resultsPtr->push_back(*pairResultPtr);
        }
        return true;
    }

    ResultsPtr updatedResultsPtr = ResultsPtr(new Result());

    for (vector<int> existingComb : *_resultsPtr)
    {
        for (vector<int> pairResult : pairResults)
        {
            vector<int> newComb = existingComb;
            newComb = ClauseResult::joinTwoVectors(newComb, pairResult);
            updatedResultsPtr->push_back(newComb);
        }

        if (AbstractWrapper::GlobalStop) {
            return true;
        }
    }
    _resultsPtr = updatedResultsPtr;

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

    // Simulate zip iterator
    list<int>::iterator iter1 = syn1Results.begin();
    list<int>::iterator iter2 = syn2Results.begin();
    for (; iter1 != syn1Results.end() && iter2 != syn2Results.end(); iter1++, iter2++) {
        vector<int> pairResult;
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

    ResultsPtr updatedResultsPtr = ResultsPtr(new Result());    // to overwrite _results at the end of this method

    for (vector<int> comb : *_resultsPtr)
    {
        int valueInComb = (comb).at(synIdx);
        if (resultsSetToOverlap.find(valueInComb) != resultsSetToOverlap.end()) {
            updatedResultsPtr->push_back(comb);
        }

        if (AbstractWrapper::GlobalStop) {
            return true;
        }
    }
    _resultsPtr = updatedResultsPtr;
    return true;
}

/*
    Updates the existing the results of syn1 and syn2 so that the intermediate
    results satisfies those present in resultsToOverlap.

    Pre-condition: Both syn1 and syn2 must be present in ClauseResult
*/
bool ClauseResult::updateSynPairResults(string syn1, string syn2, pair<list<int>,list<int>> resultsToOverlap)
{
    assert(ClauseResult::synonymPresent(syn1));
    assert(ClauseResult::synonymPresent(syn2));
    assert(!_isNew);

    int syn1Idx = _synToIdxMap.at(syn1);
    int syn2Idx = _synToIdxMap.at(syn2);

    // Create hash set to facilitate the removal of existing results
    unordered_map<int, unordered_set<int>> syn1ToSyn2ValsMap;
    list<int> syn1ResultsToOverlap = resultsToOverlap.first;
    list<int> syn2ResultsToOverLap = resultsToOverlap.second;
    assert(syn1ResultsToOverlap.size() == syn2ResultsToOverLap.size());
    // Simulate zip iterator
    list<int>::iterator iter1 = syn1ResultsToOverlap.begin();
    list<int>::iterator iter2 = syn2ResultsToOverLap.begin();
    for (; iter1 != syn1ResultsToOverlap.end() && iter2 != syn2ResultsToOverLap.end(); iter1++, iter2++) {
        syn1ToSyn2ValsMap[*iter1].insert(*iter2);
    }

    // Removal of existing combinations
    list<vector<int>>::iterator existingResultsIter = _resultsPtr->begin();
    while (existingResultsIter != _resultsPtr->end())
    {
        if (AbstractWrapper::GlobalStop) {
            return true;
        }

        int syn1Val = existingResultsIter->at(syn1Idx);
        int syn2Val = existingResultsIter->at(syn2Idx);

        if (syn1ToSyn2ValsMap.find(syn1Val) == syn1ToSyn2ValsMap.end()) {
            // If syn1 is not in the hashmap's key set, then erase
            existingResultsIter = _resultsPtr->erase(existingResultsIter);
        } else {
            unordered_set<int> syn2ValsToOverlap = syn1ToSyn2ValsMap[syn1Val];
            if (syn2ValsToOverlap.find(syn2Val) == syn2ValsToOverlap.end()) {
                // syn1 is in the hashmap's key set but syn2 is not in the corresponding hash set, erase too
                existingResultsIter = _resultsPtr->erase(existingResultsIter);
            } else {
                existingResultsIter++;
            }
        }
    }
    return true;
}

/*
    Removes the synonyms in the intermediate result table that are not present
    in synsToRetain.

    Instead of actually removing columns, this method sets the values to
    ClauseResult::INT_PRUNED (-1).
*/
bool ClauseResult::pruneColumns(unordered_set<string> synsToRetain)
{
    list<int> synsIdxToPrune;
    for (string syn : _synList) {
        if ((_prunedSyns.find(syn) == _prunedSyns.end())
            && (synsToRetain.find(syn) == synsToRetain.end()))
        {
            synsIdxToPrune.push_back(_synToIdxMap.at(syn));
            _prunedSyns.insert(syn);
        }
    }

    for (list<vector<int>>::iterator resIter = _resultsPtr->begin();
        resIter != _resultsPtr->end();
        resIter++) {
        for (int synIdxToPrune : synsIdxToPrune) {
            (*resIter)[synIdxToPrune] = ClauseResult::INT_PRUNED;
        }
    }

    if (AbstractWrapper::GlobalStop) {
        return true;
    }

    _resultsPtr->sort();
    _resultsPtr->unique();

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
    assert(_synToIdxMap.find(newSyn) == _synToIdxMap.end());
    _synToIdxMap.insert({ newSyn, newSynIdx });

    // Create hash map to hasten merging with existing results
    unordered_map<int, vector<int>> oldSynValToNewSynResultMap;

    // Populate oldSynValToNewSynResultMap
    resultPairs.sort();
    resultPairs.unique();
    for (pair<int, int> resultPair : resultPairs)
    {   // Convert pair to vector so that it can be appended to existing vector easily
        oldSynValToNewSynResultMap[resultPair.first].push_back(resultPair.second);
    }

    // Merging with existing combinations
    int oldSynIdx = _synToIdxMap.at(oldSyn);
    ResultsPtr updatedResultsPtr = ResultsPtr(new Result());
    for (vector<int> existingCombination : *_resultsPtr)
    {
        const int oldSynVal = existingCombination[oldSynIdx];

        if (oldSynValToNewSynResultMap.find(oldSynVal) != oldSynValToNewSynResultMap.end()) {
            vector<int> newSynResults = oldSynValToNewSynResultMap.at(oldSynVal);
            for (int newSynResult : newSynResults) {
                vector<int> newComb = existingCombination;
                newComb.push_back(newSynResult);
                updatedResultsPtr->push_back(newComb);
            }
        }

        if (AbstractWrapper::GlobalStop) {
            return true;
        }
    }
    _resultsPtr = updatedResultsPtr;

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
        return !(_resultsPtr->empty());
    }
}

