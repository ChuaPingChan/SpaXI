#include "ResultFactory.h"


ResultFactory::ResultFactory(ClauseResult clauseResult)
{
    this->_clauseResult = clauseResult;
}


ResultFactory::~ResultFactory()
{
}

//ClauseResult ResultFactory::makeClauseResult(SelectClause clause)
//{
//    SelectionEvaluator evaluator = SelectionEvaluator();
//    return evaluator.evaluate(clause);
//}

//ClauseResult ResultFactory::makeClauseResult(SuchThatClause clause)
//{
//    int rel = clause.getRel();
//    ClauseResult clauseResult;
//
//    if (rel == FOLLOWS)
//    {
//        FollowsEvaluator evaluator = FollowsEvaluator();
//        evaluator.evaluate(clause, &clauseResult);
//        return clauseResult;
//    }
//}

//    if (rel == MODIFIES)
//    {
//        ModifiesEvaluator evaluator = ModifiesEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else if (rel == USES)
//    {
//        UsesEvaluator evaluator = UsesEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else if (rel == PARENT)
//    {
//        ParentEvaluator evaluator = ParentEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else if (rel == PARENTSTAR)
//    {
//        ParentStarEvaluator evaluator = ParentStarEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else if (rel == FOLLOWS)
//    {
//        FollowsEvaluator evaluator = FollowsEvaluator();
//        evaluator.evaluate(clause);
//        return clauseResult;
//    }
//
//    else if (rel == FOLLOWSSTAR)
//    {
//        FollowsStarEvaluator evaluator = FollowsStarEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else if (rel == CALLS)
//    {
//        CallsEvaluator evaluator = CallsEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else if (rel == CALLSSTAR)
//    {
//        CallsStarEvaluator evaluator = CallsStarEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else if (rel == NEXT)
//    {
//        NextEvaluator evaluator = NextEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else if (rel == NEXTSTAR)
//    {
//        NextStarEvaluator evaluator = NextStarEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else if (rel == AFFECTS)
//    {
//        AffectsEvaluator evaluator = AffectsEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else if (rel == AFFECTSSTAR)
//    {
//        AffectsStarEvaluator evaluator = AffectsStarEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else
//    {
//        cerr << "Relationship: " << rel << " is not regconised!" << endl;
//    }
//    return ClauseResult();
//}

//ClauseResult ResultFactory::makeClauseResult(PatternClause clause)
//{
//    int patternType = clause.getPatternType();
//
//    if (patternType == ASSIGN)
//    {
//        AssignPatternEvaluator evaluator = AssignPatternEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else if (patternType == WHILE)
//    {
//        WhilePatternEvaluator evaluator = WhilePatternEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else if (patternType == IF)
//    {
//        IfPatternEvaluator evaluator = IfPatternEvaluator();
//        return evaluator.evaluate(clause);
//    }
//
//    else
//    {
//        cerr << "Pattern Type: " << patternType << " is not regconised!" << endl;
//    }
//    return ClauseResult();
//}