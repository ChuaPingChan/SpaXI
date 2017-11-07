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
call :runTest18
call :runTest19
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
::echo Running AutoTester for QueryNextStar_Performance_UsingSource2.txt...
::AutoTester Test13_Seven\2_Two\Source2.txt Test13_Seven\2_Two\QueryNextStar_Performance_UsingSource2.txt TestResult\out13_Two_QueryNextStar_Performance_UsingSource2.xml > TestResult\cmd\cmd13_Two_QueryNextStar_Performance_UsingSource2.txt
::echo Finish running AutoTester for QueryNextStar_Performance_UsingSource2.txt.
echo -- TIMEOUT! -- QueryNextStar_Performance_UsingSource2.txt has been commented away in the bat file -- ! --
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
::echo Running AutoTester for Query4.txt...
::AutoTester Test13_Seven\4_Intense\Source4.txt Test13_Seven\4_Intense\Query4.txt TestResult\out13_Intense_Query4.xml > TestResult\cmd\cmd13_Intense_Query4.txt
::echo Finish running AutoTester for Query4.txt.
echo -- TIMEOUT! -- Query4.txt has been commented away in the bat file -- ! --
echo Running AutoTester for Query5.txt...
AutoTester Test13_Seven\4_Intense\Source5.txt Test13_Seven\4_Intense\Query5.txt TestResult\out13_Intense_Query5.xml > TestResult\cmd\cmd13_Intense_Query5.txt
echo Finish running AutoTester for Query5.txt.
REM echo -- TIMEOUT! -- Query5.txt has been commented away in the bat file -- ! --
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
::echo Running AutoTester for Query3b.txt...
::AutoTester Test14_Frozen\Source3b.txt Test14_Frozen\Query3b.txt TestResult\out14_Query3b.xml > TestResult\cmd\cmd14_Query3b.txt
echo -- TIMEOUT! -- Query3b.txt has been commented away in the bat file -- ! --
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
echo Finish running AutoTester for test 15.
call :getPauseAction
goto :eof

:runTest16
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for test 16...
AutoTester Test16_Stress\SourceStress.txt Test16_Stress\QueryStressNext.txt TestResult\out16_QueryStressNext.xml > TestResult\cmd\cmd16_QueryStressNext.txt
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
