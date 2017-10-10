#pragma once

#include <unordered_map>
#include <set>
#include <iterator>
#include <utility>

using namespace std;

/*
This class is responsible for merging and storing the results of
multiple PQL query clauses.
*/
class ClauseResult
{
public:
    ClauseResult();

    list<string> getAllSynonyms();
    list<list<int>> getSynonymResults(vector<string> synNames);
    // TODO: Implement this
    list<int> getSynonymResults(string synNames);
    // TODO: Complete list<pair<int>> getSynonymPairResults(string syn1Name, string syn2Name);
    list<pair<int,int>> getSynonymPairResults(string syn1Name, string syn2Name);
    list<list<int>> getAllResults();
    bool synonymPresent(string synName);
    bool addNewSynResults(string newSynName, list<int> newSynResults);
    // TODO: Make addNewSynResults do overlapExistingSynResults
    bool overlapExistingSynResults(string synName, list<int> synResultsToOverlap);
    bool addNewSynPairResults(string syn1Name, list<int> syn1Results, string syn2Name, list<int> syn2Results);
    bool addNewSynPairResults(string syn1Name, string syn2Name, vector<vector<int>> pairResults);
    bool removeCombinations(string synName, int value);
    bool removeCombinations(string syn1Name, int syn1Value, string syn2Name, int syn2Value);
    bool pairWithOldSyn(string oldSyn, int oldSynValue, string newSyn, list<int> newSynResults);
    bool hasResults();
    
protected:
    unordered_map<string, int> _synToIdxMap;
    vector<string> _synList;
    list<vector<int>> _results;   // All results are stored as int (i.e. indices of entities in PKB)

    // TODO: Unit test needed.
    template<typename T> static list<T> convertVectorToList(vector<T> &v)
    {
        list<T> newList;
        newList.clear();
        copy(v.begin(), v.end(), back_inserter(newList));
        return newList;
    }

    // TODO: Unit test needed.
    template<typename T> static list<list<T>> convertVectorOfVectorToListOfLists(list<vector<T>> &v)
    {
        list<list<T>> newListOfLists;
        newListOfLists.clear();
        for (list<vector<T>>::iterator innerVecPtr = v.begin();
            innerVecPtr != v.end();
            innerVecPtr++) {
            list<T> innerList = convertVectorToList(*innerVecPtr);
            newListOfLists.push_back(innerList);
        }
        return newListOfLists;
    }

    // TODO: Unit test needed.
    template<typename T> static vector<T> convertListToVector(list<T> &listToConvert)
    {
        vector<T> newVector;
        newVector.clear();
        copy(listToConvert.begin(), listToConvert.end(), back_inserter(newVector));
        return newVector;
    }

    template<typename T> static void appendToVector(vector<T> &v1, const vector<T> &v2, int n)
    {
        for (int i = 0; i < n; i++) {
            v1.insert(v1.end(), v2.begin(), v2.end());
        }
    }

    // TODO: Unit test this method
    template<typename T> static vector<T> getUniqueElements(vector<T> &vec)
    {
        set<T> s(vec.begin(), vec.end());
        vector<T> uniqueVec;
        uniqueVec.clear();
        uniqueVec.assign(s.begin(), s.end());
        return uniqueVec;
    }

    // TODO: Unit test this method
    template<typename T> static list<T> getUniqueElements(list<T> &vec)
    {
        set<T> s(vec.begin(), vec.end());
        list<T> uniqueVec;
        uniqueVec.clear();
        uniqueVec.assign(s.begin(), s.end());
        return uniqueVec;
    }
};
