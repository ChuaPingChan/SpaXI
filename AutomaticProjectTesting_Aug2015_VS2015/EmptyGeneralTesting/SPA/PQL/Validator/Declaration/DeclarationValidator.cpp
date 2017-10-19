#include "DeclarationValidator.h"

using namespace std;

DeclarationValidator::DeclarationValidator(QueryTree *qtPtrNew) {
    setQueryTree(qtPtrNew);
}

DeclarationValidator::~DeclarationValidator() {}

bool DeclarationValidator::isValidDeclaration(string str) {
    string entity;
    string synonym;
    int numWord = 0;
    int numComma = 0;
    int expectedNumComma = 0;

    string EVERYTHING_EXCEPT_SPACE = "[^[:space:]]+";
    regex exceptSpaceRegex(EVERYTHING_EXCEPT_SPACE);
    sregex_iterator pos(str.cbegin(), str.cend(), exceptSpaceRegex);
    sregex_iterator end;

    int counter = 0;
    for (; pos != end; pos++) {
        string token = pos->str(0);

        if (counter == 0 && isValidEntity(token)) {
            numWord++;
            entity = token;
            counter++;
            continue;
        }
        else if (counter == 0 && !isValidEntity(token)) {
            return false;
        }

        if (token == ",") {
            numComma++;
            counter++;
            continue;
        }
        else if (token.back() == ',') {
            numComma++;
            regex removeCommaRegex("([[:w:]]+),");
            smatch m;
            regex_search(token, m, removeCommaRegex);
            string extracted = m[1].str();
            if (isValidSynonym(extracted)) {
                numWord++;
                synonym = extracted;
            }
            else {
                return false;
            }
        }
        else if (isValidSynonym(token)) {
            numWord++;
            synonym = token;
        }
        else {
            return false;
        }

        if (synonymBank.find(synonym) == synonymBank.end()) {
           synonymBank.insert(synonym);
            qtPtr->insertSynonym(getEntityIndexReference(entity), synonym);
        }
        else {
            return false;
        }

        counter++;
    }

    expectedNumComma = numWord - 2;

    return numComma == expectedNumComma;
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
