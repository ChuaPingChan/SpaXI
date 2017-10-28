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
    if (str.empty())
    {
        return false;
    }
    string selectWithoutKeyword = removeSelectKeyword(str);
    string processedStr = Formatter::removeAllSpacesAndTabs(selectWithoutKeyword);
    return isValidSelectBoolean(processedStr) || isValidSelectSingle(processedStr) || isValidSelectTuple(processedStr);
}

bool SelectValidator::isValidSelectBoolean(string selectedStr)
{
    if (RegexValidators::isValidBooleanRegex(selectedStr))
    {
        SelectClause sc = makeSelectClause(SELECT_BOOLEAN);
        storeInQueryTree(sc);
        return true;
    }
    return false;
}

bool SelectValidator::isValidSelectSingle(string selectedStr)
{
    if (RegexValidators::isValidSynonymRegex(selectedStr))
    {
        try {
            Entity entity = getEntityOfSynonym(selectedStr);
            SelectClause sc = makeSelectClause(SELECT_SINGLE, entity, selectedStr);
            storeInQueryTree(sc);
            return true;
        }
        catch (SynonymNotFoundException& snfe) {
            //TODO: Add to logging
            return false;
        }
        
    }

    else if (RegexValidators::isValidAttrRefRegex(selectedStr))
    {
        if (isValidAttrRefForSynonym(selectedStr))
        {
            Entity entity = getEntityOfSynonym(selectedStr);
            SelectClause sc = makeSelectClause(SELECT_SINGLE, entity, selectedStr);
            storeInQueryTree(sc);
            return true;
        }
    }
        return false;
}

bool SelectValidator::isValidSelectTuple(string selectedStr)
{
    if (RegexValidators::isValidTupleRegex(selectedStr))
    {
        vector<string> synonymList;
        vector<Entity> entityList;
        string formattedStr = removeSpecialCharactersFromTuple(selectedStr);
       
        char delimiter = ','; //delimit characters using ,     
        stringstream ss(formattedStr);
        string arguments;
        while (getline(ss, arguments, delimiter)) 
        {
            synonymList.push_back(arguments);
        }

        for (string s : synonymList)
        {
            if (RegexValidators::isValidSynonymRegex(s))
            {
                try {
                    Entity entity = getEntityOfSynonym(s);
                    entityList.push_back(entity);
                }
                catch (SynonymNotFoundException& snfe) {
                    //TODO: Add to logging
                    return false;
                }
            }

            else if (RegexValidators::isValidAttrRefRegex(s))
            {
                if (isValidAttrRefForSynonym(s))
                {
                    Entity entity = getEntityOfSynonym(s);
                    entityList.push_back(entity);
                }
            }
        }

        SelectClause sc = makeSelectClause(SELECT_TUPLE, entityList, synonymList);
        storeInQueryTree(sc);
        return true;

    }
    //TODO: Add support for AttrRef
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
    qtPtr->insertSelect(sc);
    return true;
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
    else {
        throw SynonymNotFoundException("Inside SelectValidator, when calling getEntityOfSynonym()");
    }
}

bool SelectValidator::isValidAttrRefForSynonym(string &str)
{
    string synonymWithAttribute = str;
    synonymWithAttribute.erase(std::remove(synonymWithAttribute.begin(), synonymWithAttribute.end(), ' '), synonymWithAttribute.end()); //remove all whitespaces
    string synonym = Formatter::getStringBeforeDelim(synonymWithAttribute, ".");
    string attribute = Formatter::getStringAfterDelim(synonymWithAttribute, ".");
    Entity entity;
    try {
         entity = getEntityOfSynonym(synonym);
         str = synonym;
    }
    catch (SynonymNotFoundException& snfe) {
        //TODO: Add to logging
        return false;
    }

    switch (entity) 
    {
    case PROCEDURE: return isProcNameAttribute(attribute);
    case STMT: return isStmtNumAttribute(attribute);
    case ASSIGN: return isStmtNumAttribute(attribute);
    case CALL: return isStmtNumAttribute(attribute) || isProcNameAttribute(attribute);
    case WHILE: return isStmtNumAttribute(attribute);
    case IF: return isStmtNumAttribute(attribute);
    case VARIABLE: return isVarNameAttribute(attribute);
    case CONSTANT: return isValueAttribute(attribute);
    default: return false;
    }
    return true;
}

bool SelectValidator::isProcNameAttribute(string attribute)
{
    string procName = "procName";
    return(attribute == procName);
}

bool SelectValidator::isStmtNumAttribute(string attribute)
{
    string stmtNum = "stmt#";
    return(attribute == stmtNum);
}

bool SelectValidator::isVarNameAttribute(string attribute)
{
    string varName = "varName";
    return(attribute == varName);
}

bool SelectValidator::isValueAttribute(string attribute)
{
    string value = "value";
    return(attribute == value);
}


string SelectValidator::removeSelectKeyword(string str)
{
    size_t f = str.find("Select");
    str.replace(f, std::string("Select").length(), "");
    return str;
}

string SelectValidator::removeSpecialCharactersFromTuple(string selectedStr)
{
    selectedStr.erase(std::remove(selectedStr.begin(), selectedStr.end(), '<'), selectedStr.end()); //remove < from tuple
    selectedStr.erase(std::remove(selectedStr.begin(), selectedStr.end(), '>'), selectedStr.end()); //remove > from tuple
    selectedStr.erase(std::remove(selectedStr.begin(), selectedStr.end(), ' '), selectedStr.end()); //remove all whitespaces for easier tokenizing

    return selectedStr;
}
