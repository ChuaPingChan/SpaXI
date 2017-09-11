#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

class ModTableVarToStmt {
public:
    ModTableVarToStmt();

private:
	unordered_map<int, pair<int, int>> followsTable;
};