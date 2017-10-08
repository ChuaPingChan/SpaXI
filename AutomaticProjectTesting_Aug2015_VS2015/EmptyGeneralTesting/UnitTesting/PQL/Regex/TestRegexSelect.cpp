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

        TEST_METHOD(TestRegex_Select_Tuple_MissingWhitespaces_Invalid)
        {
            string str = "Select<s,a>";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
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

        //TODO: Change this to IsTrue when implement Next
        TEST_METHOD(TestRegex_SingleRelation_Next_Valid)
        {
            string str = "Select s such that Next(n1,n2)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        //TODO: Change this to IsTrue when implement Next*
        TEST_METHOD(TestRegex_SingleRelation_NextStar_Valid)
        {
            string str = "Select s such that Next*(n1,n2)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        //TODO: Change this to IsTrue when implement Affects
        TEST_METHOD(TestRegex_SingleRelation_Affects_Valid)
        {
            string str = "Select s such that Affects(a1,a2)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        //TODO: Change this to IsTrue when implement Affects*
        TEST_METHOD(TestRegex_SingleRelation_AffectsStar_Valid)
        {
            string str = "Select s such that Affects*(a1,a2)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Whitespace_Valid)
        {
            string str = "  Select   s12      such    that  Uses   (   b  ,  c   )   ";
            Assert::IsTrue(RegexValidators::isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Tab_Valid)
        {
            string str = "	Select	s12		such	that	Uses	(	b	,	c	)	";
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
        


        /***********************
        * Select, With, Single *
        ***********************/
        //TODO: Change to IsTrue when implement with
        TEST_METHOD(TestRegex_Select_With_Single_Valid)
        {
            string str = "Select s with c.value=1";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }


        /*************************
        * Select, With, Multiple *
        *************************/
        //TODO: Change to IsTrue when implement multiple pattern
        TEST_METHOD(TestRegex_Select_With_Twice_Valid)
        {
            string str = "Select s with c.value=1 and v.varName=\"x\"";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple pattern
        TEST_METHOD(TestRegex_Select_With_Thrice_Valid)
        {
            string str = "Select s with c.value=1 and v.varName=\"x\" and c.value=v.value";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
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

        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_SuchThat_With_Valid)
        {
            string str = "Select s such that Uses(1, v) with c.value=stmt#";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_With_SuchThat_Valid)
        {
            string str = "Select s with c.value=stmt# such that Uses(1, v)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_Pattern_With_Valid)
        {
            string str = "Select s pattern a( _ , _ ) with c.value=stmt#";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_With_Pattern_Valid)
        {
            string str = "Select s with c.value=stmt# pattern a( _ , _ )";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_SuchThat_Pattern_With_Valid)
        {
            string str = "Select s such that Uses(1, v) pattern a(_,_) with c.value=stmt#";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_SuchThat_Pattern_With_Multiple_Valid)
        {
            string str = "Select s such that Uses(1, v) pattern a(_,_) with c.value=stmt# such that Modifies(3, v) and Follows(1, 2) with c.value=1 and v.varName=\"x\" pattern a(v, _) and a1(v1, _)";
            Assert::IsFalse(RegexValidators::isValidSelectOverallRegex(str));
        }
    };
}
