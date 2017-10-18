@echo off
:main
echo ===============================================================================
echo Welcome to Team 11 AutoTester (o.o)
echo ===============================================================================
echo Type the test index to run the test
echo [0] Receive a compliment
echo [?] Run AutoTester for test ?
echo [a] Run AutoTester for specified test path
echo [x] Exit
set option=
set /p option=Please select your options: 
if '%option%'=='0' (
	goto :generateCompliment
)
if '%option%'=='x' (
	goto :close
)
if '%option%'=='a' (
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
goto :main
echo ===============================================================================

:close
goto eof

:generateCompliment
@echo off
echo.
echo You are beautiful :) Thank you for teaching us!
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
AutoTester Test1_Frozen\test1source.txt Test1_Frozen\test1query.txt Test1_Frozen\out1.xml> Test1_Frozen\AutoTester1.txt
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
AutoTester Test2\test2source.txt Test2\test2query.txt Test2\out2.xml> Test2\AutoTester2.txt
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