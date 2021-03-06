@echo off
:main
set isPause=1
echo ===============================================================================
echo Welcome to Team 11 static program analyzer. I am SpaXI.
echo ===============================================================================
echo Type the test index to run the test
echo [0] Receive a compliment
echo [s] Run AutoTester for specified test path
echo [a] Run All Tests
echo [?] Run Predefined Test #?
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
	goto :runTest6
)
if '%option%'=='7' (
	goto :runTest7
)
if '%option%'=='8' (
	goto :runTest8
)
if '%option%'=='9' (
	goto :runTest9
)
if '%option%'=='10' (
	goto :runTest10
)
if '%option%'=='11' (
	goto :runTest11
)
if '%option%'=='12' (
	goto :runTest12
)
if '%option%'=='13' (
	goto :runTest13
)
if '%option%'=='14' (
	goto :runTest14
)
if '%option%'=='15' (
	goto :runTest15
)
if '%option%'=='16' (
	goto :runTest16
)
if '%option%'=='17' (
	goto :runTest17
)
if '%option%'=='18' (
	goto :runTest18
)
if '%option%'=='19' (
	goto :runTest19
)
if '%option%'=='20' (
	goto :runTest20
)
if '%option%'=='21' (
	goto :runTest21
)
if '%option%'=='22' (
	goto :runTest22
)
if '%option%'=='23' (
	goto :runTest23
)
if '%option%'=='24' (
	goto :runTest24
)
cls
goto :main
echo ===============================================================================

:close
goto eof

:getPauseAction
if %isPause%==1 (
	pause
	cls
	goto :main
)
goto :eof

:clearAllResultFiles
if exist TestResult\cmd\*.txt (
	del TestResult\cmd\*.txt
)
if exist TestResult\*.xml (
	del TestResult\*.xml
)
if exist TestResult\Summary.txt (
	del TestResult\Summary.txt
)
goto :eof

:createCmdOutputFolder
if not exist TestResult\cmd (
	mkdir TestResult\cmd
)
goto :eof

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
set isPause=0 
call :clearAllResultFiles
echo ===============================================================================
echo                           Start Running AutoTester
echo ===============================================================================
call :runTest1
call :runTest2
call :runTest3
call :runTest4
call :runTest5
call :runTest6
call :runTest7
call :runTest8
call :runTest9
call :runTest10
call :runTest11
call :runTest12
call :runTest13
call :runTest14
call :runTest15
call :runTest16
call :runTest17
call :runTest18
call :runTest19
call :runTest20
call :runTest21
call :runTest22
call :runTest23
call :runTest24
echo ===============================================================================
echo                           Finish Running AutoTester
echo ===============================================================================
echo Generating Summary ...
python TestResult\GenerateResultSummary.py TestResult TestResult\Summary.txt
echo Summary Generated.
start TestResult\Summary.txt
pause
cls
goto :main

:runTest1
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 1...
AutoTester Test1_Frozen\test1source.txt Test1_Frozen\test1query.txt TestResult\out1.xml > TestResult\cmd\cmd1.txt
echo Finish running AutoTester for test 1.
call :getPauseAction
goto :eof

:runTest2
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 2...
AutoTester Test2_Frozen\Source_Simple02.txt Test2_Frozen\Query_Simple02.txt TestResult\out2_Query_Simple02.xml > TestResult\cmd\cmd2_Query_Simple02.txt
echo Finish running AutoTester for test 2.
call :getPauseAction
goto :eof

:runTest3
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 3...
AutoTester Test3_Frozen\test3source.txt Test3_Frozen\test3query.txt TestResult\out3.xml > TestResult\cmd\cmd3.txt
echo Finish running AutoTester for test 3.
call :getPauseAction
goto :eof

:runTest4
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 4...
echo Running AutoTester for test 4_0...
AutoTester Test4_Frozen\test4source0.txt Test4_Frozen\test4query0.txt TestResult\out4_0.xml > TestResult\cmd\cmd4_0.txt
echo Finish running AutoTester for test 4_0.
echo Running AutoTester for test 4_1...
AutoTester Test4_Frozen\test4source1.txt Test4_Frozen\test4query1.txt TestResult\out4_1.xml > TestResult\cmd\cmd4_1.txt
echo Finish running AutoTester for test 4_1.
echo Running AutoTester for test 4_2...
AutoTester Test4_Frozen\test4source2.txt Test4_Frozen\test4query2.txt TestResult\out4_2.xml > TestResult\cmd\cmd4_2.txt
echo Finish running AutoTester for test 4_2.
echo Finish running AutoTester for test 4.
call :getPauseAction
goto :eof

:runTest5
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 5...
AutoTester Test5\test5source.txt Test5\test5query.txt TestResult\out5.xml > TestResult\cmd\cmd5.txt
echo Finish running AutoTester for test 5.
call :getPauseAction
goto :eof

:runTest6
call :createCmdOutputFolder
echo ===============================================================================
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
call :getPauseAction
goto :eof

:runTest7
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 7...
AutoTester Test7_Animal\Source_Simple01.txt Test7_Animal\Query_Simple01.txt TestResult\out7_Query_Simple01.xml > TestResult\cmd\cmd7_Query_Simple01.txt
echo Finish running AutoTester for test 7.
call :getPauseAction
goto :eof

:runTest8
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 8...
AutoTester Test8_Frozen\Sample-Source.txt Test8_Frozen\Sample-Queries.txt TestResult\out8.xml > TestResult\cmd\cmd8_Sample.txt
echo Finish running AutoTester for test 8.
call :getPauseAction
goto :eof

:runTest9
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 9...
echo Running AutoTester for QueryAffects.txt...
AutoTester Test9_InterProcedural\SourceInterProcedural.txt Test9_InterProcedural\QueryAffects.txt TestResult\out9_QueryAffects.xml > TestResult\cmd\cmd9_QueryAffects.txt
echo Finish running AutoTester for QueryAffects.txt.
echo Running AutoTester for QueryAffectsStar.txt...
AutoTester Test9_InterProcedural\SourceInterProcedural.txt Test9_InterProcedural\QueryAffectsStar.txt TestResult\out9_QueryAffectsStar.xml > TestResult\cmd\cmd9_QueryAffectsStar.txt
echo Finish running AutoTester for QueryAffectsStar.txt.
echo Running AutoTester for QueryCalls.txt...
AutoTester Test9_InterProcedural\SourceInterProcedural.txt Test9_InterProcedural\QueryCalls.txt TestResult\out9_QueryCalls.xml > TestResult\cmd\cmd9_QueryCalls.txt
echo Finish running AutoTester for QueryCalls.txt.
echo Running AutoTester for QueryCallsStar.txt...
AutoTester Test9_InterProcedural\SourceInterProcedural.txt Test9_InterProcedural\QueryCallsStar.txt TestResult\out9_QueryCallsStar.xml > TestResult\cmd\cmd9_QueryCallsStar.txt
echo Finish running AutoTester for QueryCallsStar.txt.
echo Running AutoTester for QueryModifies.txt...
AutoTester Test9_InterProcedural\SourceInterProcedural.txt Test9_InterProcedural\QueryModifies.txt TestResult\out9_QueryModifies.xml > TestResult\cmd\cmd9_QueryModifies.txt
echo Finish running AutoTester for QueryModifies.txt.
echo Running AutoTester for QueryNext.txt...
AutoTester Test9_InterProcedural\SourceInterProcedural.txt Test9_InterProcedural\QueryNext.txt TestResult\out9_QueryNext.xml > TestResult\cmd\cmd9_QueryNext.txt
echo Finish running AutoTester for QueryNext.txt.
echo Running AutoTester for QueryNextStar.txt...
AutoTester Test9_InterProcedural\SourceInterProcedural.txt Test9_InterProcedural\QueryNextStar.txt TestResult\out9_QueryNextStar.xml > TestResult\cmd\cmd9_QueryNextStar.txt
echo Finish running AutoTester for QueryNextStar.txt.
echo Running AutoTester for QueryUses.txt...
AutoTester Test9_InterProcedural\SourceInterProcedural.txt Test9_InterProcedural\QueryUses.txt TestResult\out9_QueryUses.xml > TestResult\cmd\cmd9_QueryUses.txt
echo Finish running AutoTester for QueryUses.txt.
echo Finish running AutoTester for test 9.
call :getPauseAction
goto :eof

:runTest10
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 10...
echo Running AutoTester for QueryAffects.txt...
AutoTester Test10_Loop\SourceLoop.txt Test10_Loop\QueryAffects.txt TestResult\out10_QueryAffects.xml > TestResult\cmd\cmd10_QueryAffects.txt
echo Finish running AutoTester for QueryAffects.txt.
echo Running AutoTester for QueryAffectsStar.txt...
AutoTester Test10_Loop\SourceLoop.txt Test10_Loop\QueryAffectsStar.txt TestResult\out10_QueryAffectsStar.xml > TestResult\cmd\cmd10_QueryAffectsStar.txt
echo Finish running AutoTester for QueryAffectsStar.txt.
echo Running AutoTester for QueryModifies.txt...
AutoTester Test10_Loop\SourceLoop.txt Test10_Loop\QueryModifies.txt TestResult\out10_QueryModifies.xml > TestResult\cmd\cmd10_QueryModifies.txt
echo Finish running AutoTester for QueryModifies.txt.
echo Running AutoTester for QueryNext.txt...
AutoTester Test10_Loop\SourceLoop.txt Test10_Loop\QueryNext.txt TestResult\out10_QueryNext.xml > TestResult\cmd\cmd10_QueryNext.txt
echo Finish running AutoTester for QueryNext.txt.
echo Running AutoTester for QueryNextStar.txt...
AutoTester Test10_Loop\SourceLoop.txt Test10_Loop\QueryNextStar.txt TestResult\out10_QueryNextStar.xml > TestResult\cmd\cmd10_QueryNextStar.txt
echo Finish running AutoTester for QueryNextStar.txt.
echo Running AutoTester for QueryParent.txt...
AutoTester Test10_Loop\SourceLoop.txt Test10_Loop\QueryParent.txt TestResult\out10_QueryParent.xml > TestResult\cmd\cmd10_QueryParent.txt
echo Finish running AutoTester for QueryParent.txt.
echo Running AutoTester for QueryParentStar.txt...
AutoTester Test10_Loop\SourceLoop.txt Test10_Loop\QueryParentStar.txt TestResult\out10_QueryParentStar.xml > TestResult\cmd\cmd10_QueryParentStar.txt
echo Finish running AutoTester for QueryParentStar.txt.
echo Running AutoTester for QueryPattern.txt...
AutoTester Test10_Loop\SourceLoop.txt Test10_Loop\QueryPattern.txt TestResult\out10_QueryPattern.xml > TestResult\cmd\cmd10_QueryPattern.txt
echo Finish running AutoTester for QueryPattern.txt.
echo Running AutoTester for QueryUses.txt...
AutoTester Test10_Loop\SourceLoop.txt Test10_Loop\QueryUses.txt TestResult\out10_QueryUses.xml > TestResult\cmd\cmd10_QueryUses.txt
echo Finish running AutoTester for QueryUses.txt.
echo Finish running AutoTester for test 10.
call :getPauseAction
goto :eof

:runTest11
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 11...
echo Running AutoTester for QueryFollows...
AutoTester Test11_Sequential\SourceSequential.txt Test11_Sequential\QueryFollows.txt TestResult\out11_QueryFollows.xml > TestResult\cmd\cmd11_QueryFollows.txt
echo Finish running AutoTester for QueryFollows.
echo Running AutoTester for QueryFollowsStar...
AutoTester Test11_Sequential\SourceSequential.txt Test11_Sequential\QueryFollowsStar.txt TestResult\out11_QueryFollowsStar.xml > TestResult\cmd\cmd11_QueryFollowsStar.txt
echo Finish running AutoTester for QueryFollowsStar.
echo Running AutoTester for QueryPatternAssign...
AutoTester Test11_Sequential\SourceSequential.txt Test11_Sequential\QueryPatternAssign.txt TestResult\out11_QueryPatternAssign.xml > TestResult\cmd\cmd11_QueryPatternAssign.txt
echo Finish running AutoTester for QueryPatternAssign.
echo Running AutoTester for QueryWith...
AutoTester Test11_Sequential\SourceSequential.txt Test11_Sequential\QueryWith.txt TestResult\out11_QueryWith.xml > TestResult\cmd\cmd11_QueryWith.txt
echo Finish running AutoTester for QueryWith.
echo Finish running AutoTester for test 11.
call :getPauseAction
goto :eof

