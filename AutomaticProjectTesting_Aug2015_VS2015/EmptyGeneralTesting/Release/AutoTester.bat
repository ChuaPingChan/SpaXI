@echo off
:main
echo Welcome to Team 11 AutoTester
echo ==========================================================
echo [0] Generate all queries from xls to txt
echo [1] Run AutoTester for test 1
echo [2] Run AutoTester for test 2
echo [3] Run AutoTester for test 3
echo [a] Run AutoTester for all tests
echo [x] Exit
set option=
set /p option=Please select your options: 
if '%option%'=='0' (
	goto :generateQueries
)
if '%option%'=='a' (
	goto :runAllTests
)
if '%option%'=='x' (
	goto :close
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

goto :main
echo ==========================================================

:close
goto eof

:generateQueries
@echo on
python Test1/QueryGenerator.py
python Test2/QueryGenerator.py
@echo off
pause
cls
goto :main

:runAllTests
@echo on
echo Running AutoTester ...
::Run all python files
python Test1/QueryGenerator.py
python Test2/QueryGenerator.py
::Run all AutoTester
AutoTester Test1/test1.txt Test1/testQuery1.txt Test1/outTest1.xml
AutoTester Test2/ZYTest.txt Test2/testQuery2.txt Test2/outTest2.xml
AutoTester Test3/test3source.txt Test3/test3query.txt Test3/outTest3.xml
@echo off
pause
cls
goto :main

:runTest1
@echo on
python Test1/QueryGenerator.py
echo Running AutoTester ...
AutoTester Test1/test1.txt Test1/testQuery1.txt Test1/outTest1.xml
@echo off
pause
cls
goto :main

:runTest2
@echo on
python Test2/QueryGenerator.py
echo Running AutoTester ...
AutoTester Test2/ZYTest.txt Test2/testQuery2.txt Test2/outTest2.xml
@echo off
pause
cls
goto :main

:runTest3
@echo on
echo Running AutoTester ...
AutoTester Test3/test3source.txt Test3/test3query.txt Test3/outTest3.xml
@echo off
pause
cls
goto :main
