#pragma once
#include <string>

using namespace std;

enum RELATIONSHIP
{
    MODIFIES = 0,
    USES,
    PARENT,
    PARENTSTAR,
    FOLLOWS,
    FOLLOWSSTAR,
    CALLS,
    CALLSSTAR,
    NEXT,
    NEXTSTAR,
    AFFECTS,
    AFFECTSSTAR
};

static const string RELATIONSHIP_STRING[] = { "Modifies",
                                            "Uses",
                                            "Parent",
                                            "Parent*",
                                            "Follows",
                                            "Follows*",
                                            "Calls",
                                            "Calls*",
                                            "Next",
                                            "Next*",
                                            "Affects",
                                            "Affects*" }