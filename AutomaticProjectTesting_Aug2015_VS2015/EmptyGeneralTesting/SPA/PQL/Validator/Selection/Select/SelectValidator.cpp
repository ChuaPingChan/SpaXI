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
    string processedStr = Formatter::removeAllSpaces(processedStr);
    return isValidSelectSingle(processedStr) || isValidSelectBoolean(processedStr) || isValidSelectTuple(processedStr);
}

bool SelectValidator::isValidSelectSingle(string selectedStr)
{
    if (RegexValidators::isValidSynonymRegex(selectedStr))
    {
        int entity = getEntityOfSynonym(selectedStr);
        if (entity == UNKNOWN)
            return false;
 
        vector<int> argType(entity);
        vector<string> arg;
        arg.push_back(selectedStr);
        SelectClause sc = makeSelectClause(SELECT_SINGLE, argType, arg);
        storeInQueryTree(sc);
        return true;
    }
    return false;
}

bool SelectValidator::isValidSelectBoolean(string selectedStr)
{
    return false;
}

bool SelectValidator::isValidSelectTuple(string selectedStr)
{
    return false;
}

SelectClause SelectValidator::makeSelectClause(int selectionType, vector<int> argTypes, vector<string> args)
{
    return SelectClause(selectionType, argTypes, args);
}

SelectClause SelectValidator::makeSelectClause(int selectionType)
{
    return SelectClause(selectionType);
}

bool SelectValidator::storeInQueryTree(SelectClause sc)
{
    return false;
}

int SelectValidator::getEntityOfSynonym(string syn)
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
    return UNKNOWN;
}

string SelectValidator::removeSelectKeyword(string str)
{
    size_t f = str.find("Select");
    str.replace(f, std::string("Select").length(), "");
    return str;
}