:runTest12
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 12...
echo Running AutoTester for QueryComplexNext.txt...
AutoTester Test12_ComplexNext\SourceComplexNext.txt Test12_ComplexNext\QueryComplexNext.txt TestResult\out12_QueryComplexNext.xml > TestResult\cmd\cmd12_QueryComplexNext.txt
echo Finish running AutoTester for QueryComplexNext.txt.
echo Running AutoTester for QueryComplexNextStar.txt...
AutoTester Test12_ComplexNext\SourceComplexNext.txt Test12_ComplexNext\QueryComplexNextStar.txt TestResult\out12_QueryComplexNextStar.xml > TestResult\cmd\cmd12_QueryComplexNextStar.txt
echo Finish running AutoTester for QueryComplexNextStar.txt.
echo Finish running AutoTester for test 12.
call :getPauseAction
goto :eof

:runTest13
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 13...
echo Finish running AutoTester for test 13.
echo Running AutoTester for Query1.txt...
AutoTester Test13_Seven\1_One\source1.txt Test13_Seven\1_One\query1.txt TestResult\out13_One_Query1.xml > TestResult\cmd\cmd13_One_Query1.txt
echo Finish running AutoTester for Query1.txt.
echo Running AutoTester for Query2.txt...
AutoTester Test13_Seven\1_One\source2.txt Test13_Seven\1_One\query2.txt TestResult\out13_One_Query2.xml > TestResult\cmd\cmd13_One_Query2.txt
echo Finish running AutoTester for Query2.txt.
echo Running AutoTester for Query3.txt...
AutoTester Test13_Seven\1_One\source3.txt Test13_Seven\1_One\query3.txt TestResult\out13_One_Query3.xml > TestResult\cmd\cmd13_One_Query3.txt
echo Finish running AutoTester for Query3.txt.
echo Running AutoTester for Query_With_ST_UsingSource2.txt...
AutoTester Test13_Seven\2_Two\Source2.txt Test13_Seven\2_Two\Query_With_ST_UsingSource2.txt TestResult\out13_Two_Query_With_ST_UsingSource2.xml > TestResult\cmd\cmd13_Two_Query_With_ST_UsingSource2.txt
echo Finish running AutoTester for Query_With_ST_UsingSource2.txt.
echo Running AutoTester for QueryAffects1_UsingSourceAffects.txt...
AutoTester Test13_Seven\2_Two\SourceAffects.txt Test13_Seven\2_Two\QueryAffects1_UsingSourceAffects.txt TestResult\out13_Two_QueryAffects1_UsingSourceAffects.xml > TestResult\cmd\cmd13_Two_QueryAffects1_UsingSourceAffects.txt
echo Finish running AutoTester for QueryAffects1_UsingSourceAffects.txt.
echo Running AutoTester for QueryAffects2_UsingSourceAffects.txt...
AutoTester Test13_Seven\2_Two\SourceAffects.txt Test13_Seven\2_Two\QueryAffects2_UsingSourceAffects.txt TestResult\out13_Two_QueryAffects2_UsingSourceAffects.xml > TestResult\cmd\cmd13_Two_QueryAffects2_UsingSourceAffects.txt
echo Finish running AutoTester for QueryAffects2_UsingSourceAffects.txt.
echo Running AutoTester for QueryCalls_UsingSource1.txt...
AutoTester Test13_Seven\2_Two\Source1.txt Test13_Seven\2_Two\QueryCalls_UsingSource1.txt TestResult\out13_Two_QueryCalls_UsingSource1.xml > TestResult\cmd\cmd13_Two_QueryCalls_UsingSource1.txt
echo Finish running AutoTester for QueryCalls_UsingSource1.txt.
echo Running AutoTester for QueryCallsStar_UsingSource1.txt...
AutoTester Test13_Seven\2_Two\Source1.txt Test13_Seven\2_Two\QueryCallsStar_UsingSource1.txt TestResult\out13_Two_QueryCallsStar_UsingSource1.xml > TestResult\cmd\cmd13_Two_QueryCallsStar_UsingSource1.txt
echo Finish running AutoTester for QueryCallsStar_UsingSource1.txt.
echo Running AutoTester for QueryFollows_UsingSource2.txt...
AutoTester Test13_Seven\2_Two\Source2.txt Test13_Seven\2_Two\QueryFollows_UsingSource2.txt TestResult\out13_Two_QueryFollows_UsingSource2.xml > TestResult\cmd\cmd13_Two_QueryFollows_UsingSource2.txt
echo Finish running AutoTester for QueryFollows_UsingSource2.txt.
echo Running AutoTester for QueryFollowsStar_UsingSource2.txt...
AutoTester Test13_Seven\2_Two\Source2.txt Test13_Seven\2_Two\QueryFollowsStar_UsingSource2.txt TestResult\out13_Two_QueryFollowsStar_UsingSource2.xml > TestResult\cmd\cmd13_Two_QueryFollowsStar_UsingSource2.txt
echo Finish running AutoTester for QueryFollowsStar_UsingSource2.txt.
echo Running AutoTester for QueryModifies_UsingSource1.txt...
AutoTester Test13_Seven\2_Two\Source1.txt Test13_Seven\2_Two\QueryModifies_UsingSource1.txt TestResult\out13_Two_QueryModifies_UsingSource1.xml > TestResult\cmd\cmd13_Two_QueryModifies_UsingSource1.txt
echo Finish running AutoTester for QueryModifies_UsingSource1.txt.
echo Running AutoTester for QueryMultiple_ST_Pattern_UsingSource2.txt...
AutoTester Test13_Seven\2_Two\Source2.txt Test13_Seven\2_Two\QueryMultiple_ST_Pattern_UsingSource2.txt TestResult\out13_Two_QueryMultiple_ST_Pattern_UsingSource2.xml > TestResult\cmd\cmd13_Two_QueryMultiple_ST_Pattern_UsingSource2.txt
echo Finish running AutoTester for QueryMultiple_ST_Pattern_UsingSource2.txt.
echo Running AutoTester for QueryMultipleClauses_UsingSource2.txt...
AutoTester Test13_Seven\2_Two\Source2.txt Test13_Seven\2_Two\QueryMultipleClauses_UsingSource2.txt TestResult\out13_Two_QueryMultipleClauses_UsingSource2.xml > TestResult\cmd\cmd13_Two_QueryMultipleClauses_UsingSource2.txt
echo Finish running AutoTester for QueryMultipleClauses_UsingSource2.txt.
echo Running AutoTester for QueryMultipleST_UsingSource2.txt...
AutoTester Test13_Seven\2_Two\Source2.txt Test13_Seven\2_Two\QueryMultipleST_UsingSource2.txt TestResult\out13_Two_QueryMultipleST_UsingSource2.xml > TestResult\cmd\cmd13_Two_QueryMultipleST_UsingSource2.txt
echo Finish running AutoTester for QueryMultipleST_UsingSource2.txt.
echo Running AutoTester for QueryNext_UsingSourceNext.txt...
AutoTester Test13_Seven\2_Two\SourceNext.txt Test13_Seven\2_Two\QueryNext_UsingSourceNext.txt TestResult\out13_Two_QueryNext_UsingSourceNext.xml > TestResult\cmd\cmd13_Two_QueryNext_UsingSourceNext.txt
echo Finish running AutoTester for QueryNext_UsingSourceNext.txt.
echo Running AutoTester for QueryNextStar_Performance_UsingSource2.txt...
AutoTester Test13_Seven\2_Two\Source2.txt Test13_Seven\2_Two\QueryNextStar_Performance_UsingSource2.txt TestResult\out13_Two_QueryNextStar_Performance_UsingSource2.xml > TestResult\cmd\cmd13_Two_QueryNextStar_Performance_UsingSource2.txt
echo Finish running AutoTester for QueryNextStar_Performance_UsingSource2.txt.
REM echo -- TIMEOUT! -- QueryNextStar_Performance_UsingSource2.txt has been commented away in the bat file -- ! --
echo Running AutoTester for QueryNextStar_UsingSourceNext.txt...
AutoTester Test13_Seven\2_Two\SourceNext.txt Test13_Seven\2_Two\QueryNextStar_UsingSourceNext.txt TestResult\out13_Two_QueryNextStar_UsingSourceNext.xml > TestResult\cmd\cmd13_Two_QueryNextStar_UsingSourceNext.txt
echo Finish running AutoTester for QueryNextStar_UsingSourceNext.txt.
echo Running AutoTester for QueryParentStar_UsingSource2.txt...
AutoTester Test13_Seven\2_Two\Source2.txt Test13_Seven\2_Two\QueryParentStar_UsingSource2.txt TestResult\out13_Two_QueryParentStar_UsingSource2.xml > TestResult\cmd\cmd13_Two_QueryParentStar_UsingSource2.txt
echo Finish running AutoTester for QueryParentStar_UsingSource2.txt.
echo Running AutoTester for QueryParent_UsingSource2.txt...
AutoTester Test13_Seven\2_Two\Source2.txt Test13_Seven\2_Two\QueryParent_UsingSource2.txt TestResult\out13_Two_QueryParent_UsingSource2.xml > TestResult\cmd\cmd13_Two_QueryParent_UsingSource2.txt
echo Finish running AutoTester for QueryParent_UsingSource2.txt.
echo Running AutoTester for QueryPattern_UsingSourcePattern.txt...
AutoTester Test13_Seven\2_Two\SourcePattern.txt Test13_Seven\2_Two\QueryPattern_UsingSourcePattern.txt TestResult\out13_Two_QueryPattern_UsingSourcePattern.xml > TestResult\cmd\cmd13_Two_QueryPattern_UsingSourcePattern.txt
echo Finish running AutoTester for QueryPattern_UsingSourcePattern.txt.
echo Running AutoTester for QueryUses_UsingSource1.txt...
AutoTester Test13_Seven\2_Two\Source1.txt Test13_Seven\2_Two\QueryUses_UsingSource1.txt TestResult\out13_Two_QueryUses_UsingSource1.xml > TestResult\cmd\cmd13_Two_QueryUses_UsingSource1.txt
echo Finish running AutoTester for QueryUses_UsingSource1.txt.
echo Running AutoTester for QueryWith_UsingSource1.txt...
AutoTester Test13_Seven\2_Two\Source1.txt Test13_Seven\2_Two\QueryWith_UsingSource1.txt TestResult\out13_Two_QueryWith_UsingSource1.xml > TestResult\cmd\cmd13_Two_QueryWith_UsingSource1.txt
echo Finish running AutoTester for QueryWith_UsingSource1.txt.
echo Running AutoTester for Query_Affects_AffectsStar_UsingSource4.txt...
AutoTester Test13_Seven\3_Three\Source4.txt Test13_Seven\3_Three\Query_Affects_AffectsStar_UsingSource4.txt TestResult\out13_Three_Query_Affects_AffectsStar_UsingSource4.xml > TestResult\cmd\cmd13_Three_Query_Affects_AffectsStar_UsingSource4.txt
echo Finish running AutoTester for Query_Affects_AffectsStar_UsingSource4.txt.
echo Running AutoTester for Query_Calls_CallsStar_UsingSource4.txt...
AutoTester Test13_Seven\3_Three\Source4.txt Test13_Seven\3_Three\Query_Calls_CallsStar_UsingSource4.txt TestResult\out13_Three_Query_Calls_CallsStar_UsingSource4.xml > TestResult\cmd\cmd13_Three_Query_Calls_CallsStar_UsingSource4.txt
echo Finish running AutoTester for Query_Calls_CallsStar_UsingSource4.txt.
echo Running AutoTester for Query_Next_NextStar_UsingSource4.txt...
AutoTester Test13_Seven\3_Three\Source4.txt Test13_Seven\3_Three\Query_Next_NextStar_UsingSource4.txt TestResult\out13_Three_Query_Next_NextStar_UsingSource4.xml > TestResult\cmd\cmd13_Three_Query_Next_NextStar_UsingSource4.txt
echo Finish running AutoTester for Query_Next_NextStar_UsingSource4.txt.
echo Running AutoTester for QueryAffects_UsingSource3.txt...
AutoTester Test13_Seven\3_Three\Source3.txt Test13_Seven\3_Three\QueryAffects_UsingSource3.txt TestResult\out13_Three_QueryAffects_UsingSource3.xml > TestResult\cmd\cmd13_Three_QueryAffects_UsingSource3.txt
echo Finish running AutoTester for QueryAffects_UsingSource3.txt.
echo Running AutoTester for QueryLongTestCase.txt...
AutoTester Test13_Seven\3_Three\SourceLongTestCase.txt Test13_Seven\3_Three\QueryLongTestCase.txt TestResult\out13_Three_QueryLongTestCase.xml > TestResult\cmd\cmd13_Three_QueryLongTestCase.txt
echo Finish running AutoTester for QueryLongTestCase.txt.
echo Running AutoTester for QueryMultipleClauses_UsingSource5.txt...
AutoTester Test13_Seven\3_Three\Source5.txt Test13_Seven\3_Three\QueryMultipleClauses_UsingSource5.txt TestResult\out13_Three_QueryMultipleClauses_UsingSource5.xml > TestResult\cmd\cmd13_Three_QueryMultipleClauses_UsingSource5.txt
echo Finish running AutoTester for QueryMultipleClauses_UsingSource5.txt.
echo Running AutoTester for QueryOptimization_UsingSource3.txt...
AutoTester Test13_Seven\3_Three\Source3.txt Test13_Seven\3_Three\QueryOptimization_UsingSource3.txt TestResult\out13_Three_QueryOptimization_UsingSource3.xml > TestResult\cmd\cmd13_Three_QueryOptimization_UsingSource3.txt
echo Finish running AutoTester for QueryOptimization_UsingSource3.txt.
echo Running AutoTester for Query1.txt...
AutoTester Test13_Seven\4_Intense\Source1.txt Test13_Seven\4_Intense\Query1.txt TestResult\out13_Intense_Query1.xml > TestResult\cmd\cmd13_Intense_Query1.txt
echo Finish running AutoTester for Query1.txt.
echo Running AutoTester for Query2.txt...
AutoTester Test13_Seven\4_Intense\Source2.txt Test13_Seven\4_Intense\Query2.txt TestResult\out13_Intense_Query2.xml > TestResult\cmd\cmd13_Intense_Query2.txt
echo Finish running AutoTester for Query2.txt.
echo Running AutoTester for Query3.txt...
AutoTester Test13_Seven\4_Intense\Source3.txt Test13_Seven\4_Intense\Query3.txt TestResult\out13_Intense_Query3.xml > TestResult\cmd\cmd13_Intense_Query3.txt
echo Finish running AutoTester for Query3.txt.
echo Running AutoTester for Query4.txt...
AutoTester Test13_Seven\4_Intense\Source4.txt Test13_Seven\4_Intense\Query4.txt TestResult\out13_Intense_Query4.xml > TestResult\cmd\cmd13_Intense_Query4.txt
echo Finish running AutoTester for Query4.txt.
REM echo -- TIMEOUT! -- Query4.txt has been commented away in the bat file -- ! --
echo Running AutoTester for Query5.txt...
AutoTester Test13_Seven\4_Intense\Source5.txt Test13_Seven\4_Intense\Query5.txt TestResult\out13_Intense_Query5.xml > TestResult\cmd\cmd13_Intense_Query5.txt
echo Finish running AutoTester for Query5.txt.
echo Running AutoTester for Query6a.txt...
AutoTester Test13_Seven\4_Intense\Source6.txt Test13_Seven\4_Intense\Query6a.txt TestResult\out13_Intense_Query6a.xml > TestResult\cmd\cmd13_Intense_Query6a.txt
echo Finish running AutoTester for Query6a.txt.
echo Running AutoTester for Query6b.txt...
AutoTester Test13_Seven\4_Intense\Source6.txt Test13_Seven\4_Intense\Query6b.txt TestResult\out13_Intense_Query6b.xml > TestResult\cmd\cmd13_Intense_Query6b.txt
echo Finish running AutoTester for Query6b.txt.
echo Running AutoTester for Query7a.txt...
AutoTester Test13_Seven\4_Intense\Source7.txt Test13_Seven\4_Intense\Query7a.txt TestResult\out13_Intense_Query7a.xml > TestResult\cmd\cmd13_Intense_Query7a.txt
echo Finish running AutoTester for Query7a.txt.
echo Running AutoTester for Query7b.txt...
AutoTester Test13_Seven\4_Intense\Source7.txt Test13_Seven\4_Intense\Query7b.txt TestResult\out13_Intense_Query7b.xml > TestResult\cmd\cmd13_Intense_Query7b.txt
echo Finish running AutoTester for Query7b.txt.
echo Running AutoTester for Query8.txt...
AutoTester Test13_Seven\4_Intense\Source8.txt Test13_Seven\4_Intense\Query8.txt TestResult\out13_Intense_Query8.xml > TestResult\cmd\cmd13_Intense_Query8.txt
echo Finish running AutoTester for Query8.txt.
echo Finish running AutoTester for test 13.
call :getPauseAction
goto :eof

