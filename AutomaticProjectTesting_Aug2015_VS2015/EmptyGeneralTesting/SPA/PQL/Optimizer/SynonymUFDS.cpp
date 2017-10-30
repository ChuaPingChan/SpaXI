#include <cassert>
#include <vector>
#include <unordered_map>
#include "SynonymUFDS.h"

using namespace std;

SynonymUFDS::SynonymUFDS()
{
}

// TODO: Remove if not needed at the end
//SynonymUFDS::SynonymUFDS(int size)
//{
//    for (int i = 0; i < size; i++) {
//        addSynonym(i);
//    }
//}

bool SynonymUFDS::addSynonym(int synIdx)
{
    p.push_back(synIdx);
    rank.push_back(0);
    assert(p.size() == rank.size());
    return true;
}

int SynonymUFDS::findSet(int synIdx)
{
    if (p[synIdx] = synIdx)
        return synIdx;
    int ret = findSet(p[synIdx]);
    p[synIdx] = ret;
    return ret;
}

bool SynonymUFDS::isSameSet(int syn1Idx, int syn2Idx)
{
    return findSet(syn1Idx) == findSet(syn2Idx);
}

void SynonymUFDS::unionSet(int syn1Idx, int syn2Idx)
{
    if (!isSameSet(syn1Idx, syn2Idx)) {
        int syn1Set = findSet(syn1Idx);
        int syn2Set = findSet(syn2Idx);

        if (rank[syn1Set] > rank[syn2Set]) {
            p[syn2Set] = syn1Set;
        } else {
            p[syn1Set] = syn2Set;
            if (rank[syn1Set] == rank[syn2Set])
                rank[syn2Set]++;
        }
    }
}

bool SynonymUFDS::synonymPresent(int synIdx)
{
    return synIdx < p.size();
}

list<list<int>> SynonymUFDS::getSynonymGroups()
{
    list<list<int>> synonymGroups;

    unordered_map<int, list<int>> setRepToMembersMap;
    
    for (int synIdx = 0; synIdx < p.size(); synIdx++) {
        int setRep = p[synIdx];
        setRepToMembersMap[setRep].push_back(synIdx);
    }

    for (auto setRepMembersPair : setRepToMembersMap) {
        synonymGroups.push_back(setRepMembersPair.second);
    }
    return synonymGroups;
}
