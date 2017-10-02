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
        int entity = getENTITYOfSynonym(selectedStr);
        if (entity == UNKNOWN)
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

SelectClause SelectValidator::makeSelectClause(int selectionType)
{
    return SelectClause(selectionType);
}

SelectClause SelectValidator::makeSelectClause(int selectionType, int singleArgType, string singleArg)
{
    return SelectClause(selectionType, singleArgType, singleArg);
}

SelectClause SelectValidator::makeSelectClause(int selectionType, vector<int> tupleArgTypes, vector<string> tupleArgs)
{
    return SelectClause(selectionType, tupleArgTypes, tupleArgs);
}

bool SelectValidator::storeInQueryTree(SelectClause sc)
{
    return false;
}

int SelectValidator::getENTITYOfSynonym(string syn)
{
    if (qtPtr->isENTITYSynonymExist(syn, STMT))
    {
        return STMT;
    }
    else if (qtPtr->isENTITYSynonymExist(syn, ASSIGN)) {
        return ASSIGN;
    }
    else if (qtPtr->isENTITYSynonymExist(syn, WHILE)) {
        return WHILE;
    }
    else if (qtPtr->isENTITYSynonymExist(syn, IF)) {
        return IF;
    }
    else if (qtPtr->isENTITYSynonymExist(syn, PROG_LINE)) {
        return PROG_LINE;
    }
    else if (qtPtr->isENTITYSynonymExist(syn, CALL)) {
        return CALL;
    }
    else if (qtPtr->isENTITYSynonymExist(syn, PROCEDURE)) {
        return PROCEDURE;
    }
    else if (qtPtr->isENTITYSynonymExist(syn, VARIABLE)) {
        return VARIABLE;
    }
    else if (qtPtr->isENTITYSynonymExist(syn, CONSTANT)) {
        return CONSTANT;
    }
    else if (qtPtr->isENTITYSynonymExist(syn, STMTLIST)) {
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
