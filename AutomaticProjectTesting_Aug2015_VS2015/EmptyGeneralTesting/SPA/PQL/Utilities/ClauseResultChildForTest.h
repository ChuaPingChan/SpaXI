#pragma once

#include "ClauseResult.h"

using namespace std;

class ClauseResultChildForTest : public ClauseResult
{
public:
    ClauseResultChildForTest();

    static void appendToVector(vector<int> &v1, const vector<int> &v2, int n);

};
