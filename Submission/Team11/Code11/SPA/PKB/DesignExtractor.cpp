#include "DesignExtractor.h"

using namespace std;

DesignExtractor::DesignExtractor() {
}

/*
This method computes the transitive closure of all the relations
It propagates through each key and populates the star relations
*/
unordered_map<int, list<int>> DesignExtractor::computeTransitiveClosure(unordered_map<int, list<int>> initialMap) {
    unordered_map<int, list<int>> resultMap;
    int currKey;
    list<int> currValueList;
    list<int> resultValueList;
    queue<int> toVisit;
    int currValue;

    for (auto it : initialMap) {
        currKey = it.first;
        currValueList = it.second;
        for (int value : currValueList) {
            toVisit.push(value);
        }

        while (!toVisit.empty()) {
            currValue = toVisit.front();
            toVisit.pop();
            resultValueList.push_back(currValue);

            if (initialMap.find(currValue) != initialMap.end()) {
                list<int> targetList = initialMap[currValue]; // the list that the curr value is a key to
                for (int valueToVisit : targetList) {
                    toVisit.push(valueToVisit);
                }
            }
        }

        resultValueList.sort();
        resultValueList.unique();
        resultMap[currKey] = resultValueList;
        resultValueList.clear();
        currValueList.clear();
    }
    return resultMap;
}

/*
Overloaded method for different kind of map
*/
unordered_map<int, list<int>> DesignExtractor::computeTransitiveClosure(unordered_map<int, int> initialMap) {
    int currKey;
    int currValue;
    list<int> resultValueList;
    unordered_map<int, list<int>> resultMap;
    queue<int> toVisit;

    for (auto it : initialMap) {
        currKey = it.first;
        int value = it.second;
        toVisit.push(value);

        while (!toVisit.empty()) {
            currValue = toVisit.front();
            toVisit.pop();
            resultValueList.push_back(currValue);
            if (initialMap.find(currValue) != initialMap.end()) {
                toVisit.push(initialMap[currValue]);
            }
        }

        resultValueList.sort();
        resultValueList.unique();
        resultMap[currKey] = resultValueList;
        resultValueList.clear();
    }

    return resultMap;
}

unordered_map<int, list<int>> DesignExtractor::computeParentToChildStarTable(ParentToChildTable parentToChildTable) {
    unordered_map<int, list<int>> parentToChildStarMap;
    unordered_map<int, list<int>> parentToChildMap = parentToChildTable.getTable();
    parentToChildStarMap = computeTransitiveClosure(parentToChildMap);

    return parentToChildStarMap;
}

unordered_map<int, list<int>> DesignExtractor::computeChildToParentStarTable(ChildToParentTable childToParentTable) {
    unordered_map<int, list<int>> childToParentStarMap;
    unordered_map<int, int> childToParentMap = childToParentTable.getTable();
    childToParentStarMap = computeTransitiveClosure(childToParentMap);

    return childToParentStarMap;
}

unordered_map<int, list<int>> DesignExtractor::computeFollowsStarAfterTable(FollowsTable followsTable) {
    unordered_map<int, int> followsAfterMap = followsTable.getFollowsAfterMap();
    unordered_map<int, list<int>> followsStarAfterMap;
    followsStarAfterMap = computeTransitiveClosure(followsAfterMap);
    return followsStarAfterMap;
}

unordered_map<int, list<int>> DesignExtractor::computeFollowsStarBeforeTable(FollowsTable followsTable) {
    unordered_map<int, int> followsBeforeMap = followsTable.getFollowsBeforeMap();
    unordered_map<int, list<int>> followsStarBeforeMap;
    followsStarBeforeMap = computeTransitiveClosure(followsBeforeMap);
    return followsStarBeforeMap;
}

pair<unordered_map<int, list<int>>, unordered_map<int, list<int>>> DesignExtractor::computeCallsStarTable(CallsTable callsTable) {
    unordered_map<int, list<int>> callsStarMap;
    unordered_map<int, list<int>> callsMap = callsTable.getTable();
    unordered_map<int, list<int>> callsStarMapReverse;
    unordered_map<int, list<int>> callsMapReverse = callsTable.getTableReverse();

    callsStarMap = computeTransitiveClosure(callsMap);
    callsStarMapReverse = computeTransitiveClosure(callsMapReverse);
    return make_pair(callsStarMap, callsStarMapReverse);
}

