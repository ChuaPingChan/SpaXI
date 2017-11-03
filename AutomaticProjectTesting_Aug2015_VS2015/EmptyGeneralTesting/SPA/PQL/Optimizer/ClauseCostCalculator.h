#pragma once

#include <unordered_map>
#include "../Utilities/Clause.h"

using namespace std;

class ClauseCostCalculator
{
public:
    ClauseCostCalculator();

    static int getCost(ClausePtr clausePtr);

private:

    enum ClauseType
    {
        // TODO: Implement
    };

    unordered_map<ClauseCostCalculator::ClauseType, int> _costTable;
    
};

