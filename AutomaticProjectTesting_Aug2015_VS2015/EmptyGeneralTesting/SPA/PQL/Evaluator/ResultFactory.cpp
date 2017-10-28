#include "ResultFactory.h"


ResultFactory::ResultFactory()
{
}


ResultFactory::~ResultFactory()
{
}

bool ResultFactory::processClause(SelectClause clause)
{
    SelectionEvaluator evaluator = SelectionEvaluator();
    return evaluator.evaluate(clause, &_clauseResult);
   
}

bool ResultFactory::processClause(SuchThatClause clause)
{
    Relationship rel = clause.getRel();

    if (rel == FOLLOWS)
    {
        FollowsEvaluator evaluator = FollowsEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (rel == FOLLOWSSTAR)
    {
        FollowsStarEvaluator evaluator = FollowsStarEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (rel == PARENT)
    {
        ParentEvaluator evaluator = ParentEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (rel == PARENTSTAR)
    {
        ParentStarEvaluator evaluator = ParentStarEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (rel == MODIFIES)
    {
        ModifiesEvaluator evaluator = ModifiesEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (rel == USES)
    {
        UsesEvaluator evaluator = UsesEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (rel == NEXT)
    {
        NextEvaluator evaluator = NextEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (rel == NEXTSTAR)
    {
        NextStarEvaluator evaluator = NextStarEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (rel == CALLS)
    {
        CallsEvaluator evaluator = CallsEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (rel == CALLSSTAR)
    {
        CallsStarEvaluator evaluator = CallsStarEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (rel == AFFECTS)
    {
        AffectsEvaluator evaluator = AffectsEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (rel == AFFECTSSTAR)
    {
        AffectsStarEvaluator evaluator = AffectsStarEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else
    {
        return false;
    }
}

bool ResultFactory::processClause(PatternClause clause)
{
    PatternType patternType = clause.getPatternType();
    
    if (patternType == ASSIGN_PATTERN)
    {
        AssignPatternEvaluator evaluator = AssignPatternEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }


    if (patternType == WHILE_PATTERN)
    {
        WhilePatternEvaluator evaluator = WhilePatternEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (patternType == IF_PATTERN)
    {
        IfPatternEvaluator evaluator = IfPatternEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }
}

bool ResultFactory::processClause(WithClause clause)
{
    WithType withType = clause.getWithType();

    if (withType == INTEGER_WITH)
    {
        IntWithEvaluator evaluator = IntWithEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }

    else if (withType == STRING_WITH)
    {
        StringWithEvaluator evaluator = StringWithEvaluator();
        return evaluator.evaluate(clause, &_clauseResult);
    }
}

ClauseResult ResultFactory::makeClauseResult()
{
    return _clauseResult;
}