:runTest14
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 14...
echo Running AutoTester for Query1a.txt...
AutoTester Test14_Frozen\Source1a.txt Test14_Frozen\Query1a.txt TestResult\out14_Query1a.xml > TestResult\cmd\cmd14_Query1a.txt
echo Finish running AutoTester for Query1a.txt.
echo Running AutoTester for Query1b.txt...
AutoTester Test14_Frozen\Source1b.txt Test14_Frozen\Query1b.txt TestResult\out14_Query1b.xml > TestResult\cmd\cmd14_Query1b.txt
echo Finish running AutoTester for Query1b.txt.
echo Running AutoTester for Query2a.txt...
AutoTester Test14_Frozen\Source2a.txt Test14_Frozen\Query2a.txt TestResult\out14_Query2a.xml > TestResult\cmd\cmd14_Query2a.txt
echo Finish running AutoTester for Query2a.txt.
echo Running AutoTester for Query2b.txt...
AutoTester Test14_Frozen\Source2b.txt Test14_Frozen\Query2b.txt TestResult\out14_Query2b.xml > TestResult\cmd\cmd14_Query2b.txt
echo Finish running AutoTester for Query2b.txt.
echo Running AutoTester for Query3a.txt...
AutoTester Test14_Frozen\Source3a.txt Test14_Frozen\Query3a.txt TestResult\out14_Query3a.xml > TestResult\cmd\cmd14_Query3a.txt
echo Finish running AutoTester for Query3a.txt.
echo Running AutoTester for Query3b.txt...
AutoTester Test14_Frozen\Source3b.txt Test14_Frozen\Query3b.txt TestResult\out14_Query3b.xml > TestResult\cmd\cmd14_Query3b.txt
REM echo -- TIMEOUT! -- Query3b.txt has been commented away in the bat file -- ! --
echo Finish running AutoTester for Query3b.txt.
echo Running AutoTester for Query4a.txt...
AutoTester Test14_Frozen\Source4a.txt Test14_Frozen\Query4a.txt TestResult\out14_Query4a.xml > TestResult\cmd\cmd14_Query4a.txt
echo Finish running AutoTester for Query4a.txt.
echo Running AutoTester for Query4b.txt...
AutoTester Test14_Frozen\Source4b.txt Test14_Frozen\Query4b.txt TestResult\out14_Query4b.xml > TestResult\cmd\cmd14_Query4b.txt
echo Finish running AutoTester for Query4b.txt.
echo Running AutoTester for Query5b.txt...
AutoTester Test14_Frozen\Source5b.txt Test14_Frozen\Query5b.txt TestResult\out14_Query5b.xml > TestResult\cmd\cmd14_Query5b.txt
echo Finish running AutoTester for Query5b.txt.
echo Running AutoTester for Query6Calls_UsingSource6.txt...
AutoTester Test14_Frozen\Source6.txt Test14_Frozen\Query6Calls_UsingSource6.txt TestResult\out14_Query6Calls_UsingSource6.xml > TestResult\cmd\cmd14_Query6Calls_UsingSource6.txt
echo Finish running AutoTester for Query6Calls_UsingSource6.txt.
echo Running AutoTester for Query6Follows_UsingSource6.txt...
AutoTester Test14_Frozen\Source6.txt Test14_Frozen\Query6Follows_UsingSource6.txt TestResult\out14_Query6Follows_UsingSource6.xml > TestResult\cmd\cmd14_Query6Follows_UsingSource6.txt
echo Finish running AutoTester for Query6Follows_UsingSource6.txt.
echo Running AutoTester for Query6Modifies_UsingSource6.txt...
AutoTester Test14_Frozen\Source6.txt Test14_Frozen\Query6Modifies_UsingSource6.txt TestResult\out14_Query6Modifies_UsingSource6.xml > TestResult\cmd\cmd14_Query6Modifies_UsingSource6.txt
echo Finish running AutoTester for Query6Modifies_UsingSource6.txt.
echo Running AutoTester for Query6MultipleClause_UsingSource6.txt...
AutoTester Test14_Frozen\Source6.txt Test14_Frozen\Query6MultipleClause_UsingSource6.txt TestResult\out14_Query6MultipleClause_UsingSource6.xml > TestResult\cmd\cmd14_Query6MultipleClause_UsingSource6.txt
echo Finish running AutoTester for Query6MultipleClause_UsingSource6.txt.
echo Running AutoTester for Query6Parent_UsingSource6.txt...
AutoTester Test14_Frozen\Source6.txt Test14_Frozen\Query6Parent_UsingSource6.txt TestResult\out14_Query6Parent_UsingSource6.xml > TestResult\cmd\cmd14_Query6Parent_UsingSource6.txt
echo Finish running AutoTester for Query6Parent_UsingSource6.txt.
echo Running AutoTester for Query6Uses_UsingSource6.txt...
AutoTester Test14_Frozen\Source6.txt Test14_Frozen\Query6Uses_UsingSource6.txt TestResult\out14_Query6Uses_UsingSource6.xml > TestResult\cmd\cmd14_Query6Uses_UsingSource6.txt
echo Finish running AutoTester for Query6Uses_UsingSource6.txt.
echo Finish running AutoTester for test 14.
call :getPauseAction
goto :eof

