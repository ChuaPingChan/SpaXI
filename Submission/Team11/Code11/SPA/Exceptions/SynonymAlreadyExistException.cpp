#include "SynonymAlreadyExistException.h"

const string SynonymAlreadyExistException::SYNONYM_ALREADY_EXIST = "Synonym already exist.";

SynonymAlreadyExistException::SynonymAlreadyExistException()
{
    this->msg = SYNONYM_ALREADY_EXIST;
}

SynonymAlreadyExistException::SynonymAlreadyExistException(const string & message)
{
    string errorMsg = SYNONYM_ALREADY_EXIST + " " + message;
    this->msg = errorMsg;
}


SynonymAlreadyExistException::~SynonymAlreadyExistException()
{
}

const char * SynonymAlreadyExistException::what() const throw()
{
    return msg.c_str();
}
