#include "UtilitySelection.h"


UtilitySelection::UtilitySelection()
{
}


UtilitySelection::~UtilitySelection()
{
}

SelectClause UtilitySelection::makeSelectClause(SelectionType selectionType)
{
    return SelectClause(selectionType);
}

SelectClause UtilitySelection::makeSelectClause(SelectionType selectionType, Entity singleArgType, string singleArg)
{
    return SelectClause(selectionType, singleArgType, singleArg);
}

SelectClause UtilitySelection::makeSelectClause(SelectionType selectionType, vector<Entity> tupleArgTypes, vector<string> tupleArgs)
{
    return SelectClause(selectionType, tupleArgTypes, tupleArgs);
}

bool UtilitySelection::isSameSelectClauseContent(SelectClause expected, SelectClause actual)
{
    switch (expected.getSelectionType())
    {
        case SELECT_BOOLEAN:
            return isSameSelectBooleanContent(expected, actual);
        case SELECT_SINGLE:
            return isSameSelectSingleArgContent(expected, actual);
        case SELECT_TUPLE:
            return isSameSelectTupleArgContent(expected, actual);
        default:
            return false;
    }
}



SuchThatClause UtilitySelection::makeSuchThatClause(Relationship rel, Entity argOneType, string argOne, Entity argTwoType, string argTwo)
{
    return SuchThatClause(rel, argOneType, argOne, argTwoType, argTwo);
}

SuchThatClause UtilitySelection::getFirstSuchThatClauseFromTree(QueryTree qt)
{
    vector<SuchThatClause> stcVector = qt.getSuchThatClauses();
    return stcVector.front();
}

bool UtilitySelection::isSameSuchThatClauseContent(SuchThatClause expected, SuchThatClause actual)
{
    bool isSameRel = expected.getRel() == actual.getRel();
    bool isSameArgOneType = expected.getArgOneType() == actual.getArgOneType();
    bool isSameArgTwoType = expected.getArgTwoType() == actual.getArgTwoType();
    bool isSameArgOne = expected.getArgOne() == actual.getArgOne();
    bool isSameArgTwo = expected.getArgTwo() == actual.getArgTwo();

    return isSameRel && isSameArgOneType && isSameArgTwoType && isSameArgOne && isSameArgTwo;
}

bool UtilitySelection::AreSameSuchThatClausesContentAsInTree(vector<SuchThatClause> expectedList, QueryTree qt)
{
    vector<SuchThatClause> actualList = qt.getSuchThatClauses();

    if (actualList.size() != expectedList.size()) {
        return false;
    }

    for (std::vector<SuchThatClause>::iterator iterExpected = expectedList.begin(); iterExpected != expectedList.end(); ++iterExpected) {
        SuchThatClause expectedStc = *iterExpected;

        std::vector<SuchThatClause>::iterator iterActual = actualList.begin();
        for (; iterActual != actualList.end(); ++iterActual) {
            SuchThatClause actualStc = *iterActual;
            if (isSameSuchThatClauseContent(expectedStc, actualStc)) {
                break;
            }
        }

        if (iterActual == actualList.end()) {
            return false;
        }
    }
    return true;
}


PatternClause UtilitySelection::makePatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo)
{
    //TODO: Might need to create type for unknown
    return PatternClause(patternType, patternSyn, argOneType, argOne, argTwoType, argTwo);
}

PatternClause UtilitySelection::makePatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo, Entity argThreeType, string argThree)
{
    return PatternClause(patternType, patternSyn, argOneType, argOne, argTwoType, argTwo, argThreeType, argThree);
}

PatternClause UtilitySelection::getFirstPatternClauseFromTree(QueryTree qt)
{
    vector<PatternClause> pcVector = qt.getPatternClauses();
    return pcVector.front();
}

bool UtilitySelection::isSamePatternClauseAssignWhileContent(PatternClause expected, PatternClause actual)
{
    bool isSamePatternType = expected.getPatternType() == actual.getPatternType();
    bool isSamePatternSyn = expected.getPatternSynonym() == actual.getPatternSynonym();
    bool isSameArgOneType = expected.getArgOneType() == actual.getArgOneType();
    bool isSameArgTwoType = expected.getArgTwoType() == actual.getArgTwoType();
    bool isSameArgOne = expected.getArgOne() == actual.getArgOne();
    bool isSameArgTwo = expected.getArgTwo() == actual.getArgTwo();

    return isSamePatternType && isSamePatternSyn && isSameArgOneType && isSameArgTwoType && isSameArgOne && isSameArgTwo;
}