:runTest15
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 15...
echo Running AutoTester for Query_Test1 ...
AutoTester Test15_Verb\Acceptance\Source_prog_1.txt Test15_Verb\Acceptance\Query_Test1.txt TestResult\out15_Acceptance_Query_Test1.xml > TestResult\cmd\cmd15_Acceptance_Query_Test1.txt
echo Finish running AutoTester for Query_Test1.
echo Running AutoTester for Query_Test2 ...
AutoTester Test15_Verb\Acceptance\Source_prog_2.txt Test15_Verb\Acceptance\Query_Test2.txt TestResult\out15_Acceptance_Query_Test2.xml > TestResult\cmd\cmd15_Acceptance_Query_Test2.txt
echo Finish running AutoTester for Query_Test2.
echo Running AutoTester for Query_Test3 ...
AutoTester Test15_Verb\Acceptance\Source_prog_3.txt Test15_Verb\Acceptance\Query_Test3.txt TestResult\out15_Acceptance_Query_Test3.xml > TestResult\cmd\cmd15_Acceptance_Query_Test3.txt
echo Finish running AutoTester for Query_Test3.
echo Running AutoTester for Query_Test4 ...
AutoTester Test15_Verb\Acceptance\Source_prog_4.txt Test15_Verb\Acceptance\Query_Test4.txt TestResult\out15_Acceptance_Query_Test4.xml > TestResult\cmd\cmd15_Acceptance_Query_Test4.txt
echo Finish running AutoTester for Query_Test4.
echo Running AutoTester for Query_Test5 ...
AutoTester Test15_Verb\Acceptance\Source_prog_5.txt Test15_Verb\Acceptance\Query_Test5.txt TestResult\out15_Acceptance_Query_Test5.xml > TestResult\cmd\cmd15_Acceptance_Query_Test5.txt
echo Finish running AutoTester for Query_Test5.
echo Running AutoTester for QueryStmtLst ...
AutoTester Test15_Verb\Acceptance\SourceStmtLst_prog.txt Test15_Verb\Acceptance\QueryStmtLst.txt TestResult\out15_Acceptance_QueryStmtLst.xml > TestResult\cmd\cmd15_Acceptance_QueryStmtLst.txt
echo Finish running AutoTester for QueryStmtLst.
echo Running AutoTester for QueryAffects1_UsingSource2 ...
AutoTester Test15_Verb\Regression\Source2.txt Test15_Verb\Regression\QueryAffects1_UsingSource2.txt TestResult\out15_Regression_QueryAffects1_UsingSource2.xml > TestResult\cmd\cmd15_Regression_QueryAffects1_UsingSource2.txt
echo Finish running AutoTester for QueryAffects1_UsingSource2.
echo Running AutoTester for QueryBoolean1_UsingSource1 ...
AutoTester Test15_Verb\Regression\Source1.txt Test15_Verb\Regression\QueryBoolean1_UsingSource1.txt TestResult\out15_Regression_QueryBoolean1_UsingSource1.xml > TestResult\cmd\cmd15_Regression_QueryBoolean1_UsingSource1.txt
echo Finish running AutoTester for QueryBoolean1_UsingSource1.
echo Running AutoTester for QueryModifies1_UsingSource1 ...
AutoTester Test15_Verb\Regression\Source1.txt Test15_Verb\Regression\QueryModifies1_UsingSource1.txt TestResult\out15_Regression_QueryModifies1_UsingSource1.xml > TestResult\cmd\cmd15_Regression_QueryModifies1_UsingSource1.txt
echo Finish running AutoTester for QueryModifies1_UsingSource1.
echo Running AutoTester for QueryUses1_UsingSource1 ...
AutoTester Test15_Verb\Regression\Source1.txt Test15_Verb\Regression\QueryUses1_UsingSource1.txt TestResult\out15_Regression_QueryUses1_UsingSource1.xml > TestResult\cmd\cmd15_Regression_QueryUses1_UsingSource1.txt
echo Finish running AutoTester for QueryUses1_UsingSource1.
echo Running AutoTester for QueryWith1_UsingSource1 ...
AutoTester Test15_Verb\Regression\Source1.txt Test15_Verb\Regression\QueryWith1_UsingSource1.txt TestResult\out15_Regression_QueryWith1_UsingSource1.xml > TestResult\cmd\cmd15_Regression_QueryWith1_UsingSource1.txt
echo Finish running AutoTester for QueryWith1_UsingSource1.
echo Running AutoTester for System\Affects\QueryAffectsTest1 ...
AutoTester Test15_Verb\System\Affects\SourceAffectsTest1.txt Test15_Verb\System\Affects\QueryAffectsTest1.txt TestResult\out15_SystemAffects_QueryAffectsTest1.xml > TestResult\cmd\cmd15_SystemAffects_QueryAffectsTest1.txt
echo Finish running AutoTester for System\Affects\QueryAffectsTest1.
echo Running AutoTester for System\Affects\QueryAffectsTest2 ...
AutoTester Test15_Verb\System\Affects\SourceAffectsTest2.txt Test15_Verb\System\Affects\QueryAffectsTest2.txt TestResult\out15_SystemAffects_QueryAffectsTest2.xml > TestResult\cmd\cmd15_SystemAffects_QueryAffectsTest2.txt
echo Finish running AutoTester for System\Affects\QueryAffectsTest2.
echo Running AutoTester for System\Affects\QueryAffectsTest3 ...
AutoTester Test15_Verb\System\Affects\SourceAffectsTest3.txt Test15_Verb\System\Affects\QueryAffectsTest3.txt TestResult\out15_SystemAffects_QueryAffectsTest3.xml > TestResult\cmd\cmd15_SystemAffects_QueryAffectsTest3.txt
echo Finish running AutoTester for System\Affects\QueryAffectsTest3.
echo Running AutoTester for System\Calls\QueryCallsTest1 ...
AutoTester Test15_Verb\System\Calls\SourceCallsTest1.txt Test15_Verb\System\Calls\QueryCallsTest1.txt TestResult\out15_SystemCalls_QueryCallsTest1.xml > TestResult\cmd\cmd15_SystemCalls_QueryCallsTest1.txt
echo Finish running AutoTester for System\Calls\QueryCallsTest1.
echo Running AutoTester for System\Calls\QueryCallsTest2 ...
AutoTester Test15_Verb\System\Calls\SourceCallsTest2.txt Test15_Verb\System\Calls\QueryCallsTest2.txt TestResult\out15_SystemCalls_QueryCallsTest2.xml > TestResult\cmd\cmd15_SystemCalls_QueryCallsTest2.txt
echo Finish running AutoTester for System\Calls\QueryCallsTest2.
echo Running AutoTester for System\Calls\QueryCallsTest3 ...
AutoTester Test15_Verb\System\Calls\SourceCallsTest3.txt Test15_Verb\System\Calls\QueryCallsTest3.txt TestResult\out15_SystemCalls_QueryCallsTest3.xml > TestResult\cmd\cmd15_SystemCalls_QueryCallsTest3.txt
echo Finish running AutoTester for System\Calls\QueryCallsTest3.
echo Running AutoTester for System\CommonSynonym\QueryCommonSynonymTest1 ...
AutoTester Test15_Verb\System\CommonSynonym\SourceCommonSynonymTest1.txt Test15_Verb\System\CommonSynonym\QueryCommonSynonymTest1.txt TestResult\out15_SystemCommonSynonym_QueryCommonSynonymTest1.xml > TestResult\cmd\cmd15_SystemCommonSynonym_QueryCommonSynonymTest1.txt
echo Finish running AutoTester for System\CommonSynonym\QueryCommonSynonymTest1.
echo Running AutoTester for System\CommonSynonym\QueryCommonSynonymTest2 ...
AutoTester Test15_Verb\System\CommonSynonym\SourceCommonSynonymTest2.txt Test15_Verb\System\CommonSynonym\QueryCommonSynonymTest2.txt TestResult\out15_SystemCommonSynonym_QueryCommonSynonymTest2.xml > TestResult\cmd\cmd15_SystemCommonSynonym_QueryCommonSynonymTest2.txt
echo Finish running AutoTester for System\CommonSynonym\QueryCommonSynonymTest2.
echo Running AutoTester for System\Follows\QueryFollowsTest1 ...
AutoTester Test15_Verb\System\Follows\SourceFollowsTest1.txt Test15_Verb\System\Follows\QueryFollowsTest1.txt TestResult\out15_SystemFollows_QueryFollowsTest1.xml > TestResult\cmd\cmd15_SystemFollows_QueryFollowsTest1.txt
echo Finish running AutoTester for System\Follows\QueryFollowsTest1.
echo Running AutoTester for System\Follows\QueryFollowsTest2 ...
AutoTester Test15_Verb\System\Follows\SourceFollowsTest2.txt Test15_Verb\System\Follows\QueryFollowsTest2.txt TestResult\out15_SystemFollows_QueryFollowsTest2.xml > TestResult\cmd\cmd15_SystemFollows_QueryFollowsTest2.txt
echo Finish running AutoTester for System\Follows\QueryFollowsTest2.
echo Running AutoTester for System\Follows\QueryFollowsTest3 ...
AutoTester Test15_Verb\System\Follows\SourceFollowsTest3.txt Test15_Verb\System\Follows\QueryFollowsTest3.txt TestResult\out15_SystemFollows_QueryFollowsTest3.xml > TestResult\cmd\cmd15_SystemFollows_QueryFollowsTest3.txt
echo Finish running AutoTester for System\Follows\QueryFollowsTest3.
echo Running AutoTester for System\ModifiesUses\QueryModifiesUsesTest1 ...
AutoTester Test15_Verb\System\ModifiesUses\SourceModifiesUsesTest1.txt Test15_Verb\System\ModifiesUses\QueryModifiesUsesTest1.txt TestResult\out15_SystemModifiesUses_QueryModifiesUsesTest1.xml > TestResult\cmd\cmd15_SystemModifiesUses_QueryModifiesUsesTest1.txt
echo Finish running AutoTester for System\ModifiesUses\QueryModifiesUsesTest1.
echo Running AutoTester for System\ModifiesUses\QueryModifiesUsesTest2 ...
AutoTester Test15_Verb\System\ModifiesUses\SourceModifiesUsesTest2.txt Test15_Verb\System\ModifiesUses\QueryModifiesUsesTest2.txt TestResult\out15_SystemModifiesUses_QueryModifiesUsesTest2.xml > TestResult\cmd\cmd15_SystemModifiesUses_QueryModifiesUsesTest2.txt
echo Finish running AutoTester for System\ModifiesUses\QueryModifiesUsesTest2.
echo Running AutoTester for System\ModifiesUses\QueryModifiesUsesTest3 ...
AutoTester Test15_Verb\System\ModifiesUses\SourceModifiesUsesTest3.txt Test15_Verb\System\ModifiesUses\QueryModifiesUsesTest3.txt TestResult\out15_SystemModifiesUses_QueryModifiesUsesTest3.xml > TestResult\cmd\cmd15_SystemModifiesUses_QueryModifiesUsesTest3.txt
echo Finish running AutoTester for System\ModifiesUses\QueryModifiesUsesTest3.
echo Running AutoTester for System\MultipleClauses\QueryMultipleClausesTest1 ...
AutoTester Test15_Verb\System\MultipleClauses\SourceMultipleClausesTest1.txt Test15_Verb\System\MultipleClauses\QueryMultipleClausesTest1.txt TestResult\out15_SystemMultipleClauses_QueryMultipleClausesTest1.xml > TestResult\cmd\cmd15_SystemMultipleClauses_QueryMultipleClausesTest1.txt
echo Finish running AutoTester for System\MultipleClauses\QueryMultipleClausesTest1.
echo Running AutoTester for System\MultipleClauses\QueryMultipleClausesTest2 ...
AutoTester Test15_Verb\System\MultipleClauses\SourceMultipleClausesTest2.txt Test15_Verb\System\MultipleClauses\QueryMultipleClausesTest2.txt TestResult\out15_SystemMultipleClauses_QueryMultipleClausesTest2.xml > TestResult\cmd\cmd15_SystemMultipleClauses_QueryMultipleClausesTest2.txt
echo Finish running AutoTester for System\MultipleClauses\QueryMultipleClausesTest2.
echo Running AutoTester for System\MultipleClauses\QueryMultipleClausesTest3 ...
AutoTester Test15_Verb\System\MultipleClauses\SourceMultipleClausesTest3.txt Test15_Verb\System\MultipleClauses\QueryMultipleClausesTest3.txt TestResult\out15_SystemMultipleClauses_QueryMultipleClausesTest3.xml > TestResult\cmd\cmd15_SystemMultipleClauses_QueryMultipleClausesTest3.txt
echo Finish running AutoTester for System\MultipleClauses\QueryMultipleClausesTest3.
echo Running AutoTester for System\Next\QueryNextTest1 ...
AutoTester Test15_Verb\System\Next\SourceNextTest1.txt Test15_Verb\System\Next\QueryNextTest1.txt TestResult\out15_SystemNext_QueryNextTest1.xml > TestResult\cmd\cmd15_SystemNext_QueryNextTest1.txt
echo Finish running AutoTester for System\Next\QueryNextTest1.
echo Running AutoTester for System\Next\QueryNextTest2 ...
AutoTester Test15_Verb\System\Next\SourceNextTest2.txt Test15_Verb\System\Next\QueryNextTest2.txt TestResult\out15_SystemNext_QueryNextTest2.xml > TestResult\cmd\cmd15_SystemNext_QueryNextTest2.txt
echo Finish running AutoTester for System\Next\QueryNextTest2.
echo Running AutoTester for System\Next\QueryNextTest3 ...
AutoTester Test15_Verb\System\Next\SourceNextTest3.txt Test15_Verb\System\Next\QueryNextTest3.txt TestResult\out15_SystemNext_QueryNextTest3.xml > TestResult\cmd\cmd15_SystemNext_QueryNextTest3.txt
echo Finish running AutoTester for System\Next\QueryNextTest3.
echo Running AutoTester for System\Parent\QueryParentTest1 ...
AutoTester Test15_Verb\System\Parent\SourceParentTest1.txt Test15_Verb\System\Parent\QueryParentTest1.txt TestResult\out15_SystemParent_QueryParentTest1.xml > TestResult\cmd\cmd15_SystemParent_QueryParentTest1.txt
echo Finish running AutoTester for System\Parent\QueryParentTest1.
echo Running AutoTester for System\Parent\QueryParentTest2 ...
AutoTester Test15_Verb\System\Parent\SourceParentTest2.txt Test15_Verb\System\Parent\QueryParentTest2.txt TestResult\out15_SystemParent_QueryParentTest2.xml > TestResult\cmd\cmd15_SystemParent_QueryParentTest2.txt
echo Finish running AutoTester for System\Parent\QueryParentTest2.
echo Running AutoTester for System\Parent\QueryParentTest3 ...
AutoTester Test15_Verb\System\Parent\SourceParentTest3.txt Test15_Verb\System\Parent\QueryParentTest3.txt TestResult\out15_SystemParent_QueryParentTest3.xml > TestResult\cmd\cmd15_SystemParent_QueryParentTest3.txt
echo Finish running AutoTester for System\Parent\QueryParentTest3.
echo Running AutoTester for System\Pattern\QueryPatternTest1 ...
AutoTester Test15_Verb\System\Pattern\SourcePatternTest1.txt Test15_Verb\System\Pattern\QueryPatternTest1.txt TestResult\out15_SystemPattern_QueryPatternTest1.xml > TestResult\cmd\cmd15_SystemPattern_QueryPatternTest1.txt
echo Finish running AutoTester for System\Pattern\QueryPatternTest1.
echo Running AutoTester for System\Pattern\QueryPatternTest2 ...
AutoTester Test15_Verb\System\Pattern\SourcePatternTest2.txt Test15_Verb\System\Pattern\QueryPatternTest2.txt TestResult\out15_SystemPattern_QueryPatternTest2.xml > TestResult\cmd\cmd15_SystemPattern_QueryPatternTest2.txt
echo Finish running AutoTester for System\Pattern\QueryPatternTest2.
echo Running AutoTester for System\Pattern\QueryPatternTest3 ...
AutoTester Test15_Verb\System\Pattern\SourcePatternTest3.txt Test15_Verb\System\Pattern\QueryPatternTest3.txt TestResult\out15_SystemPattern_QueryPatternTest3.xml > TestResult\cmd\cmd15_SystemPattern_QueryPatternTest3.txt
echo Finish running AutoTester for System\Pattern\QueryPatternTest3.
echo Running AutoTester for System\Select\QuerySelectTest1 ...
AutoTester Test15_Verb\System\Select\SourceSelectTest1.txt Test15_Verb\System\Select\QuerySelectTest1.txt TestResult\out15_SystemSelect_QuerySelectTest1.xml > TestResult\cmd\cmd15_SystemSelect_QuerySelectTest1.txt
echo Finish running AutoTester for System\Select\QuerySelectTest1.
echo Running AutoTester for System\Select\QuerySelectTest1_InvalidAttributes ...
AutoTester Test15_Verb\System\Select\SourceSelectTest1.txt Test15_Verb\System\Select\QuerySelectTest1_InvalidAttributes.txt TestResult\out15_SystemSelect_QuerySelectTest1_InvalidAttributes.xml > TestResult\cmd\cmd15_SystemSelect_QuerySelectTest1_InvalidAttributes.txt
echo Finish running AutoTester for System\Select\QuerySelectTest1_InvalidAttributes.
echo Running AutoTester for System\Select\QuerySelectTest2 ...
AutoTester Test15_Verb\System\Select\SourceSelectTest2.txt Test15_Verb\System\Select\QuerySelectTest2.txt TestResult\out15_SystemSelect_QuerySelectTest2.xml > TestResult\cmd\cmd15_SystemSelect_QuerySelectTest2.txt
echo Finish running AutoTester for System\Select\QuerySelectTest2.
echo Running AutoTester for System\Select\QuerySelectTest3 ...
AutoTester Test15_Verb\System\Select\SourceSelectTest3.txt Test15_Verb\System\Select\QuerySelectTest3.txt TestResult\out15_SystemSelect_QuerySelectTest3.xml > TestResult\cmd\cmd15_SystemSelect_QuerySelectTest3.txt
echo Finish running AutoTester for System\Select\QuerySelectTest3.
echo Running AutoTester for System\Tuple\QueryTupleTest1 ...
AutoTester Test15_Verb\System\Tuple\SourceTupleTest1.txt Test15_Verb\System\Tuple\QueryTupleTest1.txt TestResult\out15_SystemTuple_QueryTupleTest1.xml > TestResult\cmd\cmd15_SystemTuple_QueryTupleTest1.txt
echo Finish running AutoTester for System\Tuple\QueryTupleTest1.
echo Running AutoTester for System\With\QueryWithTest1 ...
AutoTester Test15_Verb\System\With\SourceWithTest1.txt Test15_Verb\System\With\QueryWithTest1.txt TestResult\out15_SystemWith_QueryWithTest1.xml > TestResult\cmd\cmd15_SystemWith_QueryWithTest1.txt
echo Finish running AutoTester for System\With\QueryWithTest1.
echo Running AutoTester for System\With\QueryWithTest2 ...
AutoTester Test15_Verb\System\With\SourceWithTest2.txt Test15_Verb\System\With\QueryWithTest2.txt TestResult\out15_SystemWith_QueryWithTest2.xml > TestResult\cmd\cmd15_SystemWith_QueryWithTest2.txt
echo Finish running AutoTester for System\With\QueryWithTest2.
echo Running AutoTester for System\With\QueryWithTest3 ...
AutoTester Test15_Verb\System\With\SourceWithTest3.txt Test15_Verb\System\With\QueryWithTest3.txt TestResult\out15_SystemWith_QueryWithTest3.xml > TestResult\cmd\cmd15_SystemWith_QueryWithTest3.txt
echo Finish running AutoTester for System\With\QueryWithTest3.
echo Running AutoTester for Validation\QueryValidation ...
AutoTester Test15_Verb\Validation\SourceValidation.txt Test15_Verb\Validation\QueryValidation.txt TestResult\out15_Validation_QueryValidation.xml > TestResult\cmd\cmd15_Validation_QueryValidation.txt
echo Finish running AutoTester for Validation\QueryValidation.
echo Running AutoTester for Stress\CommonSynonym\QueryStressCommonSynonymTest1 ...
AutoTester Test15_Verb\Stress\CommonSynonym\SourceStressCommonSynonymTest1.txt Test15_Verb\Stress\CommonSynonym\QueryStressCommonSynonymTest1.txt TestResult\out15_StressCommonSynonym_QueryStressCommonSynonymTest1.xml > TestResult\cmd\cmd15_StressCommonSynonym_QueryStressCommonSynonymTest1.txt
echo Finish running AutoTester for Stress\CommonSynonym\QueryStressCommonSynonymTest1.
echo Running AutoTester for Stress\MultipleClauses\QueryStressMultipleClausesTest1 ...
AutoTester Test15_Verb\Stress\MultipleClauses\SourceStressMultipleClausesTest1.txt Test15_Verb\Stress\MultipleClauses\QueryStressMultipleClausesTest1.txt TestResult\out15_StressMultipleClauses_QueryStressMultipleClausesTest1.xml > TestResult\cmd\cmd15_StressMultipleClauses_QueryStressMultipleClausesTest1.txt
echo Finish running AutoTester for Stress\MultipleClauses\QueryStressMultipleClausesTest1.
echo echo -- RECURSIVECALL! -- QueryStressNextTest1.txt has been commented away in the bat file -- ! --
REM echo Running AutoTester for Stress\Next\QueryStressNextTest1 ...
REM AutoTester Test15_Verb\Stress\Next\SourceStressNextTest1.txt Test15_Verb\Stress\Next\QueryStressNextTest1.txt TestResult\out15_StressNext_QueryStressNextTest1.xml > TestResult\cmd\cmd15_StressNext_QueryStressNextTest1.txt
REM echo Finish running AutoTester for Stress\Next\QueryStressNextTest1.
echo Finish running AutoTester for test 15.
call :getPauseAction
goto :eof

