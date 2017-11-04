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
echo [x] Exit
SpaxiSpeech\spaxi_welcome.vbs
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
AutoTester SampleTest\Sample-Source.txt SampleTest\Sample-Queries.txt TestResult\out_SampleTest_Sample-Queries.xml > TestResult\cmd\cmd_SampleTest_Sample-Queries.txt
echo Finish running AutoTester for Sample Test.
call :getPauseAction
goto :eof

:runSimple01
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for Simple Test 1...
AutoTester SimpleTest\Source_Simple01.txt SimpleTest\Query_Simple01.txt TestResult\out_SimpleTest_Query_Simple01.xml > TestResult\cmd\cmd_SimpleTest_Query_Simple01.txt
echo Finish running AutoTester Simple Test 1.
call :getPauseAction
goto :eof

:runSimple02
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for Simple Test 2...
AutoTester SimpleTest\Source_Simple02.txt SimpleTest\Query_Simple02.txt TestResult\out_SimpleTest_Query_Simple02.xml > TestResult\cmd\cmd_SimpleTest_Query_Simple02.txt
echo Finish running AutoTester Simple Test 2.
call :getPauseAction
goto :eof

:runSimple03
call :createCmdOutputFolder
echo ===============================================================================
echo Running AutoTester for Simple Test 3...
AutoTester SimpleTest\Source_Simple03.txt SimpleTest\Query_Simple03.txt TestResult\out_SimpleTest_Query_Simple03.xml > TestResult\cmd\cmd_SimpleTest_Query_Simple03.txt
echo Finish running AutoTester Simple Test 3.
call :getPauseAction
goto :eof
