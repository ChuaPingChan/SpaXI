#include "DesignExtractor.h"

using namespace std;

DesignExtractor::DesignExtractor() {
}

unordered_map<int, list<int>> DesignExtractor::computeParentToChildStarTable(ParentToChildTable parentToChildTable) {
	unordered_map<int, list<int>> parentToChildStarMap;
	unordered_map<int, list<int>> parentToChildMap = parentToChildTable.getTable();
	int currParent;
	list<int> childrenList; //all children&grandchildrens
	queue<int> toVisit; //all children to visit if they are parents
	vector<bool> hasVisited; //all nodes that have been visited

	for (unordered_map<int, list<int>>::iterator i = parentToChildMap.begin(); i != parentToChildMap.end(); ++i) {
		currParent = (*i).first;
		list<int> currChildren = (*i).second;
		hasVisited.clear();
		hasVisited.resize(10000, false);
		for (std::list<int>::iterator it = currChildren.begin(); it != currChildren.end(); ++it) {
			toVisit.push(*it);
			hasVisited[*it] = true;
		}

		while (!toVisit.empty()) {
			int currChild = toVisit.front();
			toVisit.pop();
			childrenList.push_back(currChild);

			//if the currChild is a parent
			if (parentToChildMap.find(currChild) != parentToChildMap.end()) {
				for (std::list<int>::iterator it2 = parentToChildMap[currChild].begin();
					it2 != parentToChildMap[currChild].end(); ++it2) {
					toVisit.push(*it2);
					hasVisited[*it2] = true;
				}
			}
		}

		parentToChildStarMap[currParent] = childrenList;
		currChildren.clear();
		childrenList.clear();
		hasVisited.clear();
	}

	return parentToChildStarMap;
}

unordered_map<int, list<int>> DesignExtractor::computeChildToParentStarTable(ChildToParentTable childToParentTable) {
	unordered_map<int, list<int>> childToParentStarMap;
	unordered_map<int, int> childToParentMap = childToParentTable.getTable();

	for (std::unordered_map<int, int>::iterator it = childToParentMap.begin(); it != childToParentMap.end(); ++it) {
		int currChild = (*it).first;
		int currParent = (*it).second;
		list<int> parentList;
		queue<int> toVisit;
		toVisit.push(currParent);

		while (!toVisit.empty()) {
			currParent = toVisit.front();
			toVisit.pop();
			parentList.push_back(currParent);
			if (childToParentMap.find(currParent) != childToParentMap.end()) {
				toVisit.push(childToParentMap[currParent]);
			}
		}

		childToParentStarMap[currChild] = parentList;
		parentList.clear();
	}

	return childToParentStarMap;
}

unordered_map<int, list<int>> DesignExtractor::computeFollowsStarAfterTable(FollowsTable followsTable) {
	unordered_map<int, pair<int, int>> followsMap = followsTable.getMap();
	unordered_map<int, list<int>> followsStarAfterMap;
	list<int> afterList;
	queue<int> toVisit;

	for (std::unordered_map<int, pair<int, int>>::iterator it = followsMap.begin(); it != followsMap.end(); ++it) {
		int currStmt = (*it).first;
		pair<int, int> followsPair = (*it).second;
		int stmtAfter = followsPair.second;

		if (stmtAfter != 0) {
			toVisit.push(stmtAfter);
		}

		while (!toVisit.empty()) {
			stmtAfter = toVisit.front(); // the first statement that is inside
			toVisit.pop();
			afterList.push_back(stmtAfter);
			if (followsTable.hasAfter(stmtAfter)) {
				stmtAfter = followsTable.getStmtAft(stmtAfter);
				toVisit.push(stmtAfter);
			}
		}

		followsStarAfterMap[currStmt] = afterList;
		afterList.clear();
	}

	return followsStarAfterMap;
}

unordered_map<int, list<int>> DesignExtractor::computeFollowsStarBeforeTable(FollowsTable followsTable) {
	unordered_map<int, pair<int, int>> followsMap = followsTable.getMap();
	unordered_map<int, list<int>> followsStarBeforeMap;
	list<int> beforeList;
	queue<int> toVisit;

	for (std::unordered_map<int, pair<int, int>>::iterator it = followsMap.begin(); it != followsMap.end(); ++it) {
		int currStmt = (*it).first;
		pair<int, int> followsPair = (*it).second;
		int stmtBefore = followsPair.first;

		if (stmtBefore != 0) {
			toVisit.push(stmtBefore);
		}

		while (!toVisit.empty()) {
			stmtBefore = toVisit.front(); // the first statement that is inside
			toVisit.pop();
			beforeList.push_back(stmtBefore);
			if (followsTable.hasBefore(stmtBefore)) {
				stmtBefore = followsTable.getStmtBef(stmtBefore);
				toVisit.push(stmtBefore);
			}
		}

		followsStarBeforeMap[currStmt] = beforeList;
		beforeList.clear();
	}

	return followsStarBeforeMap;
}

