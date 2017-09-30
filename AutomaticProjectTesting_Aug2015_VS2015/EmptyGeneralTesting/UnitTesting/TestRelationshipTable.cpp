#include "CppUnitTest.h"
#include "string.h"
#include "..\SPA\PQL\Validator\Selection\RelationshipTable\RelationshipTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting
{
    TEST_CLASS(TestRelationshipTable)
    {
        RelationshipTable rt;

        TEST_METHOD(TestRelationshipTableModifies)
        {
            Assert::IsTrue(rt.isArgValid(MODIFIES, INTEGER, VARIABLE));
            Assert::IsTrue(rt.isArgValid(MODIFIES, WHILE, VARIABLE));
            Assert::IsTrue(rt.isArgValid(MODIFIES, PROG_LINE, UNDERSCORE));
            Assert::IsTrue(rt.isArgValid(MODIFIES, STMT, IDENT_WITHQUOTES));
            Assert::IsTrue(rt.isArgValid(MODIFIES, IDENT_WITHQUOTES, VARIABLE));

            Assert::IsFalse(rt.isArgValid(MODIFIES, UNDERSCORE, UNDERSCORE));
            Assert::IsFalse(rt.isArgValid(MODIFIES, ASSIGN, ASSIGN));
            Assert::IsFalse(rt.isArgValid(MODIFIES, VARIABLE, UNDERSCORE));
            Assert::IsFalse(rt.isArgValid(MODIFIES, VARIABLE, ASSIGN));
            Assert::IsFalse(rt.isArgValid(MODIFIES, IDENT_WITHQUOTES, IDENT_WITHQUOTES));
        }

        TEST_METHOD(TestRelationshipTableUses)
        {
            Assert::IsTrue(rt.isArgValid(USES, ASSIGN, IDENT_WITHQUOTES));
            Assert::IsTrue(rt.isArgValid(USES, IF, VARIABLE));
            Assert::IsTrue(rt.isArgValid(USES, ASSIGN, IDENT_WITHQUOTES));
            Assert::IsTrue(rt.isArgValid(USES, INTEGER, IDENT_WITHQUOTES));
            Assert::IsTrue(rt.isArgValid(USES, IDENT_WITHQUOTES, UNDERSCORE));

            Assert::IsFalse(rt.isArgValid(USES, UNDERSCORE, CALL));
            Assert::IsFalse(rt.isArgValid(USES, ASSIGN, WHILE));
            Assert::IsFalse(rt.isArgValid(USES, VARIABLE, IF));
            Assert::IsFalse(rt.isArgValid(USES, VARIABLE, PROG_LINE));
            Assert::IsFalse(rt.isArgValid(USES, IDENT_WITHQUOTES, STMT));

        }

        TEST_METHOD(TestRelationshipTableParent)
        {
            Assert::IsTrue(rt.isArgValid(PARENT, INTEGER, INTEGER));
            Assert::IsTrue(rt.isArgValid(PARENT, WHILE, INTEGER)); 
            Assert::IsTrue(rt.isArgValid(PARENT, IF, INTEGER)); 
            Assert::IsTrue(rt.isArgValid(PARENT, UNDERSCORE, INTEGER));
            Assert::IsTrue(rt.isArgValid(PARENT, STMT, ASSIGN));

            Assert::IsFalse(rt.isArgValid(PARENT, CALL, ASSIGN));
            Assert::IsFalse(rt.isArgValid(PARENT, ASSIGN, ASSIGN));
            Assert::IsFalse(rt.isArgValid(PARENT, CALL, ASSIGN));
            Assert::IsFalse(rt.isArgValid(PARENT, ASSIGN, ASSIGN));
            Assert::IsFalse(rt.isArgValid(PARENT, CALL, ASSIGN));
        }

        TEST_METHOD(TestRelationshipTableParentStar)
        {
            Assert::IsTrue(rt.isArgValid(PARENTSTAR, INTEGER, INTEGER));
            Assert::IsTrue(rt.isArgValid(PARENTSTAR, WHILE, INTEGER)); 
            Assert::IsTrue(rt.isArgValid(PARENTSTAR, IF, INTEGER)); 
            Assert::IsTrue(rt.isArgValid(PARENTSTAR, UNDERSCORE, INTEGER));
            Assert::IsTrue(rt.isArgValid(PARENTSTAR, STMT, ASSIGN));

            Assert::IsFalse(rt.isArgValid(PARENTSTAR, CALL, ASSIGN));
            Assert::IsFalse(rt.isArgValid(PARENTSTAR, ASSIGN, ASSIGN));
            Assert::IsFalse(rt.isArgValid(PARENTSTAR, CALL, ASSIGN));
            Assert::IsFalse(rt.isArgValid(PARENTSTAR, ASSIGN, ASSIGN));
            Assert::IsFalse(rt.isArgValid(PARENTSTAR, CALL, ASSIGN));

        }

        TEST_METHOD(TestRelationshipTableFollows)
        {
            Assert::IsTrue(rt.isArgValid(FOLLOWS, INTEGER, INTEGER));
            Assert::IsTrue(rt.isArgValid(FOLLOWS, UNDERSCORE, UNDERSCORE));
            Assert::IsTrue(rt.isArgValid(FOLLOWS, IF, INTEGER));
            Assert::IsTrue(rt.isArgValid(FOLLOWS, ASSIGN, UNDERSCORE));
            Assert::IsTrue(rt.isArgValid(FOLLOWS, STMT, INTEGER));

            Assert::IsFalse(rt.isArgValid(FOLLOWS, VARIABLE, CALL));
            Assert::IsFalse(rt.isArgValid(FOLLOWS, UNDERSCORE, IDENT_WITHQUOTES));
            Assert::IsFalse(rt.isArgValid(FOLLOWS, IF, PROCEDURE));
            Assert::IsFalse(rt.isArgValid(FOLLOWS, ASSIGN, VARIABLE));
            Assert::IsFalse(rt.isArgValid(FOLLOWS, IDENT_WITHQUOTES, PROCEDURE));


        }

        TEST_METHOD(TestRelationshipTableFollowsStar)
        {
            Assert::IsTrue(rt.isArgValid(FOLLOWSSTAR, ASSIGN, UNDERSCORE));
            Assert::IsTrue(rt.isArgValid(FOLLOWSSTAR, WHILE, STMT));
            Assert::IsTrue(rt.isArgValid(FOLLOWSSTAR, PROG_LINE, IF));
            Assert::IsTrue(rt.isArgValid(FOLLOWSSTAR, CALL, CALL));
            Assert::IsTrue(rt.isArgValid(FOLLOWSSTAR, UNDERSCORE, INTEGER));

            Assert::IsFalse(rt.isArgValid(FOLLOWSSTAR, PROCEDURE, PROCEDURE));
            Assert::IsFalse(rt.isArgValid(FOLLOWSSTAR, PROCEDURE, INTEGER));
            Assert::IsFalse(rt.isArgValid(FOLLOWSSTAR, IDENT_WITHQUOTES, VARIABLE));
            Assert::IsFalse(rt.isArgValid(FOLLOWSSTAR, STMT, IDENT_WITHQUOTES));
            Assert::IsFalse(rt.isArgValid(FOLLOWSSTAR, VARIABLE, INTEGER));

        }

        TEST_METHOD(TestRelationshipTablePattern)
        {
            Assert::IsTrue(rt.isArgValid(PATTERN, ASSIGN, VARIABLE, UNDERSCORE));
            Assert::IsTrue(rt.isArgValid(PATTERN, ASSIGN, UNDERSCORE, UNDERSCORE));
            Assert::IsTrue(rt.isArgValid(PATTERN, ASSIGN, VARIABLE, EXPRESSION_SPEC));
            Assert::IsTrue(rt.isArgValid(PATTERN, WHILE, VARIABLE, UNDERSCORE));
            Assert::IsTrue(rt.isArgValid(PATTERN, WHILE, IDENT_WITHQUOTES, EXPRESSION_SPEC));

            Assert::IsFalse(rt.isArgValid(PATTERN, ASSIGN, STMT, UNDERSCORE));
            Assert::IsFalse(rt.isArgValid(PATTERN, STMT, EXPRESSION_SPEC, UNDERSCORE));
            Assert::IsFalse(rt.isArgValid(PATTERN, VARIABLE, VARIABLE, EXPRESSION_SPEC));
            Assert::IsFalse(rt.isArgValid(PATTERN, ASSIGN, IDENT_WITHQUOTES, STMT));
            Assert::IsFalse(rt.isArgValid(PATTERN, WHILE, IDENT_WITHQUOTES, VARIABLE));


        }

    };

}
