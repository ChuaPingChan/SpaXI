#include "QueryValidator.h"

QueryValidator::QueryValidator(QueryTree *qtNew) {
    this->qtPtr = qtNew;
    dv.setQueryTree(this->qtPtr);
    sv.setQueryTree(this->qtPtr);
}

QueryValidator::~QueryValidator() {}

bool QueryValidator::isValidQuery(string query) {
    vector<string> inputVector = tokenize(query);

    for (vector<string>::iterator iter = inputVector.begin(); iter != inputVector.end(); ++iter) {
        string currentLine = *iter;
        if (currentLine == inputVector.back()) {
            if (!isValidSelection(currentLine)) {
                return false;
            }
        }
        else {
            if (!isValidDeclaration(currentLine)) {
                return false;
            }
        }
    }

    return true;
}

bool QueryValidator::isValidDeclaration(string str) {
    return dv.isValidDeclaration(str);
}

bool QueryValidator::isValidSelection(string str) {
    return sv.isValidSelection(str);
}

vector<string> QueryValidator::tokenize(string query) {
    char delimiter = ';';
    stringstream ss(query);
    vector<string> tokens;
    string arguments;

    while (getline(ss, arguments, delimiter)) {
        tokens.push_back(arguments);
    }
    return tokens;
}