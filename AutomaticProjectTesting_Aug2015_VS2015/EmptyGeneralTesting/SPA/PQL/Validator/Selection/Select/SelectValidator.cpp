#include "SelectValidator.h"

using namespace std;

SelectValidator::SelectValidator(QueryTree* qtPtrNew)
{
    this->qtPtr = qtPtrNew;
}


SelectValidator::~SelectValidator()
{
}

bool SelectValidator::isValid(string str)
{
    string selectWithoutKeyword = removeSelectKeyword(str);
    string processedStr = Formatter::removeAllSpaces(selectWithoutKeyword);
    return isValidSelectBoolean(processedStr) || isValidSelectSingle(processedStr) || isValidSelectTuple(processedStr);
}

bool SelectValidator::isValidSelectBoolean(string selectedStr)
{
    return false;
}

bool SelectValidator::isValidSelectSingle(string selectedStr)
{
    if (RegexValidators::isValidSynonymRegex(selectedStr))
    {
        Entity entity = getEntityOfSynonym(selectedStr);
        if (!isKnownEntity(entity))
            return false;
        SelectClause sc = makeSelectClause(SELECT_SINGLE, entity, selectedStr);
        storeInQueryTree(sc);
        return true;
    }
    return false;
}

bool SelectValidator::isValidSelectTuple(string selectedStr)
{
    return false;
}

SelectClause SelectValidator::makeSelectClause(SelectionType selectionType)
{
    return SelectClause(selectionType);
}

SelectClause SelectValidator::makeSelectClause(SelectionType selectionType, Entity singleArgType, string singleArg)
{
    return SelectClause(selectionType, singleArgType, singleArg);
}

SelectClause SelectValidator::makeSelectClause(SelectionType selectionType, vector<Entity> tupleArgTypes, vector<string> tupleArgs)
{
    return SelectClause(selectionType, tupleArgTypes, tupleArgs);
}

bool SelectValidator::storeInQueryTree(SelectClause sc)
{
    return false;
}

Entity SelectValidator::getEntityOfSynonym(string syn)
{
    if (qtPtr->isEntitySynonymExist(syn, STMT))
    {
        return STMT;
    }
    else if (qtPtr->isEntitySynonymExist(syn, ASSIGN)) {
        return ASSIGN;
    }
    else if (qtPtr->isEntitySynonymExist(syn, WHILE)) {
        return WHILE;
    }
    else if (qtPtr->isEntitySynonymExist(syn, IF)) {
        return IF;
    }
    else if (qtPtr->isEntitySynonymExist(syn, PROG_LINE)) {
        return PROG_LINE;
    }
    else if (qtPtr->isEntitySynonymExist(syn, CALL)) {
        return CALL;
    }
    else if (qtPtr->isEntitySynonymExist(syn, PROCEDURE)) {
        return PROCEDURE;
    }
    else if (qtPtr->isEntitySynonymExist(syn, VARIABLE)) {
        return VARIABLE;
    }
    else if (qtPtr->isEntitySynonymExist(syn, CONSTANT)) {
        return CONSTANT;
    }
    else if (qtPtr->isEntitySynonymExist(syn, STMTLIST)) {
        return STMTLIST;
    }
    //TODO: Might need another type for UNKNOWN
    //return UNKNOWN;
}

bool SelectValidator::isKnownEntity(Entity entity)
{
    switch (entity) {
        case STMT:
        case ASSIGN:
        case WHILE:
        case IF:
        case PROG_LINE:
        case CALL:
        case PROCEDURE:
        case VARIABLE:
        case INTEGER:
        case UNDERSCORE:
        case IDENT_WITHQUOTES:
        case EXPRESSION_SPEC:
        case CONSTANT:
        case STMTLIST:
            return true;
        default:
            return false;
    }
}

string SelectValidator::removeSelectKeyword(string str)
{
    size_t f = str.find("Select");
    str.replace(f, std::string("Select").length(), "");
    return str;
}
