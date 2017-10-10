#include "AttributeNotFoundException.h"

const string AttributeNotFoundException::ATTRIBUTE_NOT_FOUND = "Attribute not found.";

AttributeNotFoundException::AttributeNotFoundException()
{
    this->msg = ATTRIBUTE_NOT_FOUND;
}

AttributeNotFoundException::AttributeNotFoundException(const string & message)
{
    string errorMsg = ATTRIBUTE_NOT_FOUND + " " + message;
    this->msg = errorMsg;
}

AttributeNotFoundException::~AttributeNotFoundException()
{
}

const char * AttributeNotFoundException::what() const throw()
{
    return msg.c_str();
}
