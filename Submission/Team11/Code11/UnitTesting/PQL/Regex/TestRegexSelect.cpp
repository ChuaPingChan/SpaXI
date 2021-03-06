#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\ValidationRegexLibrary\RegexValidators.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRegexSelect)
    {
    public:

        /************************
        * Select Single Synonym *
        ************************/

        TEST_METHOD(TestRegex_Select_SingleSynonym_Valid)
        {
            string str = "Select s";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SingleSynonym_WhiteSpace_Valid)
        {
            string str = "  Select   a  ";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SingleSynonym_Tabs_Valid)
        {
            string str = "	Select	s	";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_KeywordAsSynonym_Select_Valid)
        {
            string str = "Select Select";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_KeywordAsSynonym_Uses_Valid)
        {
            string str = "Select Uses";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_KeywordAsSynonym_if_Valid)
        {
            string str = "Select if";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_MissingWhitespaces_Invalid)
        {
            string str = "Selects";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_LowercaseKeyword_Invalid)
        {
            string str = "select s";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_MisspeltKeyword_Invalid)
        {
            string str = "selelct s";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_DuplicateSelect_Valid)
        {
            string str = "Select s Select v";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Brackets_Invalid)
        {
            string str = "Select (s)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_IncompleteSentence_Invalid)
        {
            string str = "select s10 such that";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }



        /*****************
        * Select Boolean *
        *****************/
        TEST_METHOD(TestRegex_Select_Boolean_Valid)
        {
            string str = "Select BOOLEAN";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }



        /***************
        * Select Tuple *
        ***************/
        TEST_METHOD(TestRegex_Select_Tuplw_SingleSynonym_Valid)
        {
            string str = "Select <s>";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Tuple_Valid)
        {
            string str = "Select <s, a>";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Tuple_Multiple_Valid)
        {
            string str = "Select <s, a, w, f>";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Tuple_NoWhitespaces_InfrontOfBrackets_Valid)
        {
            string str = "Select<s,a>";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Tuple_NoWhitespaces_AfterBrackets_Valid)
        {
            string str = "Select <s,a>such that Follows(1,2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Tuple_SeparationBtwnArg_InValid)
        {
            string str = "Select <no comma>";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Tuple_Brackets_LeftOnly_InValid)
        {
            string str = "Select <left, bracketOnly";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Tuple_Brackets_RightOnly_InValid)
        {
            string str = "Select right, bracketOnly>";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Tuple_Brackets_MissingBoth_InValid)
        {
            string str = "Select no brackets";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Tuple_Brackets_Incorrect_InValid)
        {
            string str = "Select (incorrect, bracketType)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        /******************************
        * Select Attribute - Single *
        ******************************/

        TEST_METHOD(TestRegex_ValidAttribute_ProcName)
        {
            string str = "Select p.procName";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_ValidAttribute_VarName)
        {
            string str = "Select v.varName";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_ValidAttribute_CallValue)
        {
            string str = "Select c.value";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_ValidAttribute_StmtNum)
        {
            string str = "Select s.stmt#";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_ValidAttribute_CallProcName)
        {
            string str = "Select c.procName";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_InvalidAttribute_ProcName)
        {
            string str = "Select p.Pr0cName";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_InvalidAttribute_Value)
        {
            string str = "Select v.VALUE#";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_InvalidAttribute_StmtNum)
        {
            string str = "Select a.stmtNumber";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_InvalidAttribute_VarName)
        {
            string str = "Select v.variableName";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_InvalidAttribute_CommaInsteadOfDot)
        {
            string str = "Select p,procName";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_InvalidAttribute_InvalidSynonym)
        {
            string str = "Select 1.value";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_InvalidAttribute_SpecialCharacter)
        {
            string str = "Select p.procName#";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_ValidAttribute_MultipleAttribute)
        {
            string str = "Select p.procName,v.varName";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }


        /****************************
        * Select Attribute - Tuple *
        *****************************/

        TEST_METHOD(TestRegex_Tuple_ValidAttribute_ProcName)
        {
            string str = "Select <p.procName,v.varName>";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_ValidAttribute_VarName)
        {
            string str = "Select <v.varName,c.varName>";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_ValidAttribute_CallValue)
        {
            string str = "Select <c.value,call.stmt#>";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_ValidAttribute_StmtNum)
        {
            string str = "Select <s.stmt#,v.varName,c.value>";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_ValidAttribute_MultipleAttribute)
        {
            string str = "Select <p.procName,v.varName>";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_ValidAttribute_CallProcName)
        {
            string str = "Select <c.procName>";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_InvalidAttribute_ProcName)
        {
            string str = "Select <p.Pr0cName>";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_InvalidAttribute_Value)
        {
            string str = "Select <v.VALUE#,1>";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_InvalidAttribute_StmtNum)
        {
            string str = "Select <a.stmt#,1>";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_InvalidAttribute_VarName)
        {
            string str = "Select <c.value,v.variableName>";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_InvalidAttribute_CommaInsteadOfDot)
        {
            string str = "Select <p,procName,    1.stmt#>";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_InvalidAttribute_InvalidSynonym)
        {
            string str = "Select <1.value,c.stmt#>";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Tuple_InvalidAttribute_SpecialCharacter)
        {
            string str = "Select <p.procName@,   hello.name>";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }


        /*****************************************
        * Select, Such that, Single Relationship *
        *****************************************/

        TEST_METHOD(TestRegex_SingleRelation_Uses_Valid)
        {
            string str = "Select s such that Uses(a,b)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Modifies_Valid)
        {
            string str = "Select s such that Modifies(1,v)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Follows_Valid)
        {
            string str = "Select s such that Follows(1,2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_FollowsStar_Valid)
        {
            string str = "Select s such that Follows*(1,2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Parent_Valid)
        {
            string str = "Select s such that Parent(1,2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_ParentStar_Valid)
        {
            string str = "Select s such that Parent*(1,2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Calls_Valid)
        {
            string str = "Select s such that Calls(p1,p2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_CallsStar_Valid)
        {
            string str = "Select s such that Calls*(p1,p2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Next_Valid)
        {
            string str = "Select s such that Next(n1,n2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_NextStar_Valid)
        {
            string str = "Select s such that Next*(n1,n2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Affects_Valid)
        {
            string str = "Select s such that Affects(a1,a2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_AffectsStar_Valid)
        {
            string str = "Select s such that Affects*(a1,a2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Whitespace_Valid)
        {
            string str = "  Select   s12      such that  Uses   (   b  ,  c   )   ";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Tab_Valid)
        {
            string str = "	Select	s12		such that	Uses	(	b	,	c	)	";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_SuchThat_SplitUp_Invalid)
        {
            string str = "Select s such Follows(1,2) that";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_MissingWhitespaces_Whole_Invalid)
        {
            string str = "SelectssuchthatUses(a,b)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_MissingWhitespaces_InSelect_Invalid)
        {
            string str = "Selectssuch that Uses(a,b)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_RelationStickToSuchThatKeyword_Invalid)
        {
            string str = "Select s such thatUses(a,b)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }


        /********************************************
        * Select, Such that, Multiple Relationships *
        ********************************************/
        TEST_METHOD(TestRegex_Select_SuchThat_And_Valid)
        {
            string str = "Select s such that Uses(s, v) and Modifies(2, v)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_And_And_Valid)
        {
            string str = "Select s such that Uses(s, v) and Modifies(2, v) and Follows(1,2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_SuchThat_And_Valid)
        {
            string str = "Select s such that Uses(s, v) such that Modifies(2, v) and Follows(1,2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_AndStickToBracketInFront_Valid)
        {
            string str = "Select s such that Uses(s, v)and Follows(1,2)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_AndStickToBracketBehind_Invalid)
        {
            string str = "Select s such that Uses(s, v) andFollows(1,2)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_IncorrectAndConcatenation_Invalid)
        {
            string str = "Select s such that Uses(s, v) and (1,2)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_AdjacentAnd_Invalid)
        {
            string str = "Select s such that Uses(s, v) and and Follows(1,2)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_AdjacentSuchThat_Invalid)
        {
            string str = "Select s such that such that Follows(1,2)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        

        /**************************
        * Select, Pattern, Single *
        **************************/
        TEST_METHOD(TestRegex_Select_Pattern_Single_Valid)
        {
            string str = "Select s pattern a ( _ , _ ) ";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }


        /****************************
        * Select, Pattern, Multiple *
        ****************************/
        TEST_METHOD(TestRegex_Select_Pattern_Twice_Valid)
        {
            string str = "Select s pattern a ( _ , _ ) and w (v, _)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Pattern_Thrice_Valid)
        {
            string str = "Select s pattern a ( _ , _ ) and w (v, _) and f(_, _, _)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Pattern_AndStickToPreviousType_Valid)
        {
            string str = "Select s pattern a ( _ , _ )and w (v, _)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }
        
        TEST_METHOD(TestRegex_Select_Pattern_Whitespace_Valid)
        {
            string str = "    Select s pattern         a         (    _   ,     _      )       and      w     (   v  ,     _    )    and    f(   _    ,      _    ,     _)    ";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Pattern_AndStickBehindType_Invalid)
        {
            string str = "Select s pattern a(_,_) andw(v,_)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        /***********************
        * Select, With, Single *
        ***********************/
        TEST_METHOD(TestRegex_Select_With_Single_Valid)
        {
            string str = "Select s with c.value=1";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }


        /*************************
        * Select, With, Multiple *
        *************************/
        TEST_METHOD(TestRegex_Select_With_Twice_Valid)
        {
            string str = "Select s with c.value=1 and v.varName=\"x\"";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_With_Thrice_Valid)
        {
            string str = "Select s with c.value=1 and v.varName=\"x\" and c.value=v.value";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }


        /***********************************
        * Select, Such That, Pattern, With *
        ***********************************/
        TEST_METHOD(TestRegex_Select_SuchThat_Pattern_Valid)
        {
            string str = "Select s such that Uses(1, v) pattern a ( _ , _ ) and w (v, _) and f(_, _)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Pattern_SuchThat_Valid)
        {
            string str = "Select s pattern a ( _ , _ ) and w (v, _) and f(_, _) such that Uses(1, v) and Modifies(2,v)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_With_Valid)
        {
            string str = "Select s such that Uses(1, v) with c.value=stmt#";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_With_SuchThat_Valid)
        {
            string str = "Select s with c.value=stmt# such that Uses(1, v)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Pattern_With_Valid)
        {
            string str = "Select s pattern a( _ , _ ) with c.value=stmt#";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_With_Pattern_Valid)
        {
            string str = "Select s with c.value=stmt# pattern a( _ , _ )";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_Pattern_With_Valid)
        {
            string str = "Select s such that Uses(1, v) pattern a(_,_) with c.value=stmt#";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_Pattern_With_Multiple_Valid)
        {
            string str = "Select s such that Uses(1, v) pattern a(_,_) with c.value=stmt# such that Modifies(3, v) and Follows(1, 2) with c.value=1 and v.varName=\"x\" pattern a(v, _) and a1(v1, _)";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }
    };
}
