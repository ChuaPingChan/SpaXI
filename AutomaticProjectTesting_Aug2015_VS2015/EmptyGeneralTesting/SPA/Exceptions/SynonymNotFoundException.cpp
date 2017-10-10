#include "SynonymNotFoundException.h"

SynonymNotFoundException::SynonymNotFoundException()
{
}

SynonymNotFoundException::SynonymNotFoundException(string msg)
{
    this->msg = msg;
}

SynonymNotFoundException::~SynonymNotFoundException()
{
}
