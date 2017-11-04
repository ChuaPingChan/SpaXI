#include "UnrecognisedTypeException.h"

const string UnrecognisedTypeException::UNRECOGNISED_TYPE = "Unrecognised Type: ";

UnrecognisedTypeException::UnrecognisedTypeException()
{
}

UnrecognisedTypeException::UnrecognisedTypeException(const string & message)
{
    string errorMsg = UNRECOGNISED_TYPE + message;
    this->msg = errorMsg;
}


UnrecognisedTypeException::~UnrecognisedTypeException()
{
}

const char * UnrecognisedTypeException::what() const throw()
{
    return msg.c_str();
}