:runTest16
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 16...
echo Running AutoTester for QueryStressNext...
AutoTester Test16_Stress\SourceStress.txt Test16_Stress\QueryStressNext.txt TestResult\out16_QueryStressNext.xml > TestResult\cmd\cmd16_QueryStressNext.txt
echo Finish running AutoTester for QueryStressNext.
echo Running AutoTester for QueryStressAffects...
AutoTester Test16_Stress\SourceStress.txt Test16_Stress\QueryStressAffects.txt TestResult\out16_QueryStressAffects.xml > TestResult\cmd\cmd16_QueryStressAffects.txt
echo Finish running AutoTester for QueryStressAffects.
echo Running AutoTester for QueryStressMixed...
AutoTester Test16_Stress\SourceStress.txt Test16_Stress\QueryStressMixed.txt TestResult\out16_QueryStressMixed.xml > TestResult\cmd\cmd16_QueryStressMixed.txt
echo Finish running AutoTester for QueryStressMixed.
echo Finish running AutoTester for test 16.
call :getPauseAction
goto :eof

:runTest17
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 17...
AutoTester Test17_Japan\Source_Simple03.txt Test17_Japan\Query_Simple03.txt TestResult\out17_Query_Simple03.xml > TestResult\cmd\cmd17_Query_Simple03.txt
echo Finish running AutoTester for test 17.
call :getPauseAction
goto :eof

:runTest18
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 18...
AutoTester Test18_Validation\SourceValidation.txt Test18_Validation\QueryValidation.txt TestResult\out18_QueryValidation.xml > TestResult\cmd\cmd18_QueryValidation.txt
echo Finish running AutoTester for test 18.
call :getPauseAction
goto :eof

:runTest19
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 19...
echo Running AutoTester for Query_std1_adv ...
AutoTester Test19_Mat\Source_std1.txt Test19_Mat\Query_std1_adv.txt TestResult\out19_Query_std1_adv.xml > TestResult\cmd\cmd19_Query_std1_adv.txt
echo Finish running AutoTester for Query_std1_adv.
echo Running AutoTester for Query_std1_basic ...
AutoTester Test19_Mat\Source_std1.txt Test19_Mat\Query_std1_basic.txt TestResult\out19_Query_std1_basic.xml > TestResult\cmd\cmd19_Query_std1_basic.txt
echo Finish running AutoTester for Query_std1_basic.
echo Running AutoTester for Query_std2_adv ...
AutoTester Test19_Mat\Source_std2.txt Test19_Mat\Query_std2_adv.txt TestResult\out19_Query_std2_adv.xml > TestResult\cmd\cmd19_Query_std2_adv.txt
echo Finish running AutoTester for Query_std2_adv.
echo Running AutoTester for Query_std2_basic ...
AutoTester Test19_Mat\Source_std2.txt Test19_Mat\Query_std2_basic.txt TestResult\out19_Query_std2_basic.xml > TestResult\cmd\cmd19_Query_std2_basic.txt
echo Finish running AutoTester for Query_std2_basic.
echo Running AutoTester for Query_std3_adv ...
AutoTester Test19_Mat\Source_std3.txt Test19_Mat\Query_std3_adv.txt TestResult\out19_Query_std3_adv.xml > TestResult\cmd\cmd19_Query_std3_adv.txt
echo Finish running AutoTester for Query_std3_adv.
echo Running AutoTester for Query_std3_basic ...
AutoTester Test19_Mat\Source_std3.txt Test19_Mat\Query_std3_basic.txt TestResult\out19_Query_std3_basic.xml > TestResult\cmd\cmd19_Query_std3_basic.txt
echo Finish running AutoTester for Query_std3_basic.
echo Finish running AutoTester for test 19.
call :getPauseAction
goto :eof

