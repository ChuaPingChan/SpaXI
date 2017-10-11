#include "ClauseResultChildForTest.h"
#include "../SPA/PQL/Utilities/ClauseResult.h"

using namespace std;

/*
This class's sole purpose in life is to allow unit testing
for the protected methods of the ClauseResult class :O

DO NOT use this class in the real SPA.
*/
ClauseResultChildForTest::ClauseResultChildForTest()
{
}

list<vector<int>> ClauseResultChildForTest::pairUpListsResults(list<int>& syn1Results, list<int>& syn2Results)
{
    return ClauseResult::pairUpListsResults(syn1Results, syn2Results);
}
