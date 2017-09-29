#include "DeclarationValidator.h"

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
            if (entity == synonym)
                return false;
            qtPtr->insertVariable(entity, synonym);
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

//TODO: Remove the content and call api from relation table
bool DeclarationValidator::isValidEntity(string str) {
    const string DESIGN_ENTITY_REGEX = "(procedure|stmtLst|stmt|assign|call|while|if|variable|constant|prog_line)";
    regex entityRegex(DESIGN_ENTITY_REGEX);
    return regex_match(str, entityRegex);
}

//TODO: Remove the content and call api from relation table
bool DeclarationValidator::isValidSynonym(string str) {
    const string LETTER = "([a-zA-Z])";
    const string DIGIT = "([0-9])";
    const string HASH = "(#)";
    const string IDENT = "(" + LETTER + "(" + LETTER + "|" + DIGIT + "|" + HASH + ")*)";
    const string SYNONYM = IDENT;
    regex synonymRegex(SYNONYM);
    return regex_match(str, synonymRegex);
}
