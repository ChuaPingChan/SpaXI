#include "ResultFactory.h"


ResultFactory::ResultFactory()
{
}


ResultFactory::~ResultFactory()
{
}

ClauseResult ResultFactory::makeClauseResult(ClauseObject clause)
{
	ClauseObject::TYPE clauseType = clause.getClauseType();

	switch (clauseType)
	{
	case (ClauseObject::SELECT):
		//SelectionEvaluator evaluator;
		break;

	case (ClauseObject::REL):
		break;

	case (ClauseObject::PATTERN):
		break;

	case (ClauseObject::WITH):
		break;
	}
}
