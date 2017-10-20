@echo off
:main
echo ===============================================================================
echo Welcome to Test 6 AutoTester 
echo ===============================================================================
echo Type the test index to run the test
echo [?] Run AutoTester for test ?
echo [a] Run AutoTester for specified test path
echo [e] Run AutoTester for every test
echo [x] Exit
set option=
set /p option=Please select your options: 
if '%option%'=='x' (
	goto :close
)
if '%option%'=='a' (
	goto :runGivenTest
)
if '%option%'=='e' (
	goto :runGivenTest
)
if '%option%'=='1' (
	goto :runDemo
)
if '%option%'=='2' (
	goto :runCalls
)
if '%option%'=='3' (
	goto :runFollows
)
if '%option%'=='4' (
	goto :runMixTests01
)
if '%option%'=='5' (
	goto :runMixTests02
)
cls
goto :main
echo ===============================================================================

:close
goto eof

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

:runDemo
echo ===============================================================================
echo Running AutoTester for Demo_Calls...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_Calls.txt 1_Demo\outDemo_Calls.xml > 1_Demo\AutoTesterDemo_Calls.txt
echo Finish running AutoTester for Demo_Calls.
echo Running AutoTester for Demo_CallsStar...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_CallsStar.txt 1_Demo\outDemo_CallsStar.xml > 1_Demo\AutoTesterDemo_CallsStar.txt
echo Finish running AutoTester for Demo_CallsStar.
echo Running AutoTester for Demo_Follows...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_Follows.txt 1_Demo\outDemo_Follows.xml > 1_Demo\AutoTesterDemo_Follows.txt
echo Finish running AutoTester for Demo_Follows.
echo Running AutoTester for Demo_FollowsStar...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_FollowsStar.txt 1_Demo\outDemo_FollowsStar.xml > 1_Demo\AutoTesterDemo_FollowsStar.txt
echo Finish running AutoTester for Demo_FollowsStar.
echo Running AutoTester for Demo_Modifies...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_Modifies.txt 1_Demo\outDemo_Modifies.xml > 1_Demo\AutoTesterDemo_Modifies.txt
echo Finish running AutoTester for Demo_Modifies.
echo Running AutoTester for Demo_Next...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_Next.txt 1_Demo\outDemo_Next.xml > 1_Demo\AutoTesterDemo_Next.txt
echo Finish running AutoTester for Demo_Next.
echo Running AutoTester for Demo_NextStar...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_NextStar.txt 1_Demo\outDemo_NextStar.xml > 1_Demo\AutoTesterDemo_NextStar.txt
echo Finish running AutoTester for Demo_NextStar.
echo Running AutoTester for Demo_Parent...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_Parent.txt 1_Demo\outDemo_Parent.xml > 1_Demo\AutoTesterDemo_Parent.txt
echo Finish running AutoTester for Demo_Parent.
echo Running AutoTester for Demo_ParentStar...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_ParentStar.txt 1_Demo\outDemo_ParentStar.xml > 1_Demo\AutoTesterDemo_ParentStar.txt
echo Finish running AutoTester for Demo_ParentStar.
echo Running AutoTester for Demo_Uses...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_Uses.txt 1_Demo\outDemo_Uses.xml > 1_Demo\AutoTesterDemo_Uses.txt
echo Finish running AutoTester for Demo_Uses.
pause
cls
goto :main

:runCalls
echo ===============================================================================
echo Running AutoTester for CALLS_01...
..\AutoTester 2_Calls\CALLS_SOURCE_01.txt 2_Calls\CALLS_QUERIES_01.txt 2_Calls\outCALLS_01.xml > 2_Calls\AutoTesterCALLS_01.txt
echo Finish running AutoTester for CALLS_01.
pause
cls
goto :main

:runFollows
echo ===============================================================================
echo Running AutoTester for FOLLOWS_01...
..\AutoTester 3_Follows\FOLLOWS_SOURCE_01.txt 3_Follows\FOLLOWS_QUERIES_01.txt 3_Follows\outFOLLOWS.xml > 3_Follows\AutoTesterFOLLOWS.txt
echo Finish running AutoTester for FOLLOWS_01.
pause
cls
goto :main

:runMixTests01
echo ===============================================================================
echo Running AutoTester for MixTests01...
..\AutoTester 4_MixTests01\MixTestsSource01.txt 4_MixTests01\MixTestsQuery01.txt 4_MixTests01\outMixTests01.xml > 4_MixTests01\AutoTesterMixTests01.txt
echo Finish running AutoTester for MixTests01.
pause
cls
goto :main

:runMixTests02
echo ===============================================================================
echo Running AutoTester for MixTests02...
..\AutoTester 5_MixTests02\MixTestsSource02.txt 5_MixTests02\MixTestsQuery02.txt 5_MixTests02\outMixTests02.xml > 5_MixTests02\AutoTesterMixTests02.txt
echo Finish running AutoTester for MixTests02.
pause
cls
goto :main