/*
This method performs a depth first search, propagating
the uses table(procedure and variable) updates from the leaf nodes
*/
unordered_map<int, list<int>> DesignExtractor::computeUsesTable(UsesTableProcToVar usesTable, CallsStarTable callsStarTable) {
    unordered_map<int, list<int>> usesMap = usesTable.getMap();
    unordered_map<int, list<int>> callsStarMap = callsStarTable.getMap();
    //iterate all calls
    unordered_set<int> visited;
    for (std::unordered_map<int, list<int>>::iterator it = callsStarMap.begin(); it != callsStarMap.end(); ++it) {
        int currCaller = (*it).first;
        list<int> calleeStar = (*it).second;
        for (int it2 : calleeStar) {
            if (visited.find(it2) == visited.end()) {
                DFS(it2, usesMap, visited, callsStarMap);
                usesMap[currCaller].insert(usesMap[currCaller].end(), usesMap[it2].begin(), usesMap[it2].end());
                usesMap[currCaller].sort();
                usesMap[currCaller].unique();
            }
            else {
                usesMap[currCaller].insert(usesMap[currCaller].end(), usesMap[it2].begin(), usesMap[it2].end());
                usesMap[currCaller].sort();
                usesMap[currCaller].unique();
            }
        }
        visited.insert(currCaller);
    }
    return usesMap;
}
/*
This is the depth first search algorithm used
*/
void DesignExtractor::DFS(int curr, unordered_map<int, list<int>> &map, unordered_set<int> &visited,
    unordered_map<int, list<int>> &callsStarMap) {
    if (callsStarMap.find(curr) == callsStarMap.end()) {
        visited.insert(curr); //If it is the end, aka the leaf
    }

    list<int> children = callsStarMap[curr];
    for (int it : children) {
        if (visited.find(it) == visited.end()) { //If it still has children, visit through it
            DFS(it, map, visited, callsStarMap);
            if (map.find(curr) == map.end()) {
                map[curr] = map[it];
            }
            map[curr].insert(map[curr].end(), map[it].begin(), map[it].end()); //After visited children, visit itself
            map[curr].sort();
            map[curr].unique();
        }
        else { //have alr been visited can just propagate upwards back
            if (map.find(curr) == map.end()) {
                map[curr] = map[it];
            }
            map[curr].insert(map[curr].end(), map[it].begin(), map[it].end());
            map[curr].sort();
            map[curr].unique();
        }
    }
    visited.insert(curr);
}

/*
This method is to populate the modifies procedure to var table with help from callsStarTable
It is similar to that of the computeUsesTable above
*/
unordered_map<int, list<int>> DesignExtractor::computeModifiesTable(ModTableProcToVar modTable, CallsStarTable callsStarTable) {
    unordered_map<int, list<int>> modMap = modTable.getMap();
    unordered_map<int, list<int>> callsStarMap = callsStarTable.getMap();

    unordered_set<int> visited;
    for (std::unordered_map<int, list<int>>::iterator it = callsStarMap.begin(); it != callsStarMap.end(); ++it) {
        int currCaller = (*it).first;
        list<int> calleeStar = (*it).second;
        for (int it2 : calleeStar) {
            if (visited.find(it2) == visited.end()) {
                DFS(it2, modMap, visited, callsStarMap);
                modMap[currCaller].insert(modMap[currCaller].end(), modMap[it2].begin(), modMap[it2].end());
                modMap[currCaller].sort();
                modMap[currCaller].unique();
            }
            else {
                modMap[currCaller].insert(modMap[currCaller].end(), modMap[it2].begin(), modMap[it2].end());
                modMap[currCaller].sort();
                modMap[currCaller].unique();
            }
        }
        visited.insert(currCaller);
    }
    return modMap;
}

/*
This method updates all the statements that are affected by procedure calls statements
*/
unordered_map<int, list<int>> DesignExtractor::computeUsesTable(UsesTableStmtToVar usesTableStmtToVar,
    StmtTypeList stmtTypeList, UsesTableProcToVar usesTableProcToVar, ChildToParentStarTable childToParentStarTable) {
    unordered_map<int, list<int>> usesStmtToVarMap = usesTableStmtToVar.getMap();
    unordered_map<int, int> callToProcIdxMap = stmtTypeList.getCallToProcIdxMap();
    unordered_map<int, list<int>> usesProcToVarMap = usesTableProcToVar.getMap();

    for (unordered_map<int, int>::iterator it = callToProcIdxMap.begin(); it != callToProcIdxMap.end(); ++it) {
        int callStmt = (*it).first;
        int procIdx = (*it).second;

        list<int> procUses = usesProcToVarMap[procIdx];
        list<int> parentStar = childToParentStarTable.getParentStar(callStmt);
        usesStmtToVarMap[callStmt] = procUses; //updates the call statement with the variables used in called procedure
        for (int i : parentStar) { //updates parent statement of the call statement with the variables used
            usesStmtToVarMap[i].insert(usesStmtToVarMap[i].end(), procUses.begin(), procUses.end());
            usesStmtToVarMap[i].sort();
            usesStmtToVarMap[i].unique();
        }
    }

    return usesStmtToVarMap;
}

