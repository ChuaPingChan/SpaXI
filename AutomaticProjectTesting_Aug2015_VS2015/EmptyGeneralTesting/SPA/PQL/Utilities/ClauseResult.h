#pragma once

#include <unordered_map>

using namespace std;

/*
This class is responsible for merging and storing the results of
multiple PQL query clauses.
*/
class ClauseResult
{
public:
    ClauseResult();

    vector<string> getAllSynonyms();
    vector<vector<int>> getSynonymResults(vector<string> synNames);
    vector<int> getSynonymResults(string synName);
    vector<vector<int>> getAllResults();
    bool synonymPresent(string synName);
    bool addNewSynResults(string newSynName, vector<int> newSynResults);
    //bool overlapExistingSynResults(string synName, vector<int> synResultsToOverlap);
    bool addNewSynPairResults(string syn1Name, list<int> syn1Results, string syn2Name, list<int> syn2Results);
    bool addNewSynPairResults(string syn1Name, int syn2Result, vector<vector<int>> pairResults);
    bool removeCombinations(string synName, int value);
    bool pairWithOldSyn(string oldSyn, int oldSynValue, string newSyn, vector<int> newSynResults);
    
protected:
    unordered_map<string, int> _synToIdxMap;
    vector<string> _synList;
    vector<vector<int>> _results;     // Results of stmt, constant, prog_line synonyms

    template<typename T> static void appendToVector(vector<T> &v1, const vector<T> &v2, int n)
    {
        for (int i = 0; i < n; i++) {
            v1.insert(v1.end(), v2.begin(), v2.end());
        }
    }
};
