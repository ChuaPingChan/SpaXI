#include "ClauseResult.h"

using namespace std;

ClauseResult::ClauseResult()
{
}

ClauseResult::~ClauseResult()
{
}

vector<string> ClauseResult::getAllSynonyms()
{
    return vector<string>();
}

void ClauseResult::getSynonymResults(string synName, vector<string>* results)
{
}

bool ClauseResult::synonymPresent(string synName)
{
    return false;
}

bool ClauseResult::addNewSynResults(string newSynName, vector<string> newSynResults)
{
    return false;
}

bool ClauseResult::removeCombinations(string synName, int value)
{
    return false;
}

bool ClauseResult::removeCombinations(string synName, string value)
{
    return false;
}

bool ClauseResult::pairWithOldSyn(string oldSyn, string oldSynValue, string newSyn, vector<string> newSynResults)
{
    return false;
}

bool ClauseResult::pairWithOldSyn(string oldSyn, int oldSynValue, string newSyn, vector<int> newSynResults)
{
    return false;
}
