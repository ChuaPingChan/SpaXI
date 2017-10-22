#include "EntityNotFoundException.h"

const string EntityNotFoundException::ENTITY_NOT_FOUND = "Entity not found.";

EntityNotFoundException::EntityNotFoundException()
{
    this->msg = ENTITY_NOT_FOUND;
}

EntityNotFoundException::EntityNotFoundException(const string & message)
{
    string errorMsg = ENTITY_NOT_FOUND + " " + message;
    this->msg = errorMsg;
}


EntityNotFoundException::~EntityNotFoundException()
{
}

const char * EntityNotFoundException::what() const throw()
{
    return msg.c_str();
}
