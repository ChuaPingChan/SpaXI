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
    string type1 = arr[0];
    string type2 = arr[2];
    string arg1 = arr[1];
    string arg2 = arr[3];

	if (type1 == "int" && type2 == "int")
	{
        //hasResult = isFollows(arg1, arg2);
	}
	else if (type1 == "int" && type2 == "_")
	{
        /*OK*/
        //hasResult = isBefore(stoi(arg1));
	}
	else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while")) 
	{
        /*OK*/
        //if (getAfter(stoi(arg1), arg2).empty()) {
        //    hasResult = false;
        //}
	}
	else if (type1 == "_" && type2 == "int")
	{ 
        //hasResult = isBeingFollowedBy(arg2);
	}
	else if (type1 == "_" && type2 == "_")
	{
        //hasResult = hasFollows();
	}
	else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        //if (isFollowedBy(arg2).empty()) {
        //    hasResult = false;
        //}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "int")
	{
        //if (isFollowedBy(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
	{
        //if (getAfter(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
	}
	else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        //if (getFollows(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
	}
}

void QueryEvaluator::evaluateFollowsT(array<string, 4> arr)
{
    string type1 = arr[0];
    string type2 = arr[1];
    string arg1 = arr[2];
    string arg2 = arr[3];

    if (type1 == "int" && type2 == "int")
    {
        //hasResult = isFollowsT(arg1, arg2);
    }
    else if (type1 == "int" && type2 == "_")
    {
        //hasResult = isBeingFollowedT(arg1);
    }
    else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        //if (getAfterStar(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
    }
    else if (type1 == "_" && type2 == "int")
    {
        //hasResult = isBeingFollowedByStar(arg2);
    }
    else if (type1 == "_" && type2 == "_")
    {
        //hasResult = hasFollowsT();
    }
    else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        //if (isFollowedStarBy(arg2).empty()) {
        //    hasResult = false;
        //}
    }
    else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "int")
    {
        //if (isFollowedBy(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
    }
    else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && type2 == "_")
    {
        //if (getAfter(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
    }
    else if ((type1 == "stmt" || type1 == "assign" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        //if (getFollows(arg1, arg2).empty()) {
        //
        //}
    }
}

void QueryEvaluator::evaluateParent(array<string, 4> arr)
{
    string type1 = arr[0];
    string type2 = arr[1];
    string arg1 = arr[2];
    string arg2 = arr[3];

    if (type1 == "int" && type2 == "int")
	{
        //hasResult = isParent(arg1, arg2);
	}
	else if (type1 == "int" && type2 == "_")
	{
        //hasResult = isParent(arg1);
	}
    else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        //if (getChildren(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
	}
	else if (type1 == "_" && type2 == "int")
	{
        //hasResult = isChildren(arg2);
	}
	else if (type1 == "_" && type2 == "_")
	{
        //hasResult = hasParent();
	}
    else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        //if (isParentOf(arg2).empty()) {
        //    hasResult = false;
        //}
	}
    else if ((type1 == "stmt" || type1 == "while") && type2 == "int")
	{
        //if (isParentOf(arg1, arg2)) {
        //    hasResult = false;
        //}
	}
    else if ((type1 == "stmt" || type1 == "while") && type2 == "_")
	{
        //if (getChildren(arg1)) {
        //    hasResult = false;
        //}
	}
    else if ((type1 == "stmt" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
	{
        //if (getParent(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
	}
}

void QueryEvaluator::evaluateParentT(array<string, 4> arr)
{
    string type1 = arr[0];
    string type2 = arr[1];
    string arg1 = arr[2];
    string arg2 = arr[3];

    if (type1 == "int" && type2 == "int")
    {
        //hasResult = isParentStar(arg1, arg2);
    }
    else if (type1 == "int" && type2 == "_")
    {
        //hasResult = isParentStar(arg2);
    }
    else if (type1 == "int" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {
        //if (getChildrenStar(arg1, arg2).empty()) {
        //    hasResult = false;
        //}
    }
    else if (type1 == "_" && type2 == "int")
    {

    }
    else if (type1 == "_" && type2 == "_")
    {

    }
    else if (type1 == "_" && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
    {

    }
    else if ((type1 == "stmt" || type1 == "while") && type2 == "int")
    {

    }
    else if ((type1 == "stmt" || type1 == "while") && type2 == "_")
    {

    }
    else if ((type1 == "stmt" || type1 == "while") && (type2 == "stmt" || type2 == "assign" || type2 == "while"))
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

}
