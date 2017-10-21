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

bool DeclarationValidator::isValidEntity(string str) {
    return RegexValidators::isValidEntityRegex(str);
}

bool DeclarationValidator::isValidSynonym(string str) {
    return RegexValidators::isValidSynonymRegex(str);
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
}

bool DeclarationValidator::hasValidEntityAndSynonym(string str)
{
    bool hasEntityDeclared = false;
    Entity currentEntity;

    regex declarationSubUnitRegex(RegexValidators::DESIGN_ENTITY_REGEX + "|" + RegexValidators::SYNONYM_REGEX);
    sregex_iterator it(str.cbegin(), str.cend(), declarationSubUnitRegex);
    sregex_iterator it_end;

    for (; it != it_end; it++)
    {
        string currentToken = it->str(0);
        if (RegexValidators::isValidEntityRegex(currentToken) && !hasEntityDeclared)
        {
            currentEntity = getEntityIndexReference(currentToken);
            hasEntityDeclared = true;
        }
        else if (RegexValidators::isValidSynonymRegex(currentToken) && !isDeclaredSynonym(currentToken))
        {
            synonymBank.insert(currentToken);
            qtPtr->insertSynonym(currentEntity, currentToken);
        }
        else
        {
            return false;
        }

    }
    return true;
}

bool DeclarationValidator::isDeclaredSynonym(string synonym)
{
    return synonymBank.find(synonym) != synonymBank.end();
}
