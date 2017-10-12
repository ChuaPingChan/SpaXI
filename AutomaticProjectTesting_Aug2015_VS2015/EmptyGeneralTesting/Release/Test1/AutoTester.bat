@echo off
:main
echo Hi, what would you like to do:
echo [1] Run AutoTester
echo [2] Exit
set option=
set /p option=Please select your options:
if '%option%'=='1' (
	goto :generateQueries
)

:generateQueries
@echo on
python QueryGenerator.py
@echo off
pause
cls
goto :main

:close
goto eof