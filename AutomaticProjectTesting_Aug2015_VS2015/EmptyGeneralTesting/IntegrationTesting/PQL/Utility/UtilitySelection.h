#pragma once
#include "..\..\..\SPA\PQL\QueryTree.h"
#include "..\..\..\SPA\PQL\Utilities\SelectClause.h"
#include "..\..\..\SPA\PQL\Utilities\SuchThatClause.h"
#include "..\..\..\SPA\PQL\Utilities\PatternClause.h"
#include "..\SPA\PQL\Utilities\WithClause.h"

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
    static bool areSamePatternClausesContentAsInTree(vector<PatternClause> expectedList, QueryTree qt);

    /*******
    * With *
    *******/
    static WithClause makeWithClause(WithType withType, Entity lhsEntity, string lhsValue, Entity rhsEntity, string rhsValue);
    static WithClause getFirstWithClauseFromTree(QueryTree qt);
    static bool isSameWithClauseContent(WithClause expected, WithClause actual);
    static bool areSameWithClausesContentAsInTree(vector<WithClause> expectedList, QueryTree qt);

private:
    static bool isSameSelectBooleanContent(SelectClause expected, SelectClause actual);
    static bool isSameSelectSingleArgContent(SelectClause expected, SelectClause actual);
    static bool isSameSelectTupleArgContent(SelectClause expected, SelectClause actual);
};
