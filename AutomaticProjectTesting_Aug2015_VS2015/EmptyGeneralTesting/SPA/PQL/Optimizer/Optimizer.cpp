#include "Optimizer.h"
#include "ClauseGroupsManager.h"
#include "../Utilities/ClauseWrapper.h"

Optimizer::Optimizer(const QueryTree &queryTree)
{
    // TODO: Implement
    /*
        1. Populates and initialises internal data structures
        2. Split clauses into groups
        3. Sort clauses within groups for efficient evaluation
        4. Sort clause groups for efficient evaluation
    */
    processQueryTree(queryTree);
}

/*
    Loops through all clauses in a query tree and updates the appropriate data
    structures in Optimizer.
*/
bool Optimizer::processQueryTree(const QueryTree &queryTree)
{
    // TODO: Implement
    return false;
}
