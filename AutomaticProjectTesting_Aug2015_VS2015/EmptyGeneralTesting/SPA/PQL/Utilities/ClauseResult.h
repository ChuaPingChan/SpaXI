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
    void getSynonymResults(string synName, vector<string> &results);
    void getSynonymResults(string synName, vector<int> &results);
    bool synonymPresent(string synName);
    bool addNewSynResults(string newSynName, vector<string> newSynResults);
    bool addNewSynResults(string newSynName, vector<int> newSynResults);
    bool removeCombinations(string synName, int value);
    bool removeCombinations(string synName, string value);
    bool pairWithOldSyn(string oldSyn, string oldSynValue, string newSyn, vector<string> newSynResults);
    bool pairWithOldSyn(string oldSyn, int oldSynValue, string newSyn, vector<int> newSynResults);
    
protected:
    unordered_map<string, int> _synToIdxMap;
    vector<string> _synList;
    vector<vector<int>> _intResult;     // Results of stmt, constant, prog_line synonyms
    vector<vector<string>> _strResult;  // Results of procedure and variable synonyms

    template<typename T> static void appendToVector(vector<T> &v1, const vector<T> &v2, int n)
    {
        for (int i = 0; i < n; i++) {
            v1.insert(v1.end(), v2.begin(), v2.end());
        }
    }
};
