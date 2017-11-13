#pragma once
#include <string>
#include <unordered_map>

using namespace std;

enum Relationship
{
    MODIFIES = 1,
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

static const unordered_map<string, Relationship> MAP_STR_TO_REL({
    {"Modifies", Relationship::MODIFIES},
    {"Uses", Relationship::USES},
    {"Parent", Relationship::PARENT},
    {"Parent*", Relationship::PARENTSTAR},
    {"Follows", Relationship::FOLLOWS},
    {"Follows*", Relationship::FOLLOWSSTAR},
    {"Calls", Relationship::CALLS},
    {"Calls*", Relationship::CALLSSTAR},
    {"Next", Relationship::NEXT},
    {"Next*", Relationship::NEXTSTAR},
    {"Affects", Relationship::AFFECTS},
    {"Affects*", Relationship::AFFECTSSTAR}
});

static const unordered_map<Relationship, string> MAP_REL_TO_STR({
    { Relationship::MODIFIES, "Modifies" },
    { Relationship::USES, "Uses" },
    { Relationship::PARENT, "Parent" },
    { Relationship::PARENTSTAR, "Parent*" },
    { Relationship::FOLLOWS, "Follows" },
    { Relationship::FOLLOWSSTAR, "Follows*" },
    { Relationship::CALLS, "Calls" },
    { Relationship::CALLSSTAR, "Calls*" },
    { Relationship::NEXT, "Next" },
    { Relationship::NEXTSTAR, "Next*" },
    { Relationship::AFFECTS, "Affects" },
    { Relationship::AFFECTSSTAR, "Affects*" }
});