:runTest20
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 20...
echo Running AutoTester for queries1 ...
AutoTester Test20_ZYOne\Grp\source1.txt Test20_ZYOne\Grp\queries1.txt TestResult\out20_Grp_queries1.xml > TestResult\cmd\cmd20_Grp_queries1.txt
echo Finish running AutoTester for queries1.
echo Running AutoTester for queries2 ...
AutoTester Test20_ZYOne\Grp\source2.txt Test20_ZYOne\Grp\queries2.txt TestResult\out20_Grp_queries2.xml > TestResult\cmd\cmd20_Grp_queries2.txt
echo Finish running AutoTester for queries2.
echo Running AutoTester for queries3 ...
AutoTester Test20_ZYOne\Grp\source3.txt Test20_ZYOne\Grp\queries3.txt TestResult\out20_Grp_queries3.xml > TestResult\cmd\cmd20_Grp_queries3.txt
echo Finish running AutoTester for queries3.
echo Running AutoTester for queries4 ...
AutoTester Test20_ZYOne\Grp\source4.txt Test20_ZYOne\Grp\queries4.txt TestResult\out20_Grp_queries4.xml > TestResult\cmd\cmd20_Grp_queries4.txt
echo Finish running AutoTester for queries4.
echo Running AutoTester for queries5 ...
AutoTester Test20_ZYOne\Grp\source5.txt Test20_ZYOne\Grp\queries5.txt TestResult\out20_Grp_queries5.xml > TestResult\cmd\cmd20_Grp_queries5.txt
echo Finish running AutoTester for queries5.
echo Running AutoTester for queries6 ...
AutoTester Test20_ZYOne\Grp\source6.txt Test20_ZYOne\Grp\queries6.txt TestResult\out20_Grp_queries6.xml > TestResult\cmd\cmd20_Grp_queries6.txt
echo Finish running AutoTester for queries6.
echo Running AutoTester for queries1 ...
AutoTester Test20_ZYOne\Others\source1.txt Test20_ZYOne\Others\queries1.txt TestResult\out20_Others_queries1.xml > TestResult\cmd\cmd20_Others_queries1.txt
echo Finish running AutoTester for queries1.
echo Running AutoTester for queries2 ...
AutoTester Test20_ZYOne\Others\source2.txt Test20_ZYOne\Others\queries2.txt TestResult\out20_Others_queries2.xml > TestResult\cmd\cmd20_Others_queries2.txt
echo Finish running AutoTester for queries2.
echo Running AutoTester for queries3 ...
AutoTester Test20_ZYOne\Others\source3.txt Test20_ZYOne\Others\queries3.txt TestResult\out20_Others_queries3.xml > TestResult\cmd\cmd20_Others_queries3.txt
echo Finish running AutoTester for queries3.
echo Running AutoTester for queries4 ...
AutoTester Test20_ZYOne\Others\source4.txt Test20_ZYOne\Others\queries4.txt TestResult\out20_Others_queries4.xml > TestResult\cmd\cmd20_Others_queries4.txt
echo Finish running AutoTester for queries4.
echo Running AutoTester for queries5 ...
AutoTester Test20_ZYOne\Others\source5.txt Test20_ZYOne\Others\queries5.txt TestResult\out20_Others_queries5.xml > TestResult\cmd\cmd20_Others_queries5.txt
echo Finish running AutoTester for queries5.
echo Running AutoTester for queries6 ...
AutoTester Test20_ZYOne\Others\source6.txt Test20_ZYOne\Others\queries6.txt TestResult\out20_Others_queries6.xml > TestResult\cmd\cmd20_Others_queries6.txt
echo Finish running AutoTester for queries6.
echo Running AutoTester for queries6b ...
AutoTester Test20_ZYOne\Others\source6b.txt Test20_ZYOne\Others\queries6b.txt TestResult\out20_Others_queries6b.xml > TestResult\cmd\cmd20_Others_queries6b.txt
echo Finish running AutoTester for queries6b.
echo Running AutoTester for queries7 ...
AutoTester Test20_ZYOne\Others\source7.txt Test20_ZYOne\Others\queries7.txt TestResult\out20_Others_queries7.xml > TestResult\cmd\cmd20_Others_queries7.txt
echo Finish running AutoTester for queries7.
echo Running AutoTester for queries7b ...
AutoTester Test20_ZYOne\Others\source7.txt Test20_ZYOne\Others\queries7b.txt TestResult\out20_Others_queries7b.xml > TestResult\cmd\cmd20_Others_queries7b.txt
echo Finish running AutoTester for queries7b.
echo Running AutoTester for queries8 ...
AutoTester Test20_ZYOne\Others\source8.txt Test20_ZYOne\Others\queries8.txt TestResult\out20_Others_queries8.xml > TestResult\cmd\cmd20_Others_queries8.txt
echo Finish running AutoTester for queries8.
echo Running AutoTester for queries8b ...
AutoTester Test20_ZYOne\Others\source8.txt Test20_ZYOne\Others\queries8b.txt TestResult\out20_Others_queries8b.xml > TestResult\cmd\cmd20_Others_queries8b.txt
echo Finish running AutoTester for queries8b.
echo Running AutoTester for queries9 ...
AutoTester Test20_ZYOne\Others\source9.txt Test20_ZYOne\Others\queries9.txt TestResult\out20_Others_queries9.xml > TestResult\cmd\cmd20_Others_queries9.txt
echo Finish running AutoTester for queries9.
echo Running AutoTester for queries10 ...
AutoTester Test20_ZYOne\Others\source10.txt Test20_ZYOne\Others\queries10.txt TestResult\out20_Others_queries10.xml > TestResult\cmd\cmd20_Others_queries10.txt
echo Finish running AutoTester for queries10.
echo Running AutoTester for queriesCalls ...
AutoTester Test20_ZYOne\Relation\sourceCalls.txt Test20_ZYOne\Relation\queriesCalls.txt TestResult\out20_Relation_queriesCalls.xml > TestResult\cmd\cmd20_Relation_queriesCalls.txt
echo Finish running AutoTester for queriesCalls.
echo Running AutoTester for queriesNext ...
AutoTester Test20_ZYOne\Relation\sourceNext.txt Test20_ZYOne\Relation\queriesNext.txt TestResult\out20_Relation_queriesNext.xml > TestResult\cmd\cmd20_Relation_queriesNext.txt
echo Finish running AutoTester for queriesNext.
echo Running AutoTester for queries1 ...
AutoTester Test20_ZYOne\Valid\source1.txt Test20_ZYOne\Valid\queries1.txt TestResult\out20_Valid_queries1.xml > TestResult\cmd\cmd20_Valid_queries1.txt
echo Finish running AutoTester for queries1.
echo Running AutoTester for queries2 ...
AutoTester Test20_ZYOne\Valid\source2.txt Test20_ZYOne\Valid\queries2.txt TestResult\out20_Valid_queries2.xml > TestResult\cmd\cmd20_Valid_queries2.txt
echo Finish running AutoTester for queries2.
echo Running AutoTester for queries3 ...
AutoTester Test20_ZYOne\Valid\source3.txt Test20_ZYOne\Valid\queries3.txt TestResult\out20_Valid_queries3.xml > TestResult\cmd\cmd20_Valid_queries3.txt
echo Finish running AutoTester for queries3.
echo Running AutoTester for queries4 ...
AutoTester Test20_ZYOne\Valid\source4.txt Test20_ZYOne\Valid\queries4.txt TestResult\out20_Valid_queries4.xml > TestResult\cmd\cmd20_Valid_queries4.txt
echo Finish running AutoTester for queries4.
echo Running AutoTester for queries5 ...
AutoTester Test20_ZYOne\Valid\source5.txt Test20_ZYOne\Valid\queries5.txt TestResult\out20_Valid_queries5.xml > TestResult\cmd\cmd20_Valid_queries5.txt
echo Finish running AutoTester for queries5.
echo Running AutoTester for queries6 ...
AutoTester Test20_ZYOne\Valid\source6.txt Test20_ZYOne\Valid\queries6.txt TestResult\out20_Valid_queries6.xml > TestResult\cmd\cmd20_Valid_queries6.txt
echo Finish running AutoTester for queries6.
echo Running AutoTester for queries6_Affects ...
AutoTester Test20_ZYOne\Valid\source6.txt Test20_ZYOne\Valid\queries6_Affects.txt TestResult\out20_Valid_queries6_Affects.xml > TestResult\cmd\cmd20_Valid_queries6_Affects.txt
echo Finish running AutoTester for queries6_Affects.
echo Running AutoTester for queries6_Calls ...
AutoTester Test20_ZYOne\Valid\source6.txt Test20_ZYOne\Valid\queries6_Calls.txt TestResult\out20_Valid_queries6_Calls.xml > TestResult\cmd\cmd20_Valid_queries6_Calls.txt
echo Finish running AutoTester for queries6_Calls.
echo Running AutoTester for queries6_Follows ...
AutoTester Test20_ZYOne\Valid\source6.txt Test20_ZYOne\Valid\queries6_Follows.txt TestResult\out20_Valid_queries6_Follows.xml > TestResult\cmd\cmd20_Valid_queries6_Follows.txt
echo Finish running AutoTester for queries6_Follows.
echo Running AutoTester for queries6_Modifies ...
AutoTester Test20_ZYOne\Valid\source6.txt Test20_ZYOne\Valid\queries6_Modifies.txt TestResult\out20_Valid_queries6_Modifies.xml > TestResult\cmd\cmd20_Valid_queries6_Modifies.txt
echo Finish running AutoTester for queries6_Modifies.
echo Running AutoTester for queries6_MultipleClause ...
AutoTester Test20_ZYOne\Valid\source6.txt Test20_ZYOne\Valid\queries6_MultipleClause.txt TestResult\out20_Valid_queries6_MultipleClause.xml > TestResult\cmd\cmd20_Valid_queries6_MultipleClause.txt
echo Finish running AutoTester for queries6_MultipleClause.
echo Running AutoTester for queries6_Parents ...
AutoTester Test20_ZYOne\Valid\source6.txt Test20_ZYOne\Valid\queries6_Parents.txt TestResult\out20_Valid_queries6_Parents.xml > TestResult\cmd\cmd20_Valid_queries6_Parents.txt
echo Finish running AutoTester for queries6_Parents.
echo Running AutoTester for queries6_Uses ...
AutoTester Test20_ZYOne\Valid\source6.txt Test20_ZYOne\Valid\queries6_Uses.txt TestResult\out20_Valid_queries6_Uses.xml > TestResult\cmd\cmd20_Valid_queries6_Uses.txt
echo Finish running AutoTester for queries6_Uses.
echo Finish running AutoTester for test 20.
call :getPauseAction
goto :eof

