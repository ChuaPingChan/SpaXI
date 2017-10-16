#include "SynonymNotFoundException.h"

const string SynonymNotFoundException::SYNONYM_NOT_FOUND = "Synonym not found.";

SynonymNotFoundException::SynonymNotFoundException()
{
    this->msg = SYNONYM_NOT_FOUND;
}

SynonymNotFoundException::SynonymNotFoundException(const string & message)
{
    string errorMsg = SYNONYM_NOT_FOUND + " " + message;
    this->msg = errorMsg;
}

SynonymNotFoundException::~SynonymNotFoundException()
{
}

const char * SynonymNotFoundException::what() const throw()
{
    return msg.c_str();
}
