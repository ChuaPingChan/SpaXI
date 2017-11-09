#pragma once

#include <unordered_set>
#include "Entity.h"

using namespace std;

bool entityIsSynonym(Entity entity) {
    static unordered_set<Entity> synonymEntities({
        Entity::STMT,
        Entity::ASSIGN,
        Entity::WHILE,
        Entity::IF,
        Entity::PROG_LINE,
        Entity::CALL,
        Entity::PROCEDURE,
        Entity::VARIABLE,
        Entity::CONSTANT,
        Entity::STMTLIST
    });

    return (synonymEntities.find(entity)) != synonymEntities.end();
}
