#include <DesignExtractor.h>

using namespace std;

DesignExtractor::DesignExtractor() {
}

unordered_map<int, list<int>> DesignExtractor::computeParentToChildStarTable(ParentToChildTable parentToChildTable) {
	unordered_map<int, list<int>> parentToChildStarMap;
	unordered_map<int, list<int>> parentToChildMap = parentToChildTable.getTable();

	for (auto i : parentToChildMap) {

	}

	return parentToChildStarMap;
}

unordered_map<int, list<int>> DesignExtractor::computeChildToParentStarTable(ChildToParentTable childToParentTable) {
	unordered_map<int, list<int>> test;
	return test;
}