bool UtilitySelection::isSamePatternClauseIfContent(PatternClause expected, PatternClause actual)
{
    bool isSamePatternType = expected.getPatternType() == actual.getPatternType();
    bool isSamePatternSyn = expected.getPatternSynonym() == actual.getPatternSynonym();
    bool isSameArgOneType = expected.getArgOneType() == actual.getArgOneType();
    bool isSameArgTwoType = expected.getArgTwoType() == actual.getArgTwoType();
    bool isSameArgThreeType = expected.getArgThreeType() == actual.getArgThreeType();
    bool isSameArgOne = expected.getArgOne() == actual.getArgOne();
    bool isSameArgTwo = expected.getArgTwo() == actual.getArgTwo();
    bool isSameArgThree = expected.getArgThree() == actual.getArgThree();

    return isSamePatternType && isSamePatternSyn && isSameArgOneType && isSameArgTwoType && isSameArgThreeType && isSameArgOne && isSameArgTwo && isSameArgThree;
}

bool UtilitySelection::areSamePatternClausesContentAsInTree(vector<PatternClause> expectedList, QueryTree qt)
{
    vector<PatternClause> actualList = qt.getPatternClauses();

    if (actualList.size() != expectedList.size()) {
        return false;
    }

    for (std::vector<PatternClause>::iterator iterExpected = expectedList.begin(); iterExpected != expectedList.end(); ++iterExpected) {
        PatternClause expectedPc = *iterExpected;

        std::vector<PatternClause>::iterator iterActual = actualList.begin();
        for (; iterActual != actualList.end(); ++iterActual) {
            PatternClause actualPc = *iterActual;
            PatternType actualPatternType = actualPc.getPatternType();

            if (actualPatternType == ASSSIGN_PATTERN && isSamePatternClauseAssignWhileContent(expectedPc, actualPc))
            {
                break;
            }
            else if (actualPatternType == WHILE_PATTERN && isSamePatternClauseAssignWhileContent(expectedPc, actualPc))
            {
                break;
            }
            else if (actualPatternType == If_PATTERN && isSamePatternClauseIfContent(expectedPc, actualPc))
            {
                break;
            }
        }

        if (iterActual == actualList.end()) {
            return false;
        }
    }
    return true;
}



WithClause UtilitySelection::makeWithClause(Attribute lhsAttribute, string lhsValue, Attribute rhsAttribute, string rhsValue)
{
    return WithClause(lhsAttribute, lhsValue, rhsAttribute, rhsValue);
}

WithClause UtilitySelection::getFirstWithClauseFromTree(QueryTree qt)
{
    vector<WithClause> wcVector = qt.getWithClauses();
    return wcVector.front();
}

bool UtilitySelection::isSameWithClauseContent(WithClause expected, WithClause actual)
{
    bool isSameLhsAttribute = expected.getLhsAttribute() == actual.getLhsAttribute();
    bool isSameRhsAttribute = expected.getRhsAttribute() == actual.getRhsAttribute();
    bool isSameLhsValue = expected.getLhsValue() == actual.getLhsValue();
    bool isSameRhsValue = expected.getRhsValue() == actual.getRhsValue();

    return isSameLhsAttribute && isSameRhsAttribute && isSameLhsValue && isSameRhsValue;
}

bool UtilitySelection::areSameWithClausesContentAsInTree(vector<WithClause> expectedList, QueryTree qt)
{
    vector<WithClause> actualList = qt.getWithClauses();

    if (actualList.size() != expectedList.size()) {
        return false;
    }

    for (std::vector<WithClause>::iterator iterExpected = expectedList.begin(); iterExpected != expectedList.end(); ++iterExpected) {
        WithClause expectedWc = *iterExpected;

        std::vector<WithClause>::iterator iterActual = actualList.begin();
        for (; iterActual != actualList.end(); ++iterActual) {
            WithClause actualWc = *iterActual;
            if (isSameWithClauseContent(expectedWc, actualWc)) {
                break;
            }
        }

        if (iterActual == actualList.end()) {
            return false;
        }
    }
    return true;
}



/**********
* Private *
**********/
bool UtilitySelection::isSameSelectBooleanContent(SelectClause expected, SelectClause actual)
{
    return expected.getSelectionType() == actual.getSelectionType();
}

bool UtilitySelection::isSameSelectSingleArgContent(SelectClause expected, SelectClause actual)
{
    return expected.getSelectionType() == actual.getSelectionType()
        && expected.getSingleArgType() == actual.getSingleArgType()
        && expected.getSingleArg() == actual.getSingleArg();
}

bool UtilitySelection::isSameSelectTupleArgContent(SelectClause expected, SelectClause actual)
{
    return expected.getSelectionType() == actual.getSelectionType()
        && expected.getTupleArgTypes() == actual.getTupleArgTypes()
        && expected.getTupleArgs() == actual.getTupleArgs();
}
