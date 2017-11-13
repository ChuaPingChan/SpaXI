#include "DeclarationValidator.h"

using namespace std;

DeclarationValidator::DeclarationValidator(QueryTree *qtPtrNew) {
    setQueryTree(qtPtrNew);
}

DeclarationValidator::~DeclarationValidator() {}

bool DeclarationValidator::isValidDeclaration(string str) {
    return RegexValidators::isValidDeclarationExtractedRegex(str) && hasValidEntityAndSynonym(str);
}

bool DeclarationValidator::setQueryTree(QueryTree *qtPtrNew) {
    this->qtPtr = qtPtrNew;
    return true;
}

/*
* Returns enum form of entity
* Throws EntityNotFoundException when string form cannot be mapped into its enum form
*/
Entity DeclarationValidator::getEntityIndexReference(string entity)
{
    if (RegexValidators::isValidStmtString(entity)) {
        return STMT;
    }
    else if (RegexValidators::isValidAssignString(entity)) {
        return ASSIGN;
    }
    else if (RegexValidators::isValidWhileString(entity)) {
        return WHILE;
    }
    else if (RegexValidators::isValidIfString(entity)) {
        return IF;
    }
    else if (RegexValidators::isValidProgLineString(entity)) {
        return PROG_LINE;
    }
    else if (RegexValidators::isValidCallString(entity)) {
        return CALL;
    }
    else if (RegexValidators::isValidProcedureString(entity)) {
        return PROCEDURE;
    }
    else if (RegexValidators::isValidVariableString(entity)) {
        return VARIABLE;
    }
    else if (RegexValidators::isValidConstantString(entity)) {
        return CONSTANT;
    }
    else if (RegexValidators::isValidStmtLstString(entity)) {
        return STMTLIST;
    }
    else {
        throw EntityNotFoundException("Inside DeclarationValidator.getEntityIndexReference(). Input Entity: " + entity);
    }
}

/*
* Pre-cond: entity is valid
* Returns true when all synonyms are valid and stored in the QueryTree
* Throws SynonymAlreadyExistException
*/
bool DeclarationValidator::areValidSynonyms(Entity entity, string str)
{
    regex synonymRegex(RegexValidators::SYNONYM_REGEX);
    sregex_iterator it(str.cbegin(), str.cend(), synonymRegex);
    sregex_iterator it_end;

    for (; it != it_end; it++)
    {
        string currentToken = it->str(0);
        if  (RegexValidators::isValidSynonymRegex(currentToken) && !isDeclaredSynonym(currentToken))
        {
            synonymBank.insert(currentToken);
            qtPtr->insertSynonym(entity, currentToken);
        }
        else if (isDeclaredSynonym(currentToken)) 
        {
            throw SynonymAlreadyExistException("In DeclarationValidator.areValidSynonyms(). Current Token: " + currentToken);
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool DeclarationValidator::hasValidEntityAndSynonym(string str)
{
    smatch regexMatch;
    regex extraction("([a-zA-Z_]+)\\s+([^]*)");     // Assumes the form of (entity) (synonym, synonym, ...)
    regex_search(str, regexMatch, extraction);

    try {
        string entityString = regexMatch.str(1);
        string synonymString = regexMatch.str(2);
        Entity entity = getEntityIndexReference(entityString);
        return areValidSynonyms(entity, synonymString);
    }
    catch (EntityNotFoundException enfe) {
        return false;
    }
    catch (SynonymAlreadyExistException saee) {
        return false;
    }
}

bool DeclarationValidator::isDeclaredSynonym(string synonym)
{
    return synonymBank.find(synonym) != synonymBank.end();
}
