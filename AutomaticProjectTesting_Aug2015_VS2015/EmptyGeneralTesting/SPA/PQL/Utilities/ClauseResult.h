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
    ~ClauseResult();

    vector<string> getAllSynonyms();
    void getSynonymResults(string synName, vector<string> *results);
    void getSynonymResults(string synName, vector<int> *results);
    bool synonymPresent(string synName);
    bool addNewSynResults(string newSynName, vector<string> newSynResults);
    bool addNewSynResults(string newSynName, vector<int> newSynResults);
    bool removeCombinations(string synName, int value);
    bool removeCombinations(string synName, string value);
    bool pairWithOldSyn(string oldSyn, string oldSynValue, string newSyn, vector<string> newSynResults);
    bool pairWithOldSyn(string oldSyn, int oldSynValue, string newSyn, vector<int> newSynResults);


private:
    unordered_map<string, int> _synToIdxMap;
    vector<string> _synList;
    vector<vector<int>> _intResult;
    vector<vector<string>> _stringResult;
};

