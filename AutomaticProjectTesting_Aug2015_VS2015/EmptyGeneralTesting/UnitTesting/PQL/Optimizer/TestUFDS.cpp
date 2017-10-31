#include "CppUnitTest.h"
#include <string>
#include <list>

#include "../SPA/PQL/Optimizer/SynonymUFDS.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{

    TEST_CLASS(TestUFDS)
    {
    public:

        TEST_METHOD(TestAddSynonyms) {
            /*
                Consider clauses with these synonyms:
                - c1(a, b)
                - c2(c, d)
                - c3(e, a)
                - c4(e, f)
                - c5(d, h)

                Index:
                a b c d e f g h
                0 1 2 3 4 5 6 7

                Expected groupings:
                - (a, b, e, f)
                - (c, d, h)
                - (g)
            */

            SynonymUFDS synUFDS;

            for (int synIdx = 0; synIdx < 8; synIdx++) {
                synUFDS.addSynonym(synIdx);
                Assert::IsTrue(synUFDS.synonymPresent(synIdx));
            }
        }

        TEST_METHOD(TestUnionSetAndIsSameSet) {
            /*
            Consider clauses with these synonyms:
            - c1(a, b)
            - c2(c, d)
            - c3(e, a)
            - c4(e, f)
            - c5(d, h)

            Index:
            a b c d e f g h
            0 1 2 3 4 5 6 7

            Expected groupings:
            - (a, b, e, f)
            - (c, d, h)
            - (g)
            */

            SynonymUFDS synUFDS;
            list<list<int>> expectedGroups;
            list<list<int>> actualGroups;

            for (int synIdx = 0; synIdx < 8; synIdx++) {
                synUFDS.addSynonym(synIdx);
            }

            synUFDS.unionSet(0, 1);
            synUFDS.unionSet(2, 3);
            synUFDS.unionSet(4, 0);
            synUFDS.unionSet(4, 5);
            synUFDS.unionSet(3, 7);

            Assert::IsTrue(synUFDS.isSameSet(0, 4));
            Assert::IsTrue(synUFDS.isSameSet(0, 5));
            Assert::IsTrue(synUFDS.isSameSet(1, 5));
            Assert::IsTrue(synUFDS.isSameSet(2, 7));
            Assert::IsTrue(synUFDS.isSameSet(2, 3));

            Assert::IsFalse(synUFDS.isSameSet(0, 7));
            Assert::IsFalse(synUFDS.isSameSet(2, 4));
            Assert::IsFalse(synUFDS.isSameSet(6, 3));
        }

        TEST_METHOD(TestGetSynonymGroups) {
            /*
            Consider clauses with these synonyms:
            - c1(a, b)
            - c2(c, d)
            - c3(e, a)
            - c4(e, f)
            - c5(d, h)

            Index:
            a b c d e f g h
            0 1 2 3 4 5 6 7

            Expected groupings:
            - (a, b, e, f)
            - (c, d, h)
            - (g)
            */

            SynonymUFDS synUFDS;
            list<list<int>> expectedGroups;
            list<list<int>> actualGroups;

            for (int synIdx = 0; synIdx < 8; synIdx++) {
                synUFDS.addSynonym(synIdx);
            }

            synUFDS.unionSet(0, 1);
            synUFDS.unionSet(2, 3);
            synUFDS.unionSet(4, 0);
            synUFDS.unionSet(4, 5);
            synUFDS.unionSet(3, 7);

            actualGroups = synUFDS.getSynonymGroups();
            Assert::IsTrue(actualGroups.size() == 3);
            expectedGroups = list<list<int>>{ {0, 1, 4, 5}, {2, 3, 7}, {6} };
            actualGroups.sort();
            expectedGroups.sort();
            Assert::IsTrue(actualGroups == expectedGroups);
        }
    };
}