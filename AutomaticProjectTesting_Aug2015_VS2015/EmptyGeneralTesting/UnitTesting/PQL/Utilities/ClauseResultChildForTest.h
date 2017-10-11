#pragma once

#include "../SPA/PQL/Utilities/ClauseResult.h"

using namespace std;

/*
This class's sole purpose in life is to allow unit testing
for the protected methods of the ClauseResult class :O

DO NOT use this class in the real SPA.
*/
class ClauseResultChildForTest : public ClauseResult
{
public:
    ClauseResultChildForTest();

    static list<vector<int>> pairUpListsResults(list<int> &syn1Results, list<int> &syn2Results);

    template<typename T> static vector<T> joinTwoVectors(vector<T> &v1, const vector<T> &v2, int n = 1)
    {
        return ClauseResult::joinTwoVectors(v1, v2, n);
    }

    template<typename T> static vector<T> getUniqueVectorElements(vector<T> &vec)
    {
        return ClauseResult::getUniqueVectorElements(vec);
    }

    template<typename T> static list<T> getUniqueListElements(const list<T> &l)
    {
        return ClauseResult::getUniqueListElements(l);
    }

    template<typename T> static vector<T> convertPairToVector(const pair<T, T> &p)
    {
        return ClauseResult::convertPairToVector(p);
    }

};