pair<unordered_map<int, list<int>>, unordered_map<int, list<int>>> DesignExtractor::computeCallsStarTable(CallsTable callsTable) {
	unordered_map<int, list<int>> callsStarMap;
	unordered_map<int, list<int>> callsMap = callsTable.getTable();
	unordered_map<int, list<int>> callsStarMapReverse;
	unordered_map<int, list<int>> callsMapReverse = callsTable.getTableReverse();

	int currCaller;
	list<int> calleeList; //all children&grandchildrens
	queue<int> toVisit; //all children to visit if they are parents
	vector<bool> hasVisited; //all nodes that have been visited

	for (unordered_map<int, list<int>>::iterator i = callsMap.begin(); i != callsMap.end(); ++i) {
		currCaller = (*i).first;
		list<int> currCallees = (*i).second;
		hasVisited.clear();
		hasVisited.resize(10000, false);
		for (std::list<int>::iterator it = currCallees.begin(); it != currCallees.end(); ++it) {
			toVisit.push(*it);
			hasVisited[*it] = true;
		}

		while (!toVisit.empty()) {
			int currCallee = toVisit.front();
			toVisit.pop();
			calleeList.push_back(currCallee);

			//if the currChild is a parent
			if (callsMap.find(currCallee) != callsMap.end()) {
				for (std::list<int>::iterator it2 = callsMap[currCallee].begin();
					it2 != callsMap[currCallee].end(); ++it2) {
					if (!hasVisited[*it2]) {
						toVisit.push(*it2);
						hasVisited[*it2] = true;
					}
				}
			}
		}

		callsStarMap[currCaller] = calleeList;
		currCallees.clear();
		calleeList.clear();
		hasVisited.clear();
	}

	int currCallee;
	list<int> callerList;

	for (unordered_map<int, list<int>>::iterator i = callsMapReverse.begin(); i != callsMapReverse.end(); ++i) {
		currCallee = (*i).first;
		list<int> currCallers = (*i).second;
		hasVisited.clear();
		hasVisited.resize(10000, false);
		for (std::list<int>::iterator it = currCallers.begin(); it != currCallers.end(); ++it) {
			toVisit.push(*it);
			hasVisited[*it] = true;
		}

		while (!toVisit.empty()) {
			int currCaller = toVisit.front();
			toVisit.pop();
			callerList.push_back(currCaller);

			//if the currChild is a parent
			if (callsMapReverse.find(currCaller) != callsMapReverse.end()) {
				for (std::list<int>::iterator it2 = callsMapReverse[currCaller].begin();
					it2 != callsMapReverse[currCaller].end(); ++it2) {
					if (!hasVisited[*it2]) {
						toVisit.push(*it2);
						hasVisited[*it2] = true;
					}
				}
			}
		}

		callsStarMapReverse[currCallee] = callerList;
		currCallers.clear();
		callerList.clear();
		hasVisited.clear();
	}


	return make_pair(callsStarMap, callsStarMapReverse);
}

unordered_map<int, pair<int, int>> DesignExtractor::computeFollowsTable(unordered_map<int, int> followsBefore, unordered_map<int, int> followsAfter) {
	unordered_map<int, pair<int, int>> followsMap;
	for (std::unordered_map<int, int>::iterator it = followsBefore.begin(); it != followsBefore.end(); ++it) {
		int currStmt = (*it).first;
		int befStmt = (*it).second;
		if (followsAfter.find(currStmt) != followsAfter.end()) {
			int aftStmt = followsAfter[currStmt];
			followsMap[currStmt] = make_pair(befStmt, aftStmt);
		}
		else {
			followsMap[currStmt] = make_pair(befStmt, 0);
		}
	}

	return followsMap;
}

// TODO 1 implement postorder
unordered_map<int, list<int>> DesignExtractor::computeUsesTable(UsesTableProcToVar usesTable, CallsStarTable callsStarTable) {
	unordered_map<int, list<int>> usesMap = usesTable.getMap();
	unordered_map<int, list<int>> callsStarMap = callsStarTable.setCallsStarMap();
	//iterate all calls
	unordered_set<int> visited;
	for (std::unordered_map<int, list<int>>::iterator it = callsStarMap.begin(); it != callsStarMap.end(); ++it) {
		int currCaller = (*it).first;
		list<int> calleeStar = (*it).second;
		for (int it2 : calleeStar) {
			if (visited.find(it2) != visited.end()) {

			}
		}
	}
	return usesMap;
}
// TODO 1 void DesignExtractor::dfsWalk()