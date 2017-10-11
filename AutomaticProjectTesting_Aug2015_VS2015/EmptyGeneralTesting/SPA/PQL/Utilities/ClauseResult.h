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
    list<list<int>> getSynonymResults(vector<string> synNames); // TODO: Unit testing
    list<int> getSynonymResults(string synNames);   // TODO: Unit testing
    list<pair<int, int>> getSynonymPairResults(string syn1Name, string syn2Name);    // TODO: Unit testing
    list<list<int>> getAllResults();
    bool synonymPresent(string synName);    // TODO: Unit testing
    bool updateSynResults(string synName, list<int> newSynResults);  // TODO: Unit testing
    // TODO: Make updateSynResults do overlapExistingSynResults
    bool overlapExistingSynResults(string synName, list<int> synResultsToOverlap);  // TODO: Unit testing
    bool addNewSynPairResults(string syn1Name, list<int> syn1Results, string syn2Name, list<int> syn2Results);  // TODO: Unit testing
    bool addNewSynPairResults(string syn1Name, string syn2Name, list<vector<int>> pairResults); // TODO: Unit testing
    bool removeCombinations(string synName, int value); // TODO: Unit testing
    bool removeCombinations(string syn1Name, int syn1Value, string syn2Name, int syn2Value);
    bool pairWithOldSyn(string oldSyn, string newSyn, list<pair<int, int>> resultPairs);    // TODO: Unit testing
    bool hasResults();  // TODO: Unit testing

protected:
    unordered_map<string, int> _synToIdxMap;
    vector<string> _synList;
    list<vector<int>> _results;   // All results are stored as int (i.e. indices of entities in PKB)


    /******************
     * Helper methods *
     ******************/
    list<vector<int>> convertTwoListsToListOfPairResultVector(list<int> &syn1Results, list<int> &syn2Results);

    // TODO: Unit testing
    template<typename T> static list<T> convertVectorToList(vector<T> &v)
    {
        list<T> newList;
        newList.clear();
        copy(v.begin(), v.end(), back_inserter(newList));
        return newList;
    }

    // TODO: Unit testing
    template<typename T> static list<list<T>> convertListOfVectorsToListOfLists(list<vector<T>> &v)
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

    // TODO: Unit testing
    template<typename T> static vector<T> convertListToVector(list<T> &listToConvert)
    {
        vector<T> newVector;
        newVector.clear();
        copy(listToConvert.begin(), listToConvert.end(), back_inserter(newVector));
        return newVector;
    }

    /*
    Returns a new vector which elements are the result of concatenating v2 to v1.
    If n is not given, the default value is 1.
    */
    template<typename T> static vector<T> joinTwoVectors(const vector<T> &v1, const vector<T> &v2, int n = 1)
    {
        if (v2.empty())
            return v1;

        vector<T> v3 = v1;
        for (int i = 0; i < n; i++) {
            v3.insert(v3.end(), v2.begin(), v2.end());
        }
        return v3;
    }

    template<typename T> static vector<T> getUniqueVectorElements(const vector<T> &vec)
    {
        set<T> s(vec.begin(), vec.end());
        vector<T> uniqueVec;
        uniqueVec.clear();
        uniqueVec.assign(s.begin(), s.end());
        return uniqueVec;
    }

    template<typename T> static list<T> getUniqueListElements(const list<T> &l)
    {
        list<T> uniqueList(l);
        uniqueList.sort();
        uniqueList.unique();
        return uniqueList;
    }

    template<typename T> static vector<T> convertPairToVector(const pair<T, T> &p)
    {
        vector<T> v;
        v.clear();
        v.push_back(p.first);
        v.push_back(p.second);
        return v;
    }
};
