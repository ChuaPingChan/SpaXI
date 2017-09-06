#include "ParentToChildTable.h"

using namespace std;

ParentToChildTable::ParentToChildTable()
{
}

bool ParentToChildTable::addParentChild(int parentStmt, int childStmt) 
{
	if (parentToChildMap.find(parentStmt) == parentToChildMap.end()) {
		parentToChildMap[parentStmt] = list<int>();
		parentToChildMap[parentStmt].push_back(childStmt);
	}
	else {
		parentToChildMap[parentStmt].push_back(childStmt);
	}
	return true;
}

list<int> ParentToChildTable::getChildren(int parentStmt) {
	return parentToChildMap[parentStmt];
}