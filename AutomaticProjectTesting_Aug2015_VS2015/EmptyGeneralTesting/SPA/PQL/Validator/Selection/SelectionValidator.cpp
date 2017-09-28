#include "SelectionValidator.h"

SelectionValidator::SelectionValidator(QueryTree *qtPtrNew) {
    setQueryTree(qtPtrNew);
}

SelectionValidator::~SelectionValidator() {}

bool SelectionValidator::isValidSelection(string str) {
    return false;
}

bool SelectionValidator::setQueryTree(QueryTree *qtPtrNew) {
    this->qtPtr = qtPtrNew;
    return true;
}
