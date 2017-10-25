@echo off
:main
echo ===============================================================================
echo Welcome to Team 11 AutoTester (o.o)
echo ===============================================================================
echo Type the test index to run the test
echo [0] Receive a compliment
echo [s] Run AutoTester for specified test path
echo [a] Run All Tests
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
if '%option%'=='a' (
	goto :runAllTests
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

:runAllTests
echo ===============================================================================
echo                           Start Running AutoTester
echo ===============================================================================
echo Running AutoTester for test 1...
AutoTester Test1_Frozen\test1source.txt Test1_Frozen\test1query.txt TestResult\out1.xml > TestResult\cmd\cmd1.txt
echo Finish running AutoTester for test 1.
echo -------------------------------------------------------------------------------
echo Running AutoTester for test 2...
AutoTester Test2_Frozen\test2source.txt Test2_Frozen\test2query.txt TestResult\out2.xml > TestResult\cmd\cmd2.txt
echo Finish running AutoTester for test 2.
echo -------------------------------------------------------------------------------
echo Running AutoTester for test 3...
AutoTester Test3_Frozen\test3source.txt Test3_Frozen\test3query.txt TestResult\out3.xml > TestResult\cmd\cmd3.txt
echo Finish running AutoTester for test 3.
echo -------------------------------------------------------------------------------
echo Running AutoTester for test 4_0...
AutoTester Test4_Frozen\test4source0.txt Test4_Frozen\test4query0.txt TestResult\out4_0.xml > TestResult\cmd\cmd4_0.txt
echo Finish running AutoTester for test 4_0.
echo Running AutoTester for test 4_1...
AutoTester Test4_Frozen\test4source1.txt Test4_Frozen\test4query1.txt TestResult\out4_1.xml > TestResult\cmd\cmd4_1.txt
echo Finish running AutoTester for test 4_1.
echo Running AutoTester for test 4_2...
AutoTester Test4_Frozen\test4source2.txt Test4_Frozen\test4query2.txt TestResult\out4_2.xml > TestResult\cmd\cmd4_2.txt
echo Finish running AutoTester for test 4_2.
echo -------------------------------------------------------------------------------
python Test5\QueryGenerator5.py Test5\QuerySet5.xlsx Test5\test5query.txt
echo Finish generating queries for test 5.
echo Running AutoTester for test 5...
AutoTester Test5\test5source.txt Test5\test5query.txt TestResult\out5.xml > TestResult\cmd\cmd5.txt
echo Finish running AutoTester for test 5.
echo -------------------------------------------------------------------------------
echo Running AutoTester for test 6...
echo Running AutoTester for Demo_Calls...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_Calls.txt TestResult\out6_Demo_Calls.xml > TestResult\cmd\cmd6_Demo_Calls.txt
echo Finish running AutoTester for Demo_Calls.
echo Running AutoTester for Demo_CallsStar...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_CallsStar.txt TestResult\out6_Demo_CallsStar.xml > TestResult\cmd\cmd6_Demo_CallsStar.txt
echo Finish running AutoTester for Demo_CallsStar.
echo Running AutoTester for Demo_Follows...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_Follows.txt TestResult\out6_Demo_Follows.xml > TestResult\cmd\cmd6_Demo_Follows.txt
echo Finish running AutoTester for Demo_Follows.
echo Running AutoTester for Demo_FollowsStar...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_FollowsStar.txt TestResult\out6_Demo_FollowsStar.xml > TestResult\cmd\cmd6_Demo_FollowsStar.txt
echo Finish running AutoTester for Demo_FollowsStar.
echo Running AutoTester for Demo_Modifies...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_Modifies.txt TestResult\out6_Demo_Modifies.xml > TestResult\cmd\cmd6_Demo_Modifies.txt
echo Finish running AutoTester for Demo_Modifies.
echo Running AutoTester for Demo_Next...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_Next.txt TestResult\out6_Demo_Next.xml > TestResult\cmd\cmd6_Demo_Next.txt
echo Finish running AutoTester for Demo_Next.
echo Running AutoTester for Demo_NextStar...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_NextStar.txt TestResult\out6_Demo_NextStar.xml > TestResult\cmd\cmd6_Demo_NextStar.txt
echo Finish running AutoTester for Demo_NextStar.
echo Running AutoTester for Demo_Parent...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_Parent.txt TestResult\out6_Demo_Parent.xml > TestResult\cmd\cmd6_Demo_Parent.txt
echo Finish running AutoTester for Demo_Parent.
echo Running AutoTester for Demo_ParentStar...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_ParentStar.txt TestResult\out6_Demo_ParentStar.xml > TestResult\cmd\cmd6_Demo_ParentStar.txt
echo Finish running AutoTester for Demo_ParentStar.
echo Running AutoTester for Demo_Uses...
AutoTester Test6_Frozen\1_Demo\Demo_Source.txt Test6_Frozen\1_Demo\Demo_Uses.txt TestResult\out6_Demo_Uses.xml > TestResult\cmd\cmd6_Demo_Uses.txt
echo Finish running AutoTester for Demo_Uses.
echo Running AutoTester for CALLS_01...
AutoTester Test6_Frozen\2_Calls\CALLS_SOURCE_01.txt Test6_Frozen\2_Calls\CALLS_QUERIES_01.txt TestResult\out6_CALLS_01.xml > TestResult\cmd\cmd6_CALLS_01.txt
echo Finish running AutoTester for CALLS_01.
echo Running AutoTester for FOLLOWS_01...
AutoTester Test6_Frozen\3_Follows\FOLLOWS_SOURCE_01.txt Test6_Frozen\3_Follows\FOLLOWS_QUERIES_01.txt TestResult\out6_FOLLOWS.xml > TestResult\cmd\cmd6_FOLLOWS.txt
echo Finish running AutoTester for FOLLOWS_01.
echo Running AutoTester for MixTests01...
AutoTester Test6_Frozen\4_MixTests01\MixTestsSource01.txt Test6_Frozen\4_MixTests01\MixTestsQuery01.txt TestResult\out6_MixTests01.xml > TestResult\cmd\cmd6_MixTests01.txt
echo Finish running AutoTester for MixTests01.
echo Running AutoTester for MixTests02...
AutoTester Test6_Frozen\5_MixTests02\MixTestsSource02.txt Test6_Frozen\5_MixTests02\MixTestsQuery02.txt TestResult\out6_MixTests02.xml > TestResult\cmd\cmd6_MixTests02.txt
echo Finish running AutoTester for MixTests02.
echo Running AutoTester for ModifiesUsesParent...
AutoTester Test6_Frozen\6_ModifiesUsesParent\ModifiesUsesParentSource01.txt Test6_Frozen\6_ModifiesUsesParent\ModifiesUsesParentQuery01.txt TestResult\out6_ModifiesUsesParent.xml > TestResult\cmd\cmd6_ModifiesUsesParent.txt
echo Finish running AutoTester for ModifiesUsesParent.
echo Running AutoTester for MultipleRelationship01...
AutoTester Test6_Frozen\7_MultipleRelationship01\MultipleRelationshipSource01.txt Test6_Frozen\7_MultipleRelationship01\MultipleRelationshipQuery01.txt TestResult\out6_MultipleRelationship01.xml > TestResult\cmd\cmd6_MultipleRelationship01.txt
echo Finish running AutoTester for MultipleRelationship01.
echo Running AutoTester for MultipleRelationship02...
AutoTester Test6_Frozen\8_MultipleRelationship02\MultipleRelationshipSource02.txt Test6_Frozen\8_MultipleRelationship02\MultipleRelationshipQuery02.txt TestResult\out6_MultipleRelationship02.xml > TestResult\cmd\cmd6_MultipleRelationship02.txt
echo Finish running AutoTester for MultipleRelationship02.
echo Running AutoTester for Next...
AutoTester Test6_Frozen\9_Next\NEXT_SOURCE_01.txt Test6_Frozen\9_Next\NEXT_QUERIES_01.txt TestResult\out6_Next.xml > TestResult\cmd\cmd6_Next.txt
echo Finish running AutoTester for Next.
echo Running AutoTester for NextNextStar...
AutoTester Test6_Frozen\10_NextNextStar\NEXT-NEXT-STAR_SOURCE_01.txt Test6_Frozen\10_NextNextStar\NEXT-NEXT-STAR_QUERIES_01.txt TestResult\out6_NextNextStar.xml > TestResult\cmd\cmd6_NextNextStar.txt
echo Finish running AutoTester for NextNextStar.
echo Running AutoTester for NextStar...
AutoTester Test6_Frozen\11_NextStar\NEXT-STAR_SOURCE_01.txt Test6_Frozen\11_NextStar\NEXT-STAR_QUERIES_01.txt TestResult\out6_NextStar.xml > TestResult\cmd\cmd6_NextStar.txt
echo Finish running AutoTester for NextStar.
echo Running AutoTester for Pattern...
AutoTester Test6_Frozen\12_Pattern\PATTERN_SOURCE_01.txt Test6_Frozen\12_Pattern\PATTERN_QUERIES_01.txt TestResult\out6_Pattern.xml > TestResult\cmd\cmd6_Pattern.txt
echo Finish running AutoTester for Pattern.
echo Running AutoTester for Tuple...
AutoTester Test6_Frozen\13_Tuple\TUPLE_TESTS_SOURCE_01.txt Test6_Frozen\13_Tuple\TUPLE_TESTS_QUERIES_01.txt TestResult\out6_Tuple.xml > TestResult\cmd\cmd6_Tuple.txt
echo Finish running AutoTester for Tuple.
echo Running AutoTester for With...
AutoTester Test6_Frozen\14_With\WITH_SOURCE_01.txt Test6_Frozen\14_With\WITH_QUERIES_01.txt TestResult\out6_With.xml > TestResult\cmd\cmd6_With.txt
echo Finish running AutoTester for With.
echo Running AutoTester for Simple01...
AutoTester Test6_Frozen\15_Simple01\Simple01-Source.txt Test6_Frozen\15_Simple01\Simple01-Queries.txt TestResult\out6_Simple01.xml > TestResult\cmd\cmd6_Simple01.txt
echo Finish running AutoTester for Simple01.
echo Running AutoTester for Simple02...
AutoTester Test6_Frozen\16_Simple02\Simple02-Source.txt Test6_Frozen\16_Simple02\Simple02-Queries.txt TestResult\out6_Simple02.xml > TestResult\cmd\cmd6_Simple02.txt
echo Finish running AutoTester for Simple02.
echo Running AutoTester for Simple03...
AutoTester Test6_Frozen\17_Simple03\Simple03-Source.txt Test6_Frozen\17_Simple03\Simple03-Queries.txt TestResult\out6_Simple03.xml > TestResult\cmd\cmd6_Simple03.txt
echo Finish running AutoTester for Simple03.
echo Finish running AutoTester for test 6.
echo -------------------------------------------------------------------------------
echo Running AutoTester for test 7...
echo Test is still being written. Skipping to Test 8 ...
echo Finish running AutoTester for test 7.
echo -------------------------------------------------------------------------------
echo Running AutoTester for test 8...
AutoTester Test8_Frozen\Sample-Source.txt Test8_Frozen\Sample-Queries.txt TestResult\out8.xml > TestResult\cmd\cmd8_Sample.txt
echo Finish running AutoTester for test 8.
echo -------------------------------------------------------------------------------
echo Running AutoTester for test 9...
echo ...
echo Finish running AutoTester for test 9.
echo -------------------------------------------------------------------------------
echo Running AutoTester for test 10...
echo ...
echo Finish running AutoTester for test 10.
echo -------------------------------------------------------------------------------
echo Running AutoTester for test 11...
echo Running AutoTester for QueryFollows...
AutoTester Test11_Sequential\SourceWithNoLoop.txt Test11_Sequential\QueryFollows.txt TestResult\out11_QueryFollows.xml > TestResult\cmd\cmd11_QueryFollows.txt
echo Finish running AutoTester for QueryFollows.
echo Running AutoTester for QueryFollowsStar...
AutoTester Test11_Sequential\SourceWithNoLoop.txt Test11_Sequential\QueryFollowsStar.txt TestResult\out11_QueryFollowsStar.xml > TestResult\cmd\cmd11_QueryFollowsStar.txt
echo Finish running AutoTester for QueryFollowsStar.
echo Running AutoTester for QueryPatternAssign...
AutoTester Test11_Sequential\SourceWithNoLoop.txt Test11_Sequential\QueryPatternAssign.txt TestResult\out11_QueryPatternAssign.xml > TestResult\cmd\cmd11_QueryPatternAssign.txt
echo Finish running AutoTester for QueryPatternAssign.
echo Running AutoTester for QueryWith...
AutoTester Test11_Sequential\SourceWithNoLoop.txt Test11_Sequential\QueryWith.txt TestResult\out11_QueryWith.xml > TestResult\cmd\cmd11_QueryWith.txt
echo Finish running AutoTester for QueryWith.
echo Finish running AutoTester for test 11.
echo ===============================================================================
echo                           Finish Running AutoTester
echo ===============================================================================
pause
cls
goto :main