:runTest21
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 21...
echo Running AutoTester for Queries1 ...
AutoTester Test21_ZYTwo\Source1.txt Test21_ZYTwo\Queries1.txt TestResult\out21_Queries1.xml > TestResult\cmd\cmd21_Queries1.txt
echo Finish running AutoTester for Queries1.
echo Running AutoTester for Queries1Bonus ...
AutoTester Test21_ZYTwo\Source1Bonus.txt Test21_ZYTwo\Queries1Bonus.txt TestResult\out21_Queries1Bonus.xml > TestResult\cmd\cmd21_Queries1Bonus.txt
echo Finish running AutoTester for Queries1Bonus.
echo Running AutoTester for Queries11 ...
AutoTester Test21_ZYTwo\Source11.txt Test21_ZYTwo\Queries11.txt TestResult\out21_Queries11.xml > TestResult\cmd\cmd21_Queries11.txt
echo Finish running AutoTester for Queries11.
echo Running AutoTester for Queries12 ...
AutoTester Test21_ZYTwo\Source12.txt Test21_ZYTwo\Queries12.txt TestResult\out21_Queries12.xml > TestResult\cmd\cmd21_Queries12.txt
echo Finish running AutoTester for Queries12.
echo Running AutoTester for Queries12a ...
AutoTester Test21_ZYTwo\Source12.txt Test21_ZYTwo\Queries12a.txt TestResult\out21_Queries12a.xml > TestResult\cmd\cmd21_Queries12a.txt
echo Finish running AutoTester for Queries12a.
echo Running AutoTester for Queries13 ...
AutoTester Test21_ZYTwo\Source13.txt Test21_ZYTwo\Queries13.txt TestResult\out21_Queries13.xml > TestResult\cmd\cmd21_Queries13.txt
echo Finish running AutoTester for Queries13.
echo Running AutoTester for Queries21 ...
AutoTester Test21_ZYTwo\Source21.txt Test21_ZYTwo\Queries21.txt TestResult\out21_Queries21.xml > TestResult\cmd\cmd21_Queries21.txt
echo Finish running AutoTester for Queries21.
echo Running AutoTester for Queries21a ...
AutoTester Test21_ZYTwo\Source21.txt Test21_ZYTwo\Queries21a.txt TestResult\out21_Queries21a.xml > TestResult\cmd\cmd21_Queries21a.txt
echo Finish running AutoTester for Queries21a.
echo Running AutoTester for QueriesAffects ...
AutoTester Test21_ZYTwo\SourceAffects.txt Test21_ZYTwo\QueriesAffects.txt TestResult\out21_QueriesAffects.xml > TestResult\cmd\cmd21_QueriesAffects.txt
echo Finish running AutoTester for QueriesAffects.
echo Running AutoTester for QueriesAffectsNextStarStressTest ...
AutoTester Test21_ZYTwo\SourceAffects.txt Test21_ZYTwo\QueriesAffectsNextStarStressTest.txt TestResult\out21_QueriesAffectsNextStarStressTest.xml > TestResult\cmd\cmd21_QueriesAffectsNextStarStressTest.txt
echo Finish running AutoTester for QueriesAffectsNextStarStressTest.
echo Running AutoTester for QueriesAffectsStar ...
AutoTester Test21_ZYTwo\SourceAffects.txt Test21_ZYTwo\QueriesAffectsStar.txt TestResult\out21_QueriesAffectsStar.xml > TestResult\cmd\cmd21_QueriesAffectsStar.txt
echo Finish running AutoTester for QueriesAffectsStar.
echo Running AutoTester for QueriesAffectsStressTest ...
AutoTester Test21_ZYTwo\SourceAffects.txt Test21_ZYTwo\QueriesAffectsStressTest.txt TestResult\out21_QueriesAffectsStressTest.xml > TestResult\cmd\cmd21_QueriesAffectsStressTest.txt
echo Finish running AutoTester for QueriesAffectsStressTest.
echo Running AutoTester for QueriesCalls ...
AutoTester Test21_ZYTwo\SourceCalls.txt Test21_ZYTwo\QueriesCalls.txt TestResult\out21_QueriesCalls.xml > TestResult\cmd\cmd21_QueriesCalls.txt
echo Finish running AutoTester for QueriesCalls.
echo Running AutoTester for QueriesIf ...
AutoTester Test21_ZYTwo\SourceIf.txt Test21_ZYTwo\QueriesIf.txt TestResult\out21_QueriesIf.xml > TestResult\cmd\cmd21_QueriesIf.txt
echo Finish running AutoTester for QueriesIf.
echo Running AutoTester for QueriesMiniIter1 ...
AutoTester Test21_ZYTwo\SourceMiniIter1.txt Test21_ZYTwo\QueriesMiniIter1.txt TestResult\out21_QueriesMiniIter1.xml > TestResult\cmd\cmd21_QueriesMiniIter1.txt
echo Finish running AutoTester for QueriesMiniIter1.
echo Running AutoTester for QueriesMiniIter1NoWhile ...
AutoTester Test21_ZYTwo\SourceMiniIter1NoWhile.txt Test21_ZYTwo\QueriesMiniIter1NoWhile.txt TestResult\out21_QueriesMiniIter1NoWhile.xml > TestResult\cmd\cmd21_QueriesMiniIter1NoWhile.txt
echo Finish running AutoTester for QueriesMiniIter1NoWhile.
echo Running AutoTester for QueriesNextStar ...
AutoTester Test21_ZYTwo\SourceNextStar.txt Test21_ZYTwo\QueriesNextStar.txt TestResult\out21_QueriesNextStar.xml > TestResult\cmd\cmd21_QueriesNextStar.txt
echo Finish running AutoTester for QueriesNextStar.
echo Finish running AutoTester for test 21.
call :getPauseAction
goto :eof

:runTest22
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 22...
echo Running AutoTester for queries1 ...
AutoTester Test22_ZYThree\source1.txt Test22_ZYThree\queries1.txt TestResult\out22_queries1.xml > TestResult\cmd\cmd22_queries1.txt
echo Finish running AutoTester for queries1.
echo Running AutoTester for queries2 ...
AutoTester Test22_ZYThree\source2.txt Test22_ZYThree\queries2.txt TestResult\out22_queries2.xml > TestResult\cmd\cmd22_queries2.txt
echo Finish running AutoTester for queries2.
echo Running AutoTester for queries3 ...
AutoTester Test22_ZYThree\source3.txt Test22_ZYThree\queries3.txt TestResult\out22_queries3.xml > TestResult\cmd\cmd22_queries3.txt
echo Finish running AutoTester for queries3.
echo Finish running AutoTester for test 22.
call :getPauseAction
goto :eof

:runTest23
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 23...
echo Running AutoTester for QueryComplexAffects ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexAffects.txt TestResult\out23_QueryComplexAffects.xml > TestResult\cmd\cmd23_QueryComplexAffects.txt
echo Finish running AutoTester for QueryComplexAffects.
echo Running AutoTester for QueryComplexAffectsStar ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexAffectsStar.txt TestResult\out23_QueryComplexAffectsStar.xml > TestResult\cmd\cmd23_QueryComplexAffectsStar.txt
echo Finish running AutoTester for QueryComplexAffectsStar.
echo Running AutoTester for QueryComplexAll ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexAll.txt TestResult\out23_QueryComplexAll.xml > TestResult\cmd\cmd23_QueryComplexAll.txt
echo Finish running AutoTester for QueryComplexAll.
echo Running AutoTester for QueryComplexCalls ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexCalls.txt TestResult\out23_QueryComplexCalls.xml > TestResult\cmd\cmd23_QueryComplexCalls.txt
echo Finish running AutoTester for QueryComplexCalls.
echo Running AutoTester for QueryComplexCallsStar ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexCallsStar.txt TestResult\out23_QueryComplexCallsStar.xml > TestResult\cmd\cmd23_QueryComplexCallsStar.txt
echo Finish running AutoTester for QueryComplexCallsStar.
echo Running AutoTester for QueryComplexFollows ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexFollows.txt TestResult\out23_QueryComplexFollows.xml > TestResult\cmd\cmd23_QueryComplexFollows.txt
echo Finish running AutoTester for QueryComplexFollows.
echo Running AutoTester for QueryComplexFollowsStar ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexFollowsStar.txt TestResult\out23_QueryComplexFollowsStar.xml > TestResult\cmd\cmd23_QueryComplexFollowsStar.txt
echo Finish running AutoTester for QueryComplexFollowsStar.
echo Running AutoTester for QueryComplexModifies ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexModifies.txt TestResult\out23_QueryComplexModifies.xml > TestResult\cmd\cmd23_QueryComplexModifies.txt
echo Finish running AutoTester for QueryComplexModifies.
echo Running AutoTester for QueryComplexMultipleClauses ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexMultipleClauses.txt TestResult\out23_QueryComplexMultipleClauses.xml > TestResult\cmd\cmd23_QueryComplexMultipleClauses.txt
echo Finish running AutoTester for QueryComplexMultipleClauses.
echo Running AutoTester for QueryComplexNext ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexNext.txt TestResult\out23_QueryComplexNext.xml > TestResult\cmd\cmd23_QueryComplexNext.txt
echo Finish running AutoTester for QueryComplexNext.
echo Running AutoTester for QueryComplexNextStar ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexNextStar.txt TestResult\out23_QueryComplexNextStar.xml > TestResult\cmd\cmd23_QueryComplexNextStar.txt
echo Finish running AutoTester for QueryComplexNextStar.
echo Running AutoTester for QueryComplexNoClause ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexNoClause.txt TestResult\out23_QueryComplexNoClause.xml > TestResult\cmd\cmd23_QueryComplexNoClause.txt
echo Finish running AutoTester for QueryComplexNoClause.
echo Running AutoTester for QueryComplexParent ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexParent.txt TestResult\out23_QueryComplexParent.xml > TestResult\cmd\cmd23_QueryComplexParent.txt
echo Finish running AutoTester for QueryComplexParent.
echo Running AutoTester for QueryComplexParentStar ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexParentStar.txt TestResult\out23_QueryComplexParentStar.xml > TestResult\cmd\cmd23_QueryComplexParentStar.txt
echo Finish running AutoTester for QueryComplexParentStar.
echo Running AutoTester for QueryComplexPattern ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexPattern.txt TestResult\out23_QueryComplexPattern.xml > TestResult\cmd\cmd23_QueryComplexPattern.txt
echo Finish running AutoTester for QueryComplexPattern.
echo Running AutoTester for QueryComplexTuple ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexTuple.txt TestResult\out23_QueryComplexTuple.xml > TestResult\cmd\cmd23_QueryComplexTuple.txt
echo Finish running AutoTester for QueryComplexTuple.
echo Running AutoTester for QueryComplexUses ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexUses.txt TestResult\out23_QueryComplexUses.xml > TestResult\cmd\cmd23_QueryComplexUses.txt
echo Finish running AutoTester for QueryComplexUses.
echo Running AutoTester for QueryComplexWith ...
AutoTester Test23_ZYFour\SourceComplex.txt Test23_ZYFour\QueryComplexWith.txt TestResult\out23_QueryComplexWith.xml > TestResult\cmd\cmd23_QueryComplexWith.txt
echo Finish running AutoTester for QueryComplexWith.
echo Finish running AutoTester for test 23.
call :getPauseAction
goto :eof

