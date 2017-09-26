#include "CppUnitTest.h"
#include "string.h"
#include "..\..\SPA\PQL\QueryValidatorFriend.h"

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
            QueryValidatorFriend qvf;
            string str = "Select s";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SingleSynonym_WhiteSpace_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select   a  ";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_LowercaseKeyword_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "select s";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_MisspeltKeyword_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "selelct s";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Brackets_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Selelct (s)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_IncompleteSentence_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "select s10 such that";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }



        /*****************
        * Select Boolean *
        *****************/

        //TODO: Change to IsTrue when implement Boolean
        TEST_METHOD(TestRegex_Select_Boolean_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select BOOLEAN";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }



        /***************
        * Select Tuple *
        ***************/

        //TODO: Change to IsTrue when implement tuple
        TEST_METHOD(TestRegex_Select_Tuple_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select <s, a>";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Tuple_SeparationBtwnArg_InValid)
        {
            QueryValidatorFriend qvf;
            string str = "Select <no comma>";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Tuple_Brackets_InValid)
        {
            QueryValidatorFriend qvf;
            string str = "Select <left, bracketOnly";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
            str = "Select right, bracketOnly>";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
            str = "Select no brackets";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
            str = "Select (incorrect, bracketType)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }



        /*****************************************
        * Select, Such that, Single Relationship *
        *****************************************/

        TEST_METHOD(TestRegex_SingleRelation_Uses_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Uses(a,b)";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Modifies_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Modifies(1,v)";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Follows_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Follows(1,2)";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_FollowsStar_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Follows*(1,2)";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Parent_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Parent(1,2)";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_ParentStar_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Parent*(1,2)";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change this to IsTrue when implement Call
        TEST_METHOD(TestRegex_SingleRelation_Calls_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Calls(p1,p2)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change this to IsTrue when implement Call*
        TEST_METHOD(TestRegex_SingleRelation_CallsStar_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Calls*(p1,p2)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change this to IsTrue when implement Next
        TEST_METHOD(TestRegex_SingleRelation_Next_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Next(n1,n2)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change this to IsTrue when implement Next*
        TEST_METHOD(TestRegex_SingleRelation_NextStar_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Next*(n1,n2)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change this to IsTrue when implement Affects
        TEST_METHOD(TestRegex_SingleRelation_Affects_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Affects(a1,a2)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change this to IsTrue when implement Affects*
        TEST_METHOD(TestRegex_SingleRelation_AffectsStar_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Affects*(a1,a2)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_SingleRelation_Whitespace_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s12 such that Uses ( b , c )";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_SplitUp_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such Follows(1,2) that";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }


        /********************************************
        * Select, Such that, Multiple Relationships *
        ********************************************/
        //TODO: Change to IsTrue when implement multiple pattern
        TEST_METHOD(TestRegex_Select_SuchThat_Twice_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Uses(s, v) and Modifies(2, v)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple pattern
        TEST_METHOD(TestRegex_Select_SuchThat_Thrice_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Uses(s, v) and Modifies(2, v) and Follows(1,2)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_IncorrectAndConcatenation_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Uses(s, v) and (1,2)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_AdjacentAnd_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Uses(s, v) and and Follows(1,2)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_SuchThat_AdjacentSuchThat_Invalid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that such that Follows(1,2)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        

        /**************************
        * Select, Pattern, Single *
        **************************/
        TEST_METHOD(TestRegex_Select_Pattern_Single_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s pattern a ( _ , _ ) ";
            Assert::IsTrue(qvf.isValidSelectOverallRegex(str));
        }


        /****************************
        * Select, Pattern, Multiple *
        ****************************/
        //TODO: Change to IsTrue when implement multiple pattern
        TEST_METHOD(TestRegex_Select_Pattern_Twice_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s pattern a ( _ , _ ) and w (v, _)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple pattern
        TEST_METHOD(TestRegex_Select_Pattern_Thrice_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s pattern a ( _ , _ ) and w (v, _) and f(_, _)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }
        


        /***********************
        * Select, With, Single *
        ***********************/
        //TODO: Change to IsTrue when implement with
        TEST_METHOD(TestRegex_Select_With_Single_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s with c.value=1";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }


        /*************************
        * Select, With, Multiple *
        *************************/
        //TODO: Change to IsTrue when implement multiple pattern
        TEST_METHOD(TestRegex_Select_With_Twice_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s with c.value=1 and v.varName=\"x\"";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple pattern
        TEST_METHOD(TestRegex_Select_With_Thrice_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s with c.value=1 and v.varName=\"x\" and c.value=v.value";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }


        /***********************************
        * Select, Such That, Pattern, With *
        ***********************************/
        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_SuchThat_Pattern_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Uses(1, v) pattern a ( _ , _ ) and w (v, _) and f(_, _)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        TEST_METHOD(TestRegex_Select_Pattern_SuchThat_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s pattern a ( _ , _ ) and w (v, _) and f(_, _) such that Uses(1, v) and Modifies(2,v)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_SuchThat_With_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Uses(1, v) with c.value=stmt#";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_With_SuchThat_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s with c.value=stmt# such that Uses(1, v)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_Pattern_With_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s pattern a( _ , _ ) with c.value=stmt#";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_With_Pattern_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s with c.value=stmt# pattern a( _ , _ )";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_SuchThat_Pattern_With_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Uses(1, v) pattern a(_,_) with c.value=stmt#";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }

        //TODO: Change to IsTrue when implement multiple clauses
        TEST_METHOD(TestRegex_Select_SuchThat_Pattern_With_Multiple_Valid)
        {
            QueryValidatorFriend qvf;
            string str = "Select s such that Uses(1, v) pattern a(_,_) with c.value=stmt# such that Modifies(3, v) and Follows(1, 2) with c.value=1 and v.varName=\"x\" pattern a(v, _) and a1(v1, _)";
            Assert::IsFalse(qvf.isValidSelectOverallRegex(str));
        }
    };
}
