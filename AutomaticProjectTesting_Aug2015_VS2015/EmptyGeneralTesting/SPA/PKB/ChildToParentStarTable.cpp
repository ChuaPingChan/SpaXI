#include "ChildToParentStarTable.h"

using namespace std;

ChildToParentStarTable::ChildToParentStarTable()
{
}

list<int> ChildToParentStarTable::getParentStar(int childStmt) {
    if (childToParentStarMap.find(childStmt) == childToParentStarMap.end()) {
        return list<int>();
    }
    return childToParentStarMap[childStmt];
}

/*
Iterate through the map and populate relation map
*/
void ChildToParentStarTable::setMap(unordered_map<int, list<int>> target) {
    for (auto it : target) {
        list<int> parentList = it.second;
        for (int parent : parentList) {
            childToParentStarRel[it.first].insert(parent);
        }
    }

    childToParentStarMap = target;
}

bool ChildToParentStarTable::isParentStar(int parentStmt, int childStmt) {
    if (childToParentStarRel.find(childStmt) == childToParentStarRel.end()) {
        return false;
    }

    return (childToParentStarRel[childStmt].find(parentStmt) != childToParentStarRel[childStmt].end());
}