@echo off
:main
echo ===============================================================================
echo Welcome to Team 11 AutoTester (o.o)
echo ===============================================================================
echo Type the test index to run the test
echo [0] Receive a compliment
echo [?] Run AutoTester for test ?
echo [s] Run AutoTester for specified test path
echo [x] Exit
set option=
set /p option=Please select your options: 
if '%option%'=='0' (
	goto :generateCompliment
)
if '%option%'=='x' (
	goto :close
)
if '%option%'=='s' (
	goto :runGivenTest
)
if '%option%'=='1' (
	goto :runTest1
)
if '%option%'=='2' (
	goto :runTest2
)
if '%option%'=='3' (
	goto :runTest3
)
if '%option%'=='4' (
	goto :runTest4
)
if '%option%'=='5' (
	goto :runTest5
)
if '%option%'=='6' (
	goto :runTest5
)
cls
goto :main
echo ===============================================================================

:close
goto eof

:generateCompliment
@echo off
echo.
set compliment[0]=You are beautiful :) Thank you for teaching us!
set compliment[1]=Have a great day!
set compliment[2]=This is the best module I've ever taken!
set /a i=%random%%%3
call echo %%compliment[%i%]%%
echo.
pause
cls
goto :main

:runGivenTest
@echo off
echo ===============================================================================
echo [cls]  Clear screen
echo [back] Return to main
set /p source=Enter your source path: 
echo Source Path: %source% 
if '%source%'=='cls' (
	cls
	goto :runGivenTest
)
if '%source%'=='back' (
	cls
	goto :main
)
echo.
set /p query=Enter your query path: 
echo Query Path : %query%
if '%query%'=='cls' (
	cls
	goto :runGivenTest
)
if '%query%'=='back' (
	cls
	goto :main
)
echo.
set /p output=Enter your output path: 
echo Output Path : %output%
if '%output%'=='cls' (
	cls
	goto :runGivenTest
)
if '%output%'=='back' (
	cls
	goto :main
)
echo.
echo Running [ AutoTester %source% %query% %output% ] ...
AutoTester %source% %query% %output% > %output%.txt
echo Finish running AutoTester.
echo You may view your result at %output% or %output%.txt
pause
cls
goto :main

:runTest1
echo ===============================================================================
echo Generating queries for test 1...
python Test1_Frozen\QueryGenerator1.py Test1_Frozen\QuerySet1.xlsx Test1_Frozen\test1query.txt
echo Finish generating queries for test 1.
echo Running AutoTester for test 1...
AutoTester Test1_Frozen\test1source.txt Test1_Frozen\test1query.txt Test1_Frozen\out1.xml > Test1_Frozen\AutoTester1.txt
echo Finish running AutoTester for test 1.
pause
cls
goto :main

:runTest2
echo ===============================================================================
echo Generating Queries for test 2...
python Test2\QueryGenerator2.py Test2\QuerySet2.xlsx Test2\test2query.txt
echo Finish generating queries for test 2.
echo Running AutoTester for test 2...
AutoTester Test2\test2source.txt Test2\test2query.txt Test2\out2.xml > Test2\AutoTester2.txt
echo Finish running AutoTester for test 2.
pause
cls
goto :main

:runTest3
echo ===============================================================================
echo Running AutoTester for test 3...
AutoTester Test3_Frozen\test3source.txt Test3_Frozen\test3query.txt Test3_Frozen\out3.xml > Test3_Frozen\AutoTester.txt
echo Finish running AutoTester for test 3.
pause
cls
goto :main

:runTest4
echo ===============================================================================
echo Running AutoTester for test 4_0...
AutoTester Test4_Frozen\test4source0.txt Test4_Frozen\test4query0.txt Test4_Frozen\out4_0.xml > Test4_Frozen\AutoTester4_0.txt
echo Finish running AutoTester for test 4_0.
echo Running AutoTester for test 4_1...
AutoTester Test4_Frozen\test4source1.txt Test4_Frozen\test4query1.txt Test4_Frozen\out4_1.xml > Test4_Frozen\AutoTester4_1.txt
echo Finish running AutoTester for test 4_1.
echo Running AutoTester for test 4_2...
AutoTester Test4_Frozen\test4source2.txt Test4_Frozen\test4query2.txt Test4_Frozen\out4_2.xml > Test4_Frozen\AutoTester4_2.txt
echo Finish running AutoTester for test 4_2.
pause
cls
goto :main

:runTest5
echo ===============================================================================
echo Generating Queries for test 5...
python Test5\QueryGenerator5.py Test5\QuerySet5.xlsx Test5\test5query.txt
echo Finish generating queries for test 5.
echo Running AutoTester for test 5...
AutoTester Test5\test5source.txt Test5\test5query.txt Test5\out5.xml > Test5\AutoTester5.txt
echo Finish running AutoTester for test 5.
pause
cls
goto :main

:runTest6
echo ===============================================================================
echo Running AutoTester for test 6...
echo Running AutoTester for Demo_Calls...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_Calls.txt Test6_Frozen\ZoutputZ\outDemo_Calls.xml > Test6_Frozen\ZoutputZ\AutoTesterDemo_Calls.txt
echo Finish running AutoTester for Demo_Calls.
echo Running AutoTester for Demo_CallsStar...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_CallsStar.txt Test6_Frozen\ZoutputZ\outDemo_CallsStar.xml > Test6_Frozen\ZoutputZ\AutoTesterDemo_CallsStar.txt
echo Finish running AutoTester for Demo_CallsStar.
echo Running AutoTester for Demo_Follows...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_Follows.txt Test6_Frozen\ZoutputZ\outDemo_Follows.xml > Test6_Frozen\ZoutputZ\AutoTesterDemo_Follows.txt
echo Finish running AutoTester for Demo_Follows.
echo Running AutoTester for Demo_FollowsStar...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_FollowsStar.txt Test6_Frozen\ZoutputZ\outDemo_FollowsStar.xml > Test6_Frozen\ZoutputZ\AutoTesterDemo_FollowsStar.txt
echo Finish running AutoTester for Demo_FollowsStar.
echo Running AutoTester for Demo_Modifies...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_Modifies.txt Test6_Frozen\ZoutputZ\outDemo_Modifies.xml > Test6_Frozen\ZoutputZ\AutoTesterDemo_Modifies.txt
echo Finish running AutoTester for Demo_Modifies.
echo Running AutoTester for Demo_Next...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_Next.txt Test6_Frozen\ZoutputZ\outDemo_Next.xml > Test6_Frozen\ZoutputZ\AutoTesterDemo_Next.txt
echo Finish running AutoTester for Demo_Next.
echo Running AutoTester for Demo_NextStar...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_NextStar.txt Test6_Frozen\ZoutputZ\outDemo_NextStar.xml > Test6_Frozen\ZoutputZ\AutoTesterDemo_NextStar.txt
echo Finish running AutoTester for Demo_NextStar.
echo Running AutoTester for Demo_Parent...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_Parent.txt Test6_Frozen\ZoutputZ\outDemo_Parent.xml > Test6_Frozen\ZoutputZ\AutoTesterDemo_Parent.txt
echo Finish running AutoTester for Demo_Parent.
echo Running AutoTester for Demo_ParentStar...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_ParentStar.txt Test6_Frozen\ZoutputZ\outDemo_ParentStar.xml > Test6_Frozen\ZoutputZ\AutoTesterDemo_ParentStar.txt
echo Finish running AutoTester for Demo_ParentStar.
echo Running AutoTester for Demo_Uses...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_Uses.txt Test6_Frozen\ZoutputZ\outDemo_Uses.xml > Test6_Frozen\ZoutputZ\AutoTesterDemo_Uses.txt
echo Finish running AutoTester for Demo_Uses.
echo Running AutoTester for CALLS_01...
AutoTester Test6_Frozen\2_Calls\CALLS_SOURCE_01.txt Test6_Frozen\2_Calls\CALLS_QUERIES_01.txt Test6_Frozen\ZoutputZ\outCALLS_01.xml > Test6_Frozen\ZoutputZ\AutoTesterCALLS_01.txt
echo Finish running AutoTester for CALLS_01.
echo Running AutoTester for FOLLOWS_01...
AutoTester Test6_Frozen\3_Follows\FOLLOWS_SOURCE_01.txt Test6_Frozen\3_Follows\FOLLOWS_QUERIES_01.txt Test6_Frozen\ZoutputZ\outFOLLOWS.xml > Test6_Frozen\ZoutputZ\AutoTesterFOLLOWS.txt
echo Finish running AutoTester for FOLLOWS_01.
echo Running AutoTester for MixTests01...
AutoTester Test6_Frozen\4_MixTests01\MixTestsSource01.txt Test6_Frozen\4_MixTests01\MixTestsQuery01.txt Test6_Frozen\ZoutputZ\outMixTests01.xml > Test6_Frozen\ZoutputZ\AutoTesterMixTests01.txt
echo Finish running AutoTester for MixTests01.
echo Running AutoTester for MixTests02...
AutoTester Test6_Frozen\5_MixTests02\MixTestsSource02.txt Test6_Frozen\5_MixTests02\MixTestsQuery02.txt Test6_Frozen\ZoutputZ\outMixTests02.xml > Test6_Frozen\ZoutputZ\AutoTesterMixTests02.txt
echo Finish running AutoTester for MixTests02.
echo Running AutoTester for ModifiesUsesParent...
AutoTester Test6_Frozen\6_ModifiesUsesParent\ModifiesUsesParentSource01.txt Test6_Frozen\6_ModifiesUsesParent\ModifiesUsesParentQuery01.txt Test6_Frozen\ZoutputZ\outModifiesUsesParent.xml > Test6_Frozen\ZoutputZ\AutoTesterModifiesUsesParent.txt
echo Finish running AutoTester for ModifiesUsesParent.
echo Running AutoTester for MultipleRelationship01...
AutoTester Test6_Frozen\7_MultipleRelationship01\MultipleRelationshipSource01.txt Test6_Frozen\7_MultipleRelationship01\MultipleRelationshipQuery01.txt Test6_Frozen\ZoutputZ\outMultipleRelationship01.xml > Test6_Frozen\ZoutputZ\AutoTesterMultipleRelationship01.txt
echo Finish running AutoTester for MultipleRelationship01.
echo Running AutoTester for MultipleRelationship02...
AutoTester Test6_Frozen\8_MultipleRelationship02\MultipleRelationshipSource02.txt Test6_Frozen\8_MultipleRelationship02\MultipleRelationshipQuery02.txt Test6_Frozen\ZoutputZ\outMultipleRelationship02.xml > Test6_Frozen\ZoutputZ\AutoTesterMultipleRelationship02.txt
echo Finish running AutoTester for MultipleRelationship02.
echo Running AutoTester for Next...
AutoTester Test6_Frozen\9_Next\NEXT_SOURCE_01.txt Test6_Frozen\9_Next\NEXT_QUERIES_01.txt Test6_Frozen\ZoutputZ\outNext.xml > Test6_Frozen\ZoutputZ\AutoTesterNext.txt
echo Finish running AutoTester for Next.
echo Running AutoTester for NextNextStar...
AutoTester Test6_Frozen\10_NextNextStar\NEXT-NEXT-STAR_SOURCE_01.txt Test6_Frozen\10_NextNextStar\NEXT-NEXT-STAR_QUERIES_01.txt Test6_Frozen\ZoutputZ\outNextNextStar.xml > Test6_Frozen\ZoutputZ\AutoTesterNextNextStar.txt
echo Finish running AutoTester for NextNextStar.
echo Running AutoTester for NextStar...
AutoTester Test6_Frozen\11_NextStar\NEXT-STAR_SOURCE_01.txt Test6_Frozen\11_NextStar\NEXT-STAR_QUERIES_01.txt Test6_Frozen\ZoutputZ\outNextStar.xml > Test6_Frozen\ZoutputZ\AutoTesterNextStar.txt
echo Finish running AutoTester for NextStar.
echo Running AutoTester for Pattern...
AutoTester Test6_Frozen\12_Pattern\PATTERN_SOURCE_01.txt Test6_Frozen\12_Pattern\PATTERN_QUERIES_01.txt Test6_Frozen\ZoutputZ\outPattern.xml > Test6_Frozen\ZoutputZ\AutoTesterPattern.txt
echo Finish running AutoTester for Pattern.
echo Running AutoTester for Tuple...
AutoTester Test6_Frozen\13_Tuple\TUPLE_TESTS_SOURCE_01.txt Test6_Frozen\13_Tuple\TUPLE_TESTS_QUERIES_01.txt Test6_Frozen\ZoutputZ\outTuple.xml > Test6_Frozen\ZoutputZ\AutoTesterTuple.txt
echo Finish running AutoTester for Tuple.
echo Running AutoTester for With...
AutoTester Test6_Frozen\14_With\WITH_SOURCE_01.txt Test6_Frozen\14_With\WITH_QUERIES_01.txt Test6_Frozen\ZoutputZ\outWith.xml > Test6_Frozen\ZoutputZ\AutoTesterWith.txt
echo Finish running AutoTester for With.
echo Running AutoTester for Simple01...
AutoTester Test6_Frozen\15_Simple01\Simple01-Source.txt Test6_Frozen\15_Simple01\Simple01-Queries.txt Test6_Frozen\ZoutputZ\outSimple01.xml > Test6_Frozen\ZoutputZ\AutoTesterSimple01.txt
echo Finish running AutoTester for Simple01.
echo Running AutoTester for Simple02...
AutoTester Test6_Frozen\16_Simple02\Simple02-Source.txt Test6_Frozen\16_Simple02\Simple02-Queries.txt Test6_Frozen\ZoutputZ\outSimple02.xml > Test6_Frozen\ZoutputZ\AutoTesterSimple02.txt
echo Finish running AutoTester for Simple02.
echo Running AutoTester for Simple03...
AutoTester Test6_Frozen\17_Simple03\Simple03-Source.txt Test6_Frozen\17_Simple03\Simple03-Queries.txt Test6_Frozen\ZoutputZ\outSimple03.xml > Test6_Frozen\ZoutputZ\AutoTesterSimple03.txt
echo Finish running AutoTester for Simple03.
echo Finish running AutoTester for test 6.
pause
cls
goto :main