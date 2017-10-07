#pragma once
#include "..\..\..\SPA\PQL\QueryTree.h"
#include "..\..\..\SPA\PQL\Utilities\SelectClause.h"
#include "..\..\..\SPA\PQL\Utilities\SuchThatClause.h"
#include "..\..\..\SPA\PQL\Utilities\PatternClause.h"

using namespace std;

class UtilitySelection
{
public:
    UtilitySelection();
    ~UtilitySelection();

    /*********
    * Select *
    *********/
    static SelectClause makeSelectClause(SelectionType selectionType);
    static SelectClause makeSelectClause(SelectionType selectionType, Entity singleArgType, string singleArg);
    static SelectClause makeSelectClause(SelectionType selectionType, vector<Entity> tupleArgTypes, vector<string> tupleArgs);
    static bool isSameSelectClauseContent(SelectClause expected, SelectClause actual);
    
    /************
    * Such That *
    ************/
    static SuchThatClause makeSuchThatClause(Relationship rel, Entity argOneType, string argOne, Entity argTwoType, string argTwo);
    static SuchThatClause getFirstSuchThatClauseFromTree(QueryTree qt);
    static bool isSameSuchThatClauseContent(SuchThatClause expected, SuchThatClause actual);
    static bool AreSameSuchThatClausesContentAsInTree(vector<SuchThatClause> expectedList, QueryTree qt);
    
    /**********
    * Pattern *
    **********/
    static PatternClause makePatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo);
    static PatternClause makePatternClause(PatternType patternType, string patternSyn, Entity argOneType, string argOne, Entity argTwoType, string argTwo, Entity argThreeType, string argThree);
    static PatternClause getFirstPatternClauseFromTree(QueryTree qt);
    static bool isSamePatternClauseAssignWhileContent(PatternClause expected, PatternClause actual);
    static bool isSamePatternClauseIfContent(PatternClause expected, PatternClause actual);




private:
    static bool isSameSelectBooleanContent(SelectClause expected, SelectClause actual);
    static bool isSameSelectSingleArgContent(SelectClause expected, SelectClause actual);
    static bool isSameSelectTupleArgContent(SelectClause expected, SelectClause actual);
};
