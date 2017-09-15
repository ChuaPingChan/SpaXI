#include "QueryEvaluator.h"



QueryEvaluator::QueryEvaluator()
{
}


QueryEvaluator::~QueryEvaluator()
{
}

void QueryEvaluator::evaluate()
{
}

void QueryEvaluator::evaluateFollows(array<string, 4> arr)
{

	if (arr[0] == "int" && arr[2] == "int")
	{
        //hasResult = isFollows(arr[1], arr[1]);
	}
	else if (arr[0] == "int" && arr[2] == "_")
	{
        //hasResult = isBeingFollowed(arr[1]);
	}
	else if (arr[0] == "int" && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while")) 
	{
        //getAfter(arr[0], arr[2]);
	}
	else if (arr[0] == "_" && arr[2] == "int")
	{ 
        //hasResult = isBeingFollowedBy(arr[3]);
	}
	else if (arr[0] == "_" && arr[2] == "_")
	{
        //hasResult = hasFollows();
	}
	else if (arr[0] == "_" && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
	{
        //isFollowedBy(arr[2]);
	}
	else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && arr[2] == "int")
	{
        //isFollowedBy(arr[0], arr[2]);
	}
	else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && arr[2] == "_")
	{
        //getAfter(arr[0], arr[2]);
	}
	else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
	{
        //getFollows(arr[0], arr[2];)
	}
}

void QueryEvaluator::evaluateFollowsT(array<string, 4> arr)
{
    if (arr[0] == "int" && arr[2] == "int")
    {
        //hasResult = isFollowsT(arr[1], arr[1]);
    }
    else if (arr[0] == "int" && arr[2] == "_")
    {
        //hasResult = isBeingFollowedT(arr[1]);
    }
    else if (arr[0] == "int" && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
    {
        //getAfterStar(arr[0], arr[2]);
    }
    else if (arr[0] == "_" && arr[2] == "int")
    {
        //hasResult = isBeingFollowedByStar(arr[3]);
    }
    else if (arr[0] == "_" && arr[2] == "_")
    {
        //hasResult = hasFollowsT();
    }
    else if (arr[0] == "_" && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
    {
        //isFollowedStarBy(arr[2]);
    }
    else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && arr[2] == "int")
    {
        //isFollowedBy(arr[0], arr[2]);
    }
    else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && arr[2] == "_")
    {
        //getAfter(arr[0], arr[2]);
    }
    else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
    {
        //getFollows(arr[0], arr[2];)
    }
}

void QueryEvaluator::evaluateParent(array<string, 4> arr)
{
	if (arr[0] == "int" && arr[2] == "int")
	{
        //hasResult = isParent(arr[0], arr[2]);
	}
	else if (arr[0] == "int" && arr[2] == "_")
	{
        //hasResult = isParent(arr[2]);
	}
    else if (arr[0] == "int" && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
	{
        //getChildren(arr[0], arr[2]);
	}
	else if (arr[0] == "_" && arr[2] == "int")
	{
        //hasResult = isChildren(arr[2]);
	}
	else if (arr[0] == "_" && arr[2] == "_")
	{
        //hasResult = hasParent();
	}
    else if (arr[0] == "_" && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
	{
        //isParentOf(arr[2]);
	}
    else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && arr[2] == "int")
	{
        //isParentOf(arr[0], arr[2]);
	}
    else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && arr[2] == "_")
	{
        //getChildren(arr[0]);
	}
    else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
	{
        //getParent(arr[0], arr[2]);
	}
}

void QueryEvaluator::evaluateParentT(array<string, 4> arr)
{
    if (arr[0] == "int" && arr[2] == "int")
    {

    }
    else if (arr[0] == "int" && arr[2] == "_")
    {

    }
    else if (arr[0] == "int" && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
    {

    }
    else if (arr[0] == "_" && arr[2] == "int")
    {

    }
    else if (arr[0] == "_" && arr[2] == "_")
    {

    }
    else if (arr[0] == "_" && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
    {

    }
    else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && arr[2] == "int")
    {

    }
    else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && arr[2] == "_")
    {

    }
    else if ((arr[0] == "stmt" || arr[0] == "assign" || arr[0] == "while") && (arr[2] == "stmt" || arr[2] == "assign" || arr[2] == "while"))
    {

    }
}

void QueryEvaluator::evaluateUses(array<string, 4> arr)
{
	if (arr[0] == "int" && arr[2] == "int")
	{

	}
	else if (arr[0] == "int" && arr[2] == "_")
	{

	}
	else if (arr[0] == "int" && arr[2] == "")
	{

	}
	else if (arr[0] == "" && arr[2] == "int")
	{

	}
	else if (arr[0] == "" && arr[2] == "_")
	{

	}
	else if (arr[0] == "" && arr[2] == "")
	{

	}
}

void QueryEvaluator::evaluateModifies(array<string, 4> arr)
{

}

void QueryEvaluator::evaluatePattern(array<string, 6> arr)
{
    if (arr[2] == "var" && arr[4] == "_")
    {
        //resultPattern = getVariables(assign,variable);
    }
    else if (arr[2] == "var" && arr[4] == "ident")
    {
        //resultPattern = getVariables(assign,variable);
    }
    else if (arr[2] == "_" && arr[4] == "ident")
    {
        // get List of statements in List<string> assignments
        //resultPattern = <<list<string> assignments, leave blank
    }
    else if (arr[2] == "ident" && arr[4] == "ident")
    {
        //resultPattern = hasPartialBothMatches(arr[3],arr[5])
    }
    else if (arr[2] == "_" && arr[4] == "_")
    {
        //resultPattern = getAssignments();
    }
    else if (arr[2] == "ident" && arr[4] == "_")
    {
        //resultPattern = getAssignments();
    }

}
