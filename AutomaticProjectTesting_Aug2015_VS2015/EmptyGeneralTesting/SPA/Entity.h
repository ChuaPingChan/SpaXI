#pragma once

using namespace std;

enum Entity
{
    STMT = 0,
    ASSIGN,
    WHILE,
    IF,
    PROG_LINE,
    CALL,
    PROCEDURE,
    VARIABLE,
    INTEGER,
    UNDERSCORE,
    IDENT_WITHQUOTES,
    EXPRESSION_SPEC_PARTIAL,
    EXPRESSION_SPEC_EXACT,
    CONSTANT,
    STMTLIST
};

bool entityIsSynonym(Entity entity);
