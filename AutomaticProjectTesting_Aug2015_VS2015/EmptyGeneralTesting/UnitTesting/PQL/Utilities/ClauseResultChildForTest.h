#pragma once

#include "../SPA/PQL/Utilities/ClauseResult.h"

using namespace std;

class ClauseResultChildForTest : public ClauseResult
{
public:
    ClauseResultChildForTest();

    template<typename T> static void appendToVector(vector<T> &v1, const vector<T> &v2, int n)
    {
        ClauseResult::appendToVector(v1, v2, n);
    }

};
