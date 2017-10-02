#include "ClauseEvaluator.h"

ClauseEvaluator::ClauseEvaluator()
{
	pkbInstance = PKBMain::getInstance();
}


ClauseEvaluator::~ClauseEvaluator()
{
}


list<string> ClauseEvaluator::getListStringFromListInt(list<int> listOfInt)
{
    list<string> listOfString;
    for (std::list<int>::iterator it = listOfInt.begin(); it != listOfInt.end(); ++it) {
        string stringFromInt = to_string(*it);
        listOfString.push_back(stringFromInt);
    }
    return listOfString;
}