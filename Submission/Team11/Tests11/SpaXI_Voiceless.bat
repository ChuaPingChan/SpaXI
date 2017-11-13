@echo off
:main
set isPause=1
echo ===============================================================================
echo Welcome to Team 11 static program analyzer. I am SpaXI.
echo ===============================================================================
echo Type the test index to run the test
echo [c] Receive a compliment
echo [s] Run AutoTester for specified test path
echo [a] Run All Tests
echo [0] Run Sample Test
echo [1] Run Simple01 Test
echo [2] Run Simple02 Test
echo [3] Run Simple03 Test
echo [4] Run FocusTest\Sequential
echo [5] Run FocusTest\Loop
echo [6] Run FocusTest\InterProcedural
echo [7] Run Validation Test
echo [8] Run Stress Test
echo [x] Exit
set option=
set /p option=Please select your options: 
if '%option%'=='c' (
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
if '%option%'=='0' (
	goto :runSampleTest
)
if '%option%'=='1' (
	goto :runSimple01
)
if '%option%'=='2' (
	goto :runSimple02
)
if '%option%'=='3' (
	goto :runSimple03
)
if '%option%'=='4' (
	goto :runSequential
)
if '%option%'=='5' (
	goto :runLoop
)
if '%option%'=='6' (
	goto :runInterProcedural
)
if '%option%'=='7' (
	goto :runValidation
)
if '%option%'=='8' (
	goto :runStress
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
call :runSampleTest
call :runSimple01
call :runSimple02
call :runSimple03
call :runSequential
call :runLoop
call :runValidation
call :runStress
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

:runSampleTest
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for Sample Test...
AutoTester 1_SampleTest\Sample-Source.txt 1_SampleTest\Sample-Queries.txt TestResult\out_SampleTest_Sample-Queries.xml > TestResult\cmd\cmd_SampleTest_Sample-Queries.txt
echo Finish running AutoTester for Sample Test.
call :getPauseAction
goto :eof

:runSimple01
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for Simple Test 1...
AutoTester 2_SimpleTest\Simple01\Source_Simple01.txt 2_SimpleTest\Simple01\Query_Simple01.txt TestResult\out_SimpleTest_Query_Simple01.xml > TestResult\cmd\cmd_SimpleTest_Query_Simple01.txt
echo Finish running AutoTester Simple Test 1.
call :getPauseAction
goto :eof

:runSimple02
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for Simple Test 2...
AutoTester 2_SimpleTest\Simple02\Source_Simple02.txt 2_SimpleTest\Simple02\Query_Simple02.txt TestResult\out_SimpleTest_Query_Simple02.xml > TestResult\cmd\cmd_SimpleTest_Query_Simple02.txt
echo Finish running AutoTester Simple Test 2.
call :getPauseAction
goto :eof

:runSimple03
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for Simple Test 3...
AutoTester 2_SimpleTest\Simple03\Source_Simple03.txt 2_SimpleTest\Simple03\Query_Simple03.txt TestResult\out_SimpleTest_Query_Simple03.xml > TestResult\cmd\cmd_SimpleTest_Query_Simple03.txt
echo Finish running AutoTester Simple Test 3.
call :getPauseAction
goto :eof

:runSequential
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for Sequential...
echo Running AutoTester for 3_FocusTest\1_Sequential\QueryFollows...
AutoTester 3_FocusTest\1_Sequential\SourceSequential.txt 3_FocusTest\1_Sequential\QueryFollows.txt TestResult\out_FocusTest_Sequential_QueryFollows.xml > TestResult\cmd\cmd_FocusTest_Sequential_QueryFollows.txt
echo Finish running AutoTester 3_FocusTest\1_Sequential\QueryFollows.
echo Running AutoTester for 3_FocusTest\1_Sequential\QueryFollowsStar...
AutoTester 3_FocusTest\1_Sequential\SourceSequential.txt 3_FocusTest\1_Sequential\QueryFollowsStar.txt TestResult\out_FocusTest_Sequential_QueryFollowsStar.xml > TestResult\cmd\cmd_FocusTest_Sequential_QueryFollowsStar.txt
echo Finish running AutoTester 3_FocusTest\1_Sequential\QueryFollowsStar.
echo Running AutoTester for 3_FocusTest\1_Sequential\QueryPatternAssign...
AutoTester 3_FocusTest\1_Sequential\SourceSequential.txt 3_FocusTest\1_Sequential\QueryPatternAssign.txt TestResult\out_FocusTest_Sequential_QueryPatternAssign.xml > TestResult\cmd\cmd_FocusTest_Sequential_QueryPatternAssign.txt
echo Finish running AutoTester 3_FocusTest\1_Sequential\QueryPatternAssign.
echo Running AutoTester for 3_FocusTest\1_Sequential\QueryWith...
AutoTester 3_FocusTest\1_Sequential\SourceSequential.txt 3_FocusTest\1_Sequential\QueryWith.txt TestResult\out_FocusTest_Sequential_QueryWith.xml > TestResult\cmd\cmd_FocusTest_Sequential_QueryWith.txt
echo Finish running AutoTester 3_FocusTest\1_Sequential\QueryWith.
echo Finish running AutoTester Sequential.
call :getPauseAction
goto :eof

:runLoop
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for Loop...
echo Running AutoTester for 3_FocusTest\2_Loop\QueryAffects...
AutoTester 3_FocusTest\2_Loop\SourceLoop.txt 3_FocusTest\2_Loop\QueryAffects.txt TestResult\out_FocusTest_Loop_QueryAffects.xml > TestResult\cmd\cmd_FocusTest_Loop_QueryAffects.txt
echo Finish running AutoTester 3_FocusTest\2_Loop\QueryAffects.
echo Running AutoTester for 3_FocusTest\2_Loop\QueryAffectsStar...
AutoTester 3_FocusTest\2_Loop\SourceLoop.txt 3_FocusTest\2_Loop\QueryAffectsStar.txt TestResult\out_FocusTest_Loop_QueryAffectsStar.xml > TestResult\cmd\cmd_FocusTest_Loop_QueryAffectsStar.txt
echo Finish running AutoTester 3_FocusTest\2_Loop\QueryAffectsStar.
echo Running AutoTester for 3_FocusTest\2_Loop\QueryModifies...
AutoTester 3_FocusTest\2_Loop\SourceLoop.txt 3_FocusTest\2_Loop\QueryModifies.txt TestResult\out_FocusTest_Loop_QueryModifies.xml > TestResult\cmd\cmd_FocusTest_Loop_QueryModifies.txt
echo Finish running AutoTester 3_FocusTest\2_Loop\QueryModifies.
echo Running AutoTester for 3_FocusTest\2_Loop\QueryNext...
AutoTester 3_FocusTest\2_Loop\SourceLoop.txt 3_FocusTest\2_Loop\QueryNext.txt TestResult\out_FocusTest_Loop_QueryNext.xml > TestResult\cmd\cmd_FocusTest_Loop_QueryNext.txt
echo Finish running AutoTester 3_FocusTest\2_Loop\QueryNext.
echo Running AutoTester for 3_FocusTest\2_Loop\QueryNextStar...
AutoTester 3_FocusTest\2_Loop\SourceLoop.txt 3_FocusTest\2_Loop\QueryNextStar.txt TestResult\out_FocusTest_Loop_QueryNextStar.xml > TestResult\cmd\cmd_FocusTest_Loop_QueryNextStar.txt
echo Finish running AutoTester 3_FocusTest\2_Loop\QueryNextStar.
echo Running AutoTester for 3_FocusTest\2_Loop\QueryParent...
AutoTester 3_FocusTest\2_Loop\SourceLoop.txt 3_FocusTest\2_Loop\QueryParent.txt TestResult\out_FocusTest_Loop_QueryParent.xml > TestResult\cmd\cmd_FocusTest_Loop_QueryParent.txt
echo Finish running AutoTester 3_FocusTest\2_Loop\QueryParent.
echo Running AutoTester for 3_FocusTest\2_Loop\QueryParentStar...
AutoTester 3_FocusTest\2_Loop\SourceLoop.txt 3_FocusTest\2_Loop\QueryParentStar.txt TestResult\out_FocusTest_Loop_QueryParentStar.xml > TestResult\cmd\cmd_FocusTest_Loop_QueryParentStar.txt
echo Finish running AutoTester 3_FocusTest\2_Loop\QueryParentStar.
echo Running AutoTester for 3_FocusTest\2_Loop\QueryPattern...
AutoTester 3_FocusTest\2_Loop\SourceLoop.txt 3_FocusTest\2_Loop\QueryPattern.txt TestResult\out_FocusTest_Loop_QueryPattern.xml > TestResult\cmd\cmd_FocusTest_Loop_QueryPattern.txt
echo Finish running AutoTester 3_FocusTest\2_Loop\QueryPattern.
echo Running AutoTester for 3_FocusTest\2_Loop\QueryUses...
AutoTester 3_FocusTest\2_Loop\SourceLoop.txt 3_FocusTest\2_Loop\QueryUses.txt TestResult\out_FocusTest_Loop_QueryUses.xml > TestResult\cmd\cmd_FocusTest_Loop_QueryUses.txt
echo Finish running AutoTester 3_FocusTest\2_Loop\QueryUses.
echo Finish running AutoTester Loop.
call :getPauseAction
goto :eof

:runInterProcedural
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for InterProcedural...
echo Running AutoTester for 3_FocusTest\3_InterProcedural\QueryAffects...
AutoTester 3_FocusTest\3_InterProcedural\SourceInterProcedural.txt 3_FocusTest\3_InterProcedural\QueryAffects.txt TestResult\out_FocusTest_InterProcedural_QueryAffects.xml > TestResult\cmd\cmd_FocusTest_InterProcedural_QueryAffects.txt
echo Finish running AutoTester 3_FocusTest\3_InterProcedural\QueryAffects.
echo Running AutoTester for 3_FocusTest\3_InterProcedural\QueryAffectsStar...
AutoTester 3_FocusTest\3_InterProcedural\SourceInterProcedural.txt 3_FocusTest\3_InterProcedural\QueryAffectsStar.txt TestResult\out_FocusTest_InterProcedural_QueryAffectsStar.xml > TestResult\cmd\cmd_FocusTest_InterProcedural_QueryAffectsStar.txt
echo Finish running AutoTester 3_FocusTest\3_InterProcedural\QueryAffectsStar.
echo Running AutoTester for 3_FocusTest\3_InterProcedural\QueryCalls...
AutoTester 3_FocusTest\3_InterProcedural\SourceInterProcedural.txt 3_FocusTest\3_InterProcedural\QueryCalls.txt TestResult\out_FocusTest_InterProcedural_QueryCalls.xml > TestResult\cmd\cmd_FocusTest_InterProcedural_QueryCalls.txt
echo Finish running AutoTester 3_FocusTest\3_InterProcedural\QueryCalls.
echo Running AutoTester for 3_FocusTest\3_InterProcedural\QueryCallsStar...
AutoTester 3_FocusTest\3_InterProcedural\SourceInterProcedural.txt 3_FocusTest\3_InterProcedural\QueryCallsStar.txt TestResult\out_FocusTest_InterProcedural_QueryCallsStar.xml > TestResult\cmd\cmd_FocusTest_InterProcedural_QueryCallsStar.txt
echo Finish running AutoTester 3_FocusTest\3_InterProcedural\QueryCallsStar.
echo Running AutoTester for 3_FocusTest\3_InterProcedural\QueryModifies...
AutoTester 3_FocusTest\3_InterProcedural\SourceInterProcedural.txt 3_FocusTest\3_InterProcedural\QueryModifies.txt TestResult\out_FocusTest_InterProcedural_QueryModifies.xml > TestResult\cmd\cmd_FocusTest_InterProcedural_QueryModifies.txt
echo Finish running AutoTester 3_FocusTest\3_InterProcedural\QueryModifies.
echo Running AutoTester for 3_FocusTest\3_InterProcedural\QueryNext...
AutoTester 3_FocusTest\3_InterProcedural\SourceInterProcedural.txt 3_FocusTest\3_InterProcedural\QueryNext.txt TestResult\out_FocusTest_InterProcedural_QueryNext.xml > TestResult\cmd\cmd_FocusTest_InterProcedural_QueryNext.txt
echo Finish running AutoTester 3_FocusTest\3_InterProcedural\QueryNext.
echo Running AutoTester for 3_FocusTest\3_InterProcedural\QueryNextStar...
AutoTester 3_FocusTest\3_InterProcedural\SourceInterProcedural.txt 3_FocusTest\3_InterProcedural\QueryNextStar.txt TestResult\out_FocusTest_InterProcedural_QueryNextStar.xml > TestResult\cmd\cmd_FocusTest_InterProcedural_QueryNextStar.txt
echo Finish running AutoTester 3_FocusTest\3_InterProcedural\QueryNextStar.
echo Running AutoTester for 3_FocusTest\3_InterProcedural\QueryUses...
AutoTester 3_FocusTest\3_InterProcedural\SourceInterProcedural.txt 3_FocusTest\3_InterProcedural\QueryUses.txt TestResult\out_FocusTest_InterProcedural_QueryUses.xml > TestResult\cmd\cmd_FocusTest_InterProcedural_QueryUses.txt
echo Finish running AutoTester 3_FocusTest\3_InterProcedural\QueryUses.
echo Finish running AutoTester InterProcedural.
call :getPauseAction
goto :eof

:runValidation
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for Validation...
AutoTester 4_ValidationTest\SourceValidation.txt 4_ValidationTest\QueryValidation.txt TestResult\out_Validation_QueryValidation.xml > TestResult\cmd\cmd_Valiadaion_QueryValidation.txt
echo Finish running AutoTester Validation.
call :getPauseAction
goto :eof

:runStress
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for Stress...
echo Running AutoTester for StressTest\Affects...
AutoTester 5_StressTest\SourceStress.txt 5_StressTest\QueryStressAffects.txt TestResult\out_Stress_QueryStressAffects.xml > TestResult\cmd\cmd_Stress_QueryStressAffects.txt
echo Finish running AutoTester StressTestAffects.
echo Running AutoTester for StressTest\Mixed...
AutoTester 5_StressTest\SourceStress.txt 5_StressTest\QueryStressMixed.txt TestResult\out_Stress_QueryStressMixed.xml > TestResult\cmd\cmd_Stress_QueryStressMixed.txt
echo Finish running AutoTester StressTestMixed.
echo Running AutoTester for StressTest\Next...
AutoTester 5_StressTest\SourceStress.txt 5_StressTest\QueryStressNext.txt TestResult\out_Stress_QueryStressNext.xml > TestResult\cmd\cmd_Stress_QueryStressNext.txt
echo Finish running AutoTester StressTestNext.
echo Finish running AutoTester Stress.
call :getPauseAction
goto :eof
