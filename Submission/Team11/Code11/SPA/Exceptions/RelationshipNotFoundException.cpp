#include "RelationshipNotFoundException.h"

const string RelationshipNotFoundException::RELATIONSHIP_NOT_FOUND = "Relationship not found.";

RelationshipNotFoundException::RelationshipNotFoundException()
{
    this->msg = RELATIONSHIP_NOT_FOUND;
}

RelationshipNotFoundException::RelationshipNotFoundException(const string & message)
{
    string errorMsg = RELATIONSHIP_NOT_FOUND + " " + message;
    this->msg = errorMsg;
}

RelationshipNotFoundException::~RelationshipNotFoundException()
{
}

const char * RelationshipNotFoundException::what() const throw()
{
    return msg.c_str();
}
