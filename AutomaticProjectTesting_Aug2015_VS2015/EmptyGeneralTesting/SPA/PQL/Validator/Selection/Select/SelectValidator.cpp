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
        try 
        {
            Entity entity = getEntityOfSynonym(selectedStr);
            SelectClause sc = makeSelectClause(SELECT_SINGLE, entity, selectedStr);
            storeInQueryTree(sc);
            return true;
        }
        catch (SynonymNotFoundException& snfe) 
        {
            return false;
        }
        
    }

    else if (RegexValidators::isValidAttrRefRegex(selectedStr))
    {

        if (isValidAttrRefForSynonym(selectedStr))
        {
            string synonym = splitSynonymProcName(selectedStr).at(0); //get synonym
            bool hasProcName = (splitSynonymProcName(selectedStr).at(1) == RegexValidators::PROCNAME_STRING); //check if attribute is procName
            Entity entity = getEntityOfSynonym(synonym);
            SelectClause sc = makeSelectClause(SELECT_SINGLE, entity, synonym);

            //in case the attribute selected is procName and the entity is call, we change the flag for CallsSingleSynonym in SelectClause to true
            if (hasProcName && entity == CALL)
            {
                sc.isAttributeProcName = true;
            }

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
        vector<string> extractedSynonyms;
        vector<bool> flagForCallProcName;

        vector<string> synonymList;
        vector<Entity> entityList;

        string formattedStr = removeSpecialCharactersFromTuple(selectedStr); //remove <,> and comma(,)
        extractedSynonyms = extractSynonymsFromTuple(formattedStr); //extract synonyms from tuple arguments

        for (string s : extractedSynonyms)
        {
            if (RegexValidators::isValidSynonymRegex(s))
            {
                try
                {
                    Entity entity = getEntityOfSynonym(s);
                    synonymList.push_back(s);
                    entityList.push_back(entity);
                    flagForCallProcName.push_back(false);
                }
                catch (SynonymNotFoundException& snfe)
                {
                    cerr << snfe.what() << endl;
                    return false;
                }
            }

            else if (RegexValidators::isValidAttrRefRegex(s))
            {

                if (isValidAttrRefForSynonym(s))
                {
                    string synonym = splitSynonymProcName(s).at(0); //get synonym
                    bool hasProcName = (splitSynonymProcName(s).at(1)==RegexValidators::PROCNAME_STRING); //check if attribute is procName
                    Entity entity = getEntityOfSynonym(synonym);
                    synonymList.push_back(synonym);
                    entityList.push_back(entity);
                    //in case the attribute selected is procName and the entity is call, we change the flag for CallsSingleSynonym in SelectClause to true
                    if (hasProcName && entity == CALL)
                    {
                        flagForCallProcName.push_back(true);
                    }
                    else
                    {
                        flagForCallProcName.push_back(false);

                    }
                }
                else
                {
                    return false;
                }
            }
        }

        SelectClause sc = makeSelectClause(SELECT_TUPLE, entityList, synonymList);
        sc.isAttributeProcNameForTuple = flagForCallProcName;
        storeInQueryTree(sc);
        return true;

    }
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
        throw SynonymNotFoundException("Inside SelectValidator.getEntityOfSynonym(syn). Synonym Not Found in QueryTree and Entity cannot be assigned. Input String: " + syn);
    }
}

bool SelectValidator::isValidAttrRefForSynonym(string str)
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
        cerr << snfe.what() << endl;
        return false;
    }

    switch (entity) 
    {
    case PROCEDURE: return isProcNameAttribute(attribute);
    case STMT: return isStmtNumAttribute(attribute);
    case ASSIGN: return isStmtNumAttribute(attribute);
    case WHILE: return isStmtNumAttribute(attribute);
    case IF: return isStmtNumAttribute(attribute);
    case VARIABLE: return isVarNameAttribute(attribute);
    case CONSTANT: return isValueAttribute(attribute);
    case CALL: return isStmtNumAttribute(attribute) || isProcNameAttribute(attribute);
    
    default: return false;
    }

    return true;
}


bool SelectValidator::isProcNameAttribute(string attribute)
{
    return(attribute == RegexValidators::PROCNAME_STRING);
}

bool SelectValidator::isStmtNumAttribute(string attribute)
{
    return(attribute == RegexValidators::STMTNUM_STRING);
}

bool SelectValidator::isVarNameAttribute(string attribute)
{
    return(attribute == RegexValidators::VARNAME_STRING);
}

bool SelectValidator::isValueAttribute(string attribute)
{
    return(attribute == RegexValidators::VALUE_STRING);
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

vector<string> SelectValidator::splitSynonymProcName(string selectedStr)
{
    vector<string> synonymWithProcName;
    string synonymWithAttribute = selectedStr;
    synonymWithAttribute.erase(std::remove(synonymWithAttribute.begin(), synonymWithAttribute.end(), ' '), synonymWithAttribute.end()); //remove all whitespaces
    string synonym = Formatter::getStringBeforeDelim(synonymWithAttribute, ".");
    string attribute = Formatter::getStringAfterDelim(synonymWithAttribute, ".");
    
    synonymWithProcName.push_back(synonym); //store synonym at position 0
    synonymWithProcName.push_back(attribute); //store attribute at position 1

    return synonymWithProcName;
}

vector<string> SelectValidator::extractSynonymsFromTuple(string formattedStr)
{
    vector<string> synonyms;

    char delimiter = ','; //delimit characters using ,     
    stringstream ss(formattedStr);
    string arguments;
    while (getline(ss, arguments, delimiter))
    {
        synonyms.push_back(arguments);
    }
    return synonyms;
}
