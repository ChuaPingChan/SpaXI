#include "PatternClause.h"
#include "../../Entity.h"

using namespace std;

PatternClause::PatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo)
{
    this->_patternType = patternType;
    this->_argOneType = argOneType;
    this->_argTwoType = argTwoType;
    this->_patternSyn = patternSyn;
    this->_argOne = argOne;
    this->_argTwo = argTwo;

    addSynonym(patternSyn);
    if (entityIsSynonym(argOneType)) {
        addSynonym(argOne);
    }
}

PatternClause::PatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo, Entity argThreeType, string argThree)
{
    this->_patternType = patternType;
    this->_argOneType = argOneType;
    this->_argTwoType = argTwoType;
    this->_argThreeType = argThreeType;
    this->_patternSyn = patternSyn;
    this->_argOne = argOne;
    this->_argTwo = argTwo;
    this->_argThree = argThree;

    addSynonym(patternSyn);
    if (entityIsSynonym(argOneType)) {
        addSynonym(argOne);
    }
}

PatternClause::~PatternClause()
{
}

PatternType PatternClause::getPatternType()
{
    return _patternType;
}

Entity PatternClause::getArgOneType()
{
    return this->_argOneType;
}

Entity PatternClause::getArgTwoType()
{
    return this->_argTwoType;
}

Entity PatternClause::getArgThreeType()
{
    return this->_argThreeType;
}

string PatternClause::getPatternSynonym()
{
    return this->_patternSyn;
}

string PatternClause::getArgOne()
{
    return this->_argOne;
}

string PatternClause::getArgTwo()
{
    return this->_argTwo;
}

string PatternClause::getArgThree()
{
    return this->_argThree;
}