/*
Updates all modifies statements with additional variablesas from call stmt
*/
unordered_map<int, list<int>> DesignExtractor::computeModifiesTable(ModTableStmtToVar modTableStmtToVar,
    StmtTypeList stmtTypeList, ModTableProcToVar modTableProcToVar, ChildToParentStarTable childToParentStarTable) {
    unordered_map<int, list<int>> modStmtToVarMap = modTableStmtToVar.getMap();
    unordered_map<int, int> callToProcIdxMap = stmtTypeList.getCallToProcIdxMap();
    unordered_map<int, list<int>> modProcToVarMap = modTableProcToVar.getMap();

    for (unordered_map<int, int>::iterator it = callToProcIdxMap.begin(); it != callToProcIdxMap.end(); ++it) {
        int callStmt = (*it).first;
        int procIdx = (*it).second;

        list<int> procModifies = modProcToVarMap[procIdx];
        list<int> parentStar = childToParentStarTable.getParentStar(callStmt);
        modStmtToVarMap[callStmt] = procModifies;
        for (int i : parentStar) {
            modStmtToVarMap[i].insert(modStmtToVarMap[i].end(), procModifies.begin(), procModifies.end());
            modStmtToVarMap[i].sort();
            modStmtToVarMap[i].unique();
        }
    }

    return modStmtToVarMap;
}

/*
Updates relations for uses for all reverse maps from variable to statement
*/
unordered_map<int, list<int>> DesignExtractor::computeUsesTableStmt(UsesTableStmtToVar usesTableStmtToVar) {
    unordered_map<int, list<int>> usesStmtToVarMap = usesTableStmtToVar.getMap();
    unordered_map<int, list<int>> usesVarToStmtMap;

    for (unordered_map<int, list<int>>::iterator it = usesStmtToVarMap.begin(); it != usesStmtToVarMap.end(); ++it) {
        int stmt = (*it).first;
        list<int> varList = (*it).second;
        for (int var : varList) {
            if (usesVarToStmtMap.find(var) == usesVarToStmtMap.end()) {
                usesVarToStmtMap[var] = list<int>();
                usesVarToStmtMap[var].push_back(stmt);
            }
            else {
                usesVarToStmtMap[var].push_back(stmt);
                usesVarToStmtMap[var].sort();
                usesVarToStmtMap[var].unique();
            }
        }
    }

    return usesVarToStmtMap;
}

/*
Updates reverse mapping from variable to procedure
*/
unordered_map<int, list<int>> DesignExtractor::computeUsesTableProc(UsesTableProcToVar usesTableProcToVar) {
    unordered_map<int, list<int>> usesProcToVarMap = usesTableProcToVar.getMap();
    unordered_map<int, list<int>> usesVarToProcMap;

    for (unordered_map<int, list<int>>::iterator it = usesProcToVarMap.begin(); it != usesProcToVarMap.end(); ++it) {
        int proc = (*it).first;
        list<int> varList = (*it).second;
        for (int var : varList) {
            if (usesVarToProcMap.find(var) == usesVarToProcMap.end()) {
                usesVarToProcMap[var] = list<int>();
                usesVarToProcMap[var].push_back(proc);
            }
            else {
                usesVarToProcMap[var].push_back(proc);
                usesVarToProcMap[var].sort();
                usesVarToProcMap[var].unique();
            }
        }
    }

    return usesVarToProcMap;
}

/*
Updates reverse mapping from variables to statement
*/
unordered_map<int, list<int>> DesignExtractor::computeModTableStmt(ModTableStmtToVar modTableStmtToVar) {
    unordered_map<int, list<int>> modStmtToVarMap = modTableStmtToVar.getMap();
    unordered_map<int, list<int>> modVarToStmtMap;

    for (unordered_map<int, list<int>>::iterator it = modStmtToVarMap.begin(); it != modStmtToVarMap.end(); ++it) {
        int stmt = (*it).first;
        list<int> varList = (*it).second;
        for (int var : varList) {
            if (modVarToStmtMap.find(var) == modVarToStmtMap.end()) {
                modVarToStmtMap[var] = list<int>();
                modVarToStmtMap[var].push_back(stmt);
            }
            else {
                modVarToStmtMap[var].push_back(stmt);
                modVarToStmtMap[var].sort();
                modVarToStmtMap[var].unique();
            }
        }
    }

    return modVarToStmtMap;
}

/*
Updates reverse mapping from variable to procedure
*/
unordered_map<int, list<int>> DesignExtractor::computeModTableProc(ModTableProcToVar modTableProcToVar) {
    unordered_map<int, list<int>> modProcToVarMap = modTableProcToVar.getMap();
    unordered_map<int, list<int>> modVarToProcMap;

    for (unordered_map<int, list<int>>::iterator it = modProcToVarMap.begin(); it != modProcToVarMap.end(); ++it) {
        int proc = (*it).first;
        list<int> varList = (*it).second;
        for (int var : varList) {
            if (modVarToProcMap.find(var) == modVarToProcMap.end()) {
                modVarToProcMap[var] = list<int>();
                modVarToProcMap[var].push_back(proc);
            }
            else {
                modVarToProcMap[var].push_back(proc);
                modVarToProcMap[var].sort();
                modVarToProcMap[var].unique();
            }
        }
    }

    return modVarToProcMap;
}