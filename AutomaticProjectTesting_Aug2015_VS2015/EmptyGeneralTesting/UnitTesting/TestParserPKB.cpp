#include <string>
#include <cstdio>
#include <regex>

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/Parser/Parser.h"
#include "../SPA/Parser/ParserChildForTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const std::string dummySimpleSourcePath = "../UnitTesting/ParserTestDependencies/dummySimpleSource.txt";

/************************************
* Integration Testing: Parser & PKB *
*************************************/
namespace UnitTesting
{

    TEST_CLASS(testName)
    {
    }
}