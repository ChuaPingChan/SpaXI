#pragma once

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <iterator>
#include <utility>
#include <memory>

using namespace std;

/*
This class is responsible for merging and storing the results of
multiple PQL query clauses.
*/
class ClauseResult
{
public:
    static const int INT_PRUNED = -1;

    ClauseResult();

    list<string> getAllSynonyms();
    list<list<int>> getSynonymResults(list<string> synNames);
    list<int> getSynonymResults(string synNames);
    list<pair<int, int>> getSynonymPairResults(string syn1Name, string syn2Name);
    list<list<int>> getAllResults();
    bool synonymPresent(string synName);
    bool updateSynResults(string synName, list<int> newSynResults);
    bool mergeClauseResult(ClauseResult clauseResultToMerge, unordered_set<string> selectedSyns);
    bool addNewSynPairResults(string syn1Name, list<int> syn1Results, string syn2Name, list<int> syn2Results);
    bool removeCombinations(string synName, int value);
    bool removeCombinations(string syn1Name, int syn1Value, string syn2Name, int syn2Value);
    bool pruneColumns(unordered_set<string> synsToRetain);
    bool pairWithOldSyn(string oldSyn, string newSyn, list<pair<int, int>> resultPairs);
    bool hasResults();

protected:
    unordered_map<string, int> _synToIdxMap;
    vector<string> _synList;
    shared_ptr<list<vector<int>>> _resultsPtr;  // All results are stored as int (i.e. indices of entities in PKB)
    bool _isNew;    // Flag to indicate whether ClauseResult has been populated before

    /******************
     * Helper methods *
     ******************/
    static list<vector<int>> pairUpListsResults(list<int> &syn1Results, list<int> &syn2Results);
    bool overlapExistingSynResults(string synName, list<int> synResultsToOverlap);
    bool addNewSynPairResults(string syn1Name, string syn2Name, list<vector<int>> pairResults);

    template<typename T> static list<T> convertVectorToList(vector<T> &v)
    {
        list<T> newList;
        copy(v.begin(), v.end(), back_inserter(newList));
        return newList;
    }

    template<typename T> static list<list<T>> convertListOfVectorsToListOfLists(list<vector<T>> &v)
    {
        list<list<T>> newListOfLists;
        for (list<vector<T>>::iterator innerVecPtr = v.begin();
            innerVecPtr != v.end();
            innerVecPtr++) {
            list<T> innerList = convertVectorToList(*innerVecPtr);
            newListOfLists.push_back(innerList);
        }
        return newListOfLists;
    }

    template<typename T> static vector<T> convertListToVector(list<T> &listToConvert)
    {
        vector<T> newVector;
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
        v.push_back(p.first);
        v.push_back(p.second);
        return v;
    }
};

typedef list<vector<int>> Result;
typedef shared_ptr<list<vector<int>>> ResultsPtr;
