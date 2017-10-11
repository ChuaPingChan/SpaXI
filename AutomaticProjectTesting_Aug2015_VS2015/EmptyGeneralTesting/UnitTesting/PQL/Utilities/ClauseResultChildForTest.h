#pragma once

#include "../SPA/PQL/Utilities/ClauseResult.h"

using namespace std;

class ClauseResultChildForTest : public ClauseResult
{
public:
    ClauseResultChildForTest();

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
