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

void QueryEvaluator::evaluateFollowsT(array<string, 4> arr)
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
	else if (arr[0] == "_" && arr[2] == "int")
	{

	}
	else if (arr[0] == "_" && arr[2] == "_")
	{

	}
	else if (arr[0] == "_" && arr[2] == "")
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

void QueryEvaluator::evaluateParent(array<string, 4> arr)
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
	else if (arr[0] == "_" && arr[2] == "int")
	{

	}
	else if (arr[0] == "_" && arr[2] == "_")
	{

	}
	else if (arr[0] == "_" && arr[2] == "")
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

void QueryEvaluator::evaluateParentT(array<string, 4> arr)
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
	else if (arr[0] == "_" && arr[2] == "int")
	{

	}
	else if (arr[0] == "_" && arr[2] == "_")
	{

	}
	else if (arr[0] == "_" && arr[2] == "")
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
