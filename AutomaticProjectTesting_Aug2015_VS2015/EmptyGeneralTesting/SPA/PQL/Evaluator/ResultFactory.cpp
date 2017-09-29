#include "ResultFactory.h"


ResultFactory::ResultFactory()
{
}

ResultFactory::ResultFactory(QueryTree* qtPtr)
{
	this->_qt = qtPtr;
}


ResultFactory::~ResultFactory()
{
}
