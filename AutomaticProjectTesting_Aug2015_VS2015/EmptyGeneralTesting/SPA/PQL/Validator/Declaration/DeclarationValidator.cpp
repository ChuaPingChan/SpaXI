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
    else {
        throw EntityNotFoundException("Inside DeclarationValidator, when calling getEntityIndexReference()");
    }
}

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
            throw SynonymAlreadyExistException("In DeclarationValidator, when calling areValidSynonyms()");
        }
        else
        {
            return false;
        }
    }
    return "true";
}

bool DeclarationValidator::hasValidEntityAndSynonym(string str)
{
    smatch regexMatch;
    regex extraction("([a-zA-Z_]+)\\s+([^]*)");
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
