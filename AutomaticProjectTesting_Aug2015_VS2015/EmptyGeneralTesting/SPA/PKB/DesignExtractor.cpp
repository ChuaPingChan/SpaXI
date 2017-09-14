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