#include "SelectionValidator.h"

SelectionValidator::SelectionValidator(QueryTreeStub *qtPtrNew) {
    setQueryTreeStub(qtPtrNew);
}

SelectionValidator::~SelectionValidator() {}

bool SelectionValidator::isValidSelection(string str) {
    return false;
}

bool SelectionValidator::setQueryTreeStub(QueryTreeStub *qtPtrNew) {
    this->qtPtr = qtPtrNew;
    return true;
}