:runTest24
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 24...
echo Running AutoTester for QueryAffects ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryAffects.txt TestResult\out24_First_QueryAffects.xml > TestResult\cmd\cmd24_First_QueryAffects.txt
echo Finish running AutoTester for QueryAffects.
echo Running AutoTester for QueryAffects_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryAffects_Invalid.txt TestResult\out24_First_QueryAffects_Invalid.xml > TestResult\cmd\cmd24_First_QueryAffects_Invalid.txt
echo Finish running AutoTester for QueryAffects_Invalid.
echo Running AutoTester for QueryAffectsStar ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryAffectsStar.txt TestResult\out24_First_QueryAffectsStar.xml > TestResult\cmd\cmd24_First_QueryAffectsStar.txt
echo Finish running AutoTester for QueryAffectsStar.
echo Running AutoTester for QueryAffectsStar_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryAffectsStar_Invalid.txt TestResult\out24_First_QueryAffectsStar_Invalid.xml > TestResult\cmd\cmd24_First_QueryAffectsStar_Invalid.txt
echo Finish running AutoTester for QueryAffectsStar_Invalid.
echo Running AutoTester for QueryCalls ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryCalls.txt TestResult\out24_First_QueryCalls.xml > TestResult\cmd\cmd24_First_QueryCalls.txt
echo Finish running AutoTester for QueryCalls.
echo Running AutoTester for QueryCalls_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryCalls_Invalid.txt TestResult\out24_First_QueryCalls_Invalid.xml > TestResult\cmd\cmd24_First_QueryCalls_Invalid.txt
echo Finish running AutoTester for QueryCalls_Invalid.
echo Running AutoTester for QueryCallsStar ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryCallsStar.txt TestResult\out24_First_QueryCallsStar.xml > TestResult\cmd\cmd24_First_QueryCallsStar.txt
echo Finish running AutoTester for QueryCallsStar.
echo Running AutoTester for QueryCallsStar_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryCallsStar_Invalid.txt TestResult\out24_First_QueryCallsStar_Invalid.xml > TestResult\cmd\cmd24_First_QueryCallsStar_Invalid.txt
echo Finish running AutoTester for QueryCallsStar_Invalid.
echo Running AutoTester for QueryFollows ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryFollows.txt TestResult\out24_First_QueryFollows.xml > TestResult\cmd\cmd24_First_QueryFollows.txt
echo Finish running AutoTester for QueryFollows.
echo Running AutoTester for QueryFollows_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryFollows_Invalid.txt TestResult\out24_First_QueryFollows_Invalid.xml > TestResult\cmd\cmd24_First_QueryFollows_Invalid.txt
echo Finish running AutoTester for QueryFollows_Invalid.
echo Running AutoTester for QueryFollowsStar ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryFollowsStar.txt TestResult\out24_First_QueryFollowsStar.xml > TestResult\cmd\cmd24_First_QueryFollowsStar.txt
echo Finish running AutoTester for QueryFollowsStar.
echo Running AutoTester for QueryFollowsStar_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryFollowsStar_Invalid.txt TestResult\out24_First_QueryFollowsStar_Invalid.xml > TestResult\cmd\cmd24_First_QueryFollowsStar_Invalid.txt
echo Finish running AutoTester for QueryFollowsStar_Invalid.
echo Running AutoTester for QueryModifies ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryModifies.txt TestResult\out24_First_QueryModifies.xml > TestResult\cmd\cmd24_First_QueryModifies.txt
echo Finish running AutoTester for QueryModifies.
echo Running AutoTester for QueryModifies_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryModifies_Invalid.txt TestResult\out24_First_QueryModifies_Invalid.xml > TestResult\cmd\cmd24_First_QueryModifies_Invalid.txt
echo Finish running AutoTester for QueryModifies_Invalid.
echo Running AutoTester for QueryMultipleClauses ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryMultipleClauses.txt TestResult\out24_First_QueryMultipleClauses.xml > TestResult\cmd\cmd24_First_QueryMultipleClauses.txt
echo Finish running AutoTester for QueryMultipleClauses.
echo Running AutoTester for QueryNext ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryNext.txt TestResult\out24_First_QueryNext.xml > TestResult\cmd\cmd24_First_QueryNext.txt
echo Finish running AutoTester for QueryNext.
echo Running AutoTester for QueryNext_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryNext_Invalid.txt TestResult\out24_First_QueryNext_Invalid.xml > TestResult\cmd\cmd24_First_QueryNext_Invalid.txt
echo Finish running AutoTester for QueryNext_Invalid.
echo Running AutoTester for QueryNextStar ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryNextStar.txt TestResult\out24_First_QueryNextStar.xml > TestResult\cmd\cmd24_First_QueryNextStar.txt
echo Finish running AutoTester for QueryNextStar.
echo Running AutoTester for QueryNextStar_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryNextStar_Invalid.txt TestResult\out24_First_QueryNextStar_Invalid.xml > TestResult\cmd\cmd24_First_QueryNextStar_Invalid.txt
echo Finish running AutoTester for QueryNextStar_Invalid.
echo Running AutoTester for QueryParent ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryParent.txt TestResult\out24_First_QueryParent.xml > TestResult\cmd\cmd24_First_QueryParent.txt
echo Finish running AutoTester for QueryParent.
echo Running AutoTester for QueryParent_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryParent_Invalid.txt TestResult\out24_First_QueryParent_Invalid.xml > TestResult\cmd\cmd24_First_QueryParent_Invalid.txt
echo Finish running AutoTester for QueryParent_Invalid.
echo Running AutoTester for QueryParentStar ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryParentStar.txt TestResult\out24_First_QueryParentStar.xml > TestResult\cmd\cmd24_First_QueryParentStar.txt
echo Finish running AutoTester for QueryParentStar.
echo Running AutoTester for QueryParentStar_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryParentStar_Invalid.txt TestResult\out24_First_QueryParentStar_Invalid.xml > TestResult\cmd\cmd24_First_QueryParentStar_Invalid.txt
echo Finish running AutoTester for QueryParentStar_Invalid.
echo Running AutoTester for QueryPattern ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryPattern.txt TestResult\out24_First_QueryPattern.xml > TestResult\cmd\cmd24_First_QueryPattern.txt
echo Finish running AutoTester for QueryPattern.
echo Running AutoTester for QueryPattern_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryPattern_Invalid.txt TestResult\out24_First_QueryPattern_Invalid.xml > TestResult\cmd\cmd24_First_QueryPattern_Invalid.txt
echo Finish running AutoTester for QueryPattern_Invalid.
echo Running AutoTester for QueryUses ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryUses.txt TestResult\out24_First_QueryUses.xml > TestResult\cmd\cmd24_First_QueryUses.txt
echo Finish running AutoTester for QueryUses.
echo Running AutoTester for QueryUses_Invalid ...
AutoTester Test24_ZYSix\First\Source1.txt Test24_ZYSix\First\QueryUses_Invalid.txt TestResult\out24_First_QueryUses_Invalid.xml > TestResult\cmd\cmd24_First_QueryUses_Invalid.txt
echo Finish running AutoTester for QueryUses_Invalid.
echo Running AutoTester for QueryAffects ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryAffects.txt TestResult\out24_Third_QueryAffects.xml > TestResult\cmd\cmd24_Third_QueryAffects.txt
echo Finish running AutoTester for QueryAffects.
echo Running AutoTester for QueryAffects_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryAffects_Invalid.txt TestResult\out24_Third_QueryAffects_Invalid.xml > TestResult\cmd\cmd24_Third_QueryAffects_Invalid.txt
echo Finish running AutoTester for QueryAffects_Invalid.
echo Running AutoTester for QueryAffectsStar ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryAffectsStar.txt TestResult\out24_Third_QueryAffectsStar.xml > TestResult\cmd\cmd24_Third_QueryAffectsStar.txt
echo Finish running AutoTester for QueryAffectsStar.
echo Running AutoTester for QueryAffectsStar_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryAffectsStar_Invalid.txt TestResult\out24_Third_QueryAffectsStar_Invalid.xml > TestResult\cmd\cmd24_Third_QueryAffectsStar_Invalid.txt
echo Finish running AutoTester for QueryAffectsStar_Invalid.
echo Running AutoTester for QueryCalls ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryCalls.txt TestResult\out24_Third_QueryCalls.xml > TestResult\cmd\cmd24_Third_QueryCalls.txt
echo Finish running AutoTester for QueryCalls.
echo Running AutoTester for QueryCalls_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryCalls_Invalid.txt TestResult\out24_Third_QueryCalls_Invalid.xml > TestResult\cmd\cmd24_Third_QueryCalls_Invalid.txt
echo Finish running AutoTester for QueryCalls_Invalid.
echo Running AutoTester for QueryCallsStar ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryCallsStar.txt TestResult\out24_Third_QueryCallsStar.xml > TestResult\cmd\cmd24_Third_QueryCallsStar.txt
echo Finish running AutoTester for QueryCallsStar.
echo Running AutoTester for QueryCallsStar_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryCallsStar_Invalid.txt TestResult\out24_Third_QueryCallsStar_Invalid.xml > TestResult\cmd\cmd24_Third_QueryCallsStar_Invalid.txt
echo Finish running AutoTester for QueryCallsStar_Invalid.
echo Running AutoTester for QueryFollows ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryFollows.txt TestResult\out24_Third_QueryFollows.xml > TestResult\cmd\cmd24_Third_QueryFollows.txt
echo Finish running AutoTester for QueryFollows.
echo Running AutoTester for QueryFollows_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryFollows_Invalid.txt TestResult\out24_Third_QueryFollows_Invalid.xml > TestResult\cmd\cmd24_Third_QueryFollows_Invalid.txt
echo Finish running AutoTester for QueryFollows_Invalid.
echo Running AutoTester for QueryFollowsStar ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryFollowsStar.txt TestResult\out24_Third_QueryFollowsStar.xml > TestResult\cmd\cmd24_Third_QueryFollowsStar.txt
echo Finish running AutoTester for QueryFollowsStar.
echo Running AutoTester for QueryFollowsStar_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryFollowsStar_Invalid.txt TestResult\out24_Third_QueryFollowsStar_Invalid.xml > TestResult\cmd\cmd24_Third_QueryFollowsStar_Invalid.txt
echo Finish running AutoTester for QueryFollowsStar_Invalid.
echo Running AutoTester for QueryModifies ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryModifies.txt TestResult\out24_Third_QueryModifies.xml > TestResult\cmd\cmd24_Third_QueryModifies.txt
echo Finish running AutoTester for QueryModifies.
echo Running AutoTester for QueryModifies_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryModifies_Invalid.txt TestResult\out24_Third_QueryModifies_Invalid.xml > TestResult\cmd\cmd24_Third_QueryModifies_Invalid.txt
echo Finish running AutoTester for QueryModifies_Invalid.
echo Running AutoTester for QueryMultipleClauses ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryMultipleClauses.txt TestResult\out24_Third_QueryMultipleClauses.xml > TestResult\cmd\cmd24_Third_QueryMultipleClauses.txt
echo Finish running AutoTester for QueryMultipleClauses.
echo Running AutoTester for QueryNext ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryNext.txt TestResult\out24_Third_QueryNext.xml > TestResult\cmd\cmd24_Third_QueryNext.txt
echo Finish running AutoTester for QueryNext.
echo Running AutoTester for QueryNext_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryNext_Invalid.txt TestResult\out24_Third_QueryNext_Invalid.xml > TestResult\cmd\cmd24_Third_QueryNext_Invalid.txt
echo Finish running AutoTester for QueryNext_Invalid.
echo Running AutoTester for QueryNextStar ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryNextStar.txt TestResult\out24_Third_QueryNextStar.xml > TestResult\cmd\cmd24_Third_QueryNextStar.txt
echo Finish running AutoTester for QueryNextStar.
echo Running AutoTester for QueryNextStar_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryNextStar_Invalid.txt TestResult\out24_Third_QueryNextStar_Invalid.xml > TestResult\cmd\cmd24_Third_QueryNextStar_Invalid.txt
echo Finish running AutoTester for QueryNextStar_Invalid.
echo Running AutoTester for QueryParent ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryParent.txt TestResult\out24_Third_QueryParent.xml > TestResult\cmd\cmd24_Third_QueryParent.txt
echo Finish running AutoTester for QueryParent.
echo Running AutoTester for QueryParent_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryParent_Invalid.txt TestResult\out24_Third_QueryParent_Invalid.xml > TestResult\cmd\cmd24_Third_QueryParent_Invalid.txt
echo Finish running AutoTester for QueryParent_Invalid.
echo Running AutoTester for QueryParentStar ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryParentStar.txt TestResult\out24_Third_QueryParentStar.xml > TestResult\cmd\cmd24_Third_QueryParentStar.txt
echo Finish running AutoTester for QueryParentStar.
echo Running AutoTester for QueryParentStar_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryParentStar_Invalid.txt TestResult\out24_Third_QueryParentStar_Invalid.xml > TestResult\cmd\cmd24_Third_QueryParentStar_Invalid.txt
echo Finish running AutoTester for QueryParentStar_Invalid.
echo Running AutoTester for QueryPattern ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryPattern.txt TestResult\out24_Third_QueryPattern.xml > TestResult\cmd\cmd24_Third_QueryPattern.txt
echo Finish running AutoTester for QueryPattern.
echo Running AutoTester for QueryPattern_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryPattern_Invalid.txt TestResult\out24_Third_QueryPattern_Invalid.xml > TestResult\cmd\cmd24_Third_QueryPattern_Invalid.txt
echo Finish running AutoTester for QueryPattern_Invalid.
echo Running AutoTester for QueryUses ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryUses.txt TestResult\out24_Third_QueryUses.xml > TestResult\cmd\cmd24_Third_QueryUses.txt
echo Finish running AutoTester for QueryUses.
echo Running AutoTester for QueryUses_Invalid ...
AutoTester Test24_ZYSix\Third\Source3.txt Test24_ZYSix\Third\QueryUses_Invalid.txt TestResult\out24_Third_QueryUses_Invalid.xml > TestResult\cmd\cmd24_Third_QueryUses_Invalid.txt
echo Finish running AutoTester for QueryUses_Invalid.
echo Finish running AutoTester for test 24.
call :getPauseAction
goto :eof
