#pragma once
#include <vector>
#include <list>

using namespace std;

class SynonymUFDS
{
public:
    SynonymUFDS();

    bool addSynonym(int synIdx);
    int findSet(int synIdx);
    bool isSameSet(int syn1Idx, int syn2Idx);
    void unionSet(int syn1Idx, int syn2Idx);
    bool synonymPresent(int synIdx);

    list<list<int>> getSynonymGroups();

private:
    vector<int> p;
    vector<int> rank;

};

