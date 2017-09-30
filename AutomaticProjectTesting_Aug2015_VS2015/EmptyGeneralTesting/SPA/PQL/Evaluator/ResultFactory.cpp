#include "ResultFactory.h"


ResultFactory::ResultFactory()
{
}


ResultFactory::~ResultFactory()
{
}

ClauseResult ResultFactory::makeClauseResult(SelectClause clause)
{
	return ClauseResult();
}

ClauseResult ResultFactory::makeClauseResult(SuchThatClause clause)
{
	int rel = clause.getRel();

	if (rel == MODIFIES)
	{
		ModifiesEvaluator evaluator = ModifiesEvaluator();
		return evaluator.evaluate(clause);
	}

	else if (rel == USES)
	{
		UsesEvaluator evaluator = UsesEvaluator();
		return evaluator.evaluate(clause);
	}

	else if (rel == PARENT)
	{
		ParentEvaluator evaluator = ParentEvaluator();
		return evaluator.evaluate(clause);
	}

	else if (rel == PARENTSTAR)
	{
		ParentStarEvaluator evaluator = ParentStarEvaluator();
		return evaluator.evaluate(clause);
	}

	else if (rel == FOLLOWS)
	{
		FollowsEvaluator evaluator = FollowsEvaluator();
		return evaluator.evaluate(clause);
	}

	else if (rel == FOLLOWSSTAR)
	{
		FollowsStarEvaluator evaluator = FollowsStarEvaluator();
		return evaluator.evaluate(clause);
	}

	//else if (rel == CALLS)
	//{
	//	CallsEvaluator evaluator = CallsEvaluator();
	//	return evaluator.evaluate(clause);
	//}

	//else if (rel == CALLSSTAR)
	//{
	//	CallsStarEvaluator evaluator = CallsStarEvaluator();
	//	return evaluator.evaluate(clause);
	//}

	else if (rel == NEXT)
	{
		NextEvaluator evaluator = NextEvaluator();
		return evaluator.evaluate(clause);
	}

	else if (rel == NEXTSTAR)
	{
		NextStarEvaluator evaluator = NextStarEvaluator();
		return evaluator.evaluate(clause);
	}

	else if (rel == AFFECTS)
	{
		AffectsEvaluator evaluator = AffectsEvaluator();
		return evaluator.evaluate(clause);
	}

	else if (rel == AFFECTSSTAR)
	{
		AffectsStarEvaluator evaluator = AffectsStarEvaluator();
		return evaluator.evaluate(clause);
	}

	else
	{

	}
}

ClauseResult ResultFactory::makeClauseResult(PatternClause clause)
{
	return ClauseResult();
}
