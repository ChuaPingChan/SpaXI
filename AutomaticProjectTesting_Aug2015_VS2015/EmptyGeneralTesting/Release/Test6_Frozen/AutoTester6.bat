@echo off
:main
echo ===============================================================================
echo Welcome to Test 6 AutoTester 
echo ===============================================================================
echo Type the test index to run the test
echo [?] Run AutoTester for test ?
echo [s] Run AutoTester for specified test path
echo [a] Run AutoTester for all tests
echo [x] Exit
set option=
set /p option=Please select your options: 
if '%option%'=='x' (
	goto :close
)
if '%option%'=='a' (
	goto :runAll
)
if '%option%'=='s' (
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
if '%option%'=='6' (
	goto :runModifiesUsesParent
)
if '%option%'=='7' (
	goto :runMultipleRelationship01
)
if '%option%'=='8' (
	goto :runMultipleRelationship02
)
if '%option%'=='9' (
	goto :runNext
)
if '%option%'=='10' (
	goto :runNextNextStar
)
if '%option%'=='11' (
	goto :runNextStar
)
if '%option%'=='12' (
	goto :runPattern
)
if '%option%'=='13' (
	goto :runTuple
)
if '%option%'=='14' (
	goto :runWith
)
if '%option%'=='15' (
	goto :runSimple01
)
if '%option%'=='16' (
	goto :runSimple02
)
if '%option%'=='17' (
	goto :runSimple03
)
cls
goto :main
echo ===============================================================================

:close
goto eof

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

:runModifiesUsesParent
echo ===============================================================================
echo Running AutoTester for ModifiesUsesParent...
..\AutoTester 6_ModifiesUsesParent\ModifiesUsesParentSource01.txt 6_ModifiesUsesParent\ModifiesUsesParentQuery01.txt 6_ModifiesUsesParent\outModifiesUsesParent.xml > 6_ModifiesUsesParent\AutoTesterModifiesUsesParent.txt
echo Finish running AutoTester for ModifiesUsesParent.
pause
cls
goto :main

:runMultipleRelationship01
echo ===============================================================================
echo Running AutoTester for MultipleRelationship01...
..\AutoTester 7_MultipleRelationship01\MultipleRelationshipSource01.txt 7_MultipleRelationship01\MultipleRelationshipQuery01.txt 7_MultipleRelationship01\outMultipleRelationship01.xml > 7_MultipleRelationship01\AutoTesterMultipleRelationship01.txt
echo Finish running AutoTester for MultipleRelationship01.
pause
cls
goto :main

:runMultipleRelationship02
echo ===============================================================================
echo Running AutoTester for MultipleRelationship02...
..\AutoTester 8_MultipleRelationship02\MultipleRelationshipSource02.txt 8_MultipleRelationship02\MultipleRelationshipQuery02.txt 8_MultipleRelationship02\outMultipleRelationship02.xml > 8_MultipleRelationship02\AutoTesterMultipleRelationship02.txt
echo Finish running AutoTester for MultipleRelationship02.
pause
cls
goto :main

:runNext
echo ===============================================================================
echo Running AutoTester for Next...
..\AutoTester 9_Next\NEXT_SOURCE_01.txt 9_Next\NEXT_QUERIES_01.txt 9_Next\outNext.xml > 9_Next\AutoTesterNext.txt
echo Finish running AutoTester for Next.
pause
cls
goto :main

:runNextNextStar
echo ===============================================================================
echo Running AutoTester for NextNextStar...
..\AutoTester 10_NextNextStar\NEXT-NEXT-STAR_SOURCE_01.txt 10_NextNextStar\NEXT-NEXT-STAR_QUERIES_01.txt 10_NextNextStar\outNextNextStar.xml > 10_NextNextStar\AutoTesterNextNextStar.txt
echo Finish running AutoTester for NextNextStar.
pause
cls
goto :main

:runNextStar
echo ===============================================================================
echo Running AutoTester for NextStar...
..\AutoTester 11_NextStar\NEXT-STAR_SOURCE_01.txt 11_NextStar\NEXT-STAR_QUERIES_01.txt 11_NextStar\outNextStar.xml > 11_NextStar\AutoTesterNextStar.txt
echo Finish running AutoTester for NextStar.
pause
cls
goto :main

:runPattern
echo ===============================================================================
echo Running AutoTester for Pattern...
..\AutoTester 12_Pattern\PATTERN_SOURCE_01.txt 12_Pattern\PATTERN_QUERIES_01.txt 12_Pattern\outPattern.xml > 12_Pattern\AutoTesterPattern.txt
echo Finish running AutoTester for Pattern.
pause
cls
goto :main

:runTuple
echo ===============================================================================
echo Running AutoTester for Tuple...
..\AutoTester 13_Tuple\TUPLE_TESTS_SOURCE_01.txt 13_Tuple\TUPLE_TESTS_QUERIES_01.txt 13_Tuple\outTuple.xml > 13_Tuple\AutoTesterTuple.txt
echo Finish running AutoTester for Tuple.
pause
cls
goto :main

:runWith
echo ===============================================================================
echo Running AutoTester for With...
..\AutoTester 14_With\WITH_SOURCE_01.txt 14_With\WITH_QUERIES_01.txt 14_With\outWith.xml > 14_With\AutoTesterWith.txt
echo Finish running AutoTester for With.
pause
cls
goto :main

:runSimple01
echo ===============================================================================
echo Running AutoTester for Simple01...
..\AutoTester 15_Simple01\Simple01-Source.txt 15_Simple01\Simple01-Queries.txt 15_Simple01\outSimple01.xml > 15_Simple01\AutoTesterSimple01.txt
echo Finish running AutoTester for Simple01.
pause
cls
goto :main

:runSimple02
echo ===============================================================================
echo Running AutoTester for Simple02...
..\AutoTester 16_Simple02\Simple02-Source.txt 16_Simple02\Simple02-Queries.txt 16_Simple02\outSimple02.xml > 16_Simple02\AutoTesterSimple02.txt
echo Finish running AutoTester for Simple02.
pause
cls
goto :main

:runSimple03
echo ===============================================================================
echo Running AutoTester for Simple03...
..\AutoTester 17_Simple03\Simple03-Source.txt 17_Simple03\Simple03-Queries.txt 17_Simple03\outSimple03.xml > 17_Simple03\AutoTesterSimple03.txt
echo Finish running AutoTester for Simple03.
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

:runAll
echo ===============================================================================
echo Running All Tests...
echo Running AutoTester for Demo_Calls...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_Calls.txt ZoutputZ\outDemo_Calls.xml > ZoutputZ\AutoTesterDemo_Calls.txt
echo Finish running AutoTester for Demo_Calls.
echo Running AutoTester for Demo_CallsStar...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_CallsStar.txt ZoutputZ\outDemo_CallsStar.xml > ZoutputZ\AutoTesterDemo_CallsStar.txt
echo Finish running AutoTester for Demo_CallsStar.
echo Running AutoTester for Demo_Follows...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_Follows.txt ZoutputZ\outDemo_Follows.xml > ZoutputZ\AutoTesterDemo_Follows.txt
echo Finish running AutoTester for Demo_Follows.
echo Running AutoTester for Demo_FollowsStar...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_FollowsStar.txt ZoutputZ\outDemo_FollowsStar.xml > ZoutputZ\AutoTesterDemo_FollowsStar.txt
echo Finish running AutoTester for Demo_FollowsStar.
echo Running AutoTester for Demo_Modifies...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_Modifies.txt ZoutputZ\outDemo_Modifies.xml > ZoutputZ\AutoTesterDemo_Modifies.txt
echo Finish running AutoTester for Demo_Modifies.
echo Running AutoTester for Demo_Next...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_Next.txt ZoutputZ\outDemo_Next.xml > ZoutputZ\AutoTesterDemo_Next.txt
echo Finish running AutoTester for Demo_Next.
echo Running AutoTester for Demo_NextStar...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_NextStar.txt ZoutputZ\outDemo_NextStar.xml > ZoutputZ\AutoTesterDemo_NextStar.txt
echo Finish running AutoTester for Demo_NextStar.
echo Running AutoTester for Demo_Parent...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_Parent.txt ZoutputZ\outDemo_Parent.xml > ZoutputZ\AutoTesterDemo_Parent.txt
echo Finish running AutoTester for Demo_Parent.
echo Running AutoTester for Demo_ParentStar...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_ParentStar.txt ZoutputZ\outDemo_ParentStar.xml > ZoutputZ\AutoTesterDemo_ParentStar.txt
echo Finish running AutoTester for Demo_ParentStar.
echo Running AutoTester for Demo_Uses...
..\AutoTester 1_Demo\Demo_Source.txt 1_Demo\Demo_Uses.txt ZoutputZ\outDemo_Uses.xml > ZoutputZ\AutoTesterDemo_Uses.txt
echo Finish running AutoTester for Demo_Uses.
echo Running AutoTester for CALLS_01...
..\AutoTester 2_Calls\CALLS_SOURCE_01.txt 2_Calls\CALLS_QUERIES_01.txt ZoutputZ\outCALLS_01.xml > ZoutputZ\AutoTesterCALLS_01.txt
echo Finish running AutoTester for CALLS_01.
echo Running AutoTester for FOLLOWS_01...
..\AutoTester 3_Follows\FOLLOWS_SOURCE_01.txt 3_Follows\FOLLOWS_QUERIES_01.txt ZoutputZ\outFOLLOWS.xml > ZoutputZ\AutoTesterFOLLOWS.txt
echo Finish running AutoTester for FOLLOWS_01.
echo Running AutoTester for MixTests01...
..\AutoTester 4_MixTests01\MixTestsSource01.txt 4_MixTests01\MixTestsQuery01.txt ZoutputZ\outMixTests01.xml > ZoutputZ\AutoTesterMixTests01.txt
echo Finish running AutoTester for MixTests01.
echo Running AutoTester for MixTests02...
..\AutoTester 5_MixTests02\MixTestsSource02.txt 5_MixTests02\MixTestsQuery02.txt ZoutputZ\outMixTests02.xml > ZoutputZ\AutoTesterMixTests02.txt
echo Finish running AutoTester for MixTests02.
echo Running AutoTester for ModifiesUsesParent...
..\AutoTester 6_ModifiesUsesParent\ModifiesUsesParentSource01.txt 6_ModifiesUsesParent\ModifiesUsesParentQuery01.txt ZoutputZ\outModifiesUsesParent.xml > ZoutputZ\AutoTesterModifiesUsesParent.txt
echo Finish running AutoTester for ModifiesUsesParent.
echo Running AutoTester for MultipleRelationship01...
..\AutoTester 7_MultipleRelationship01\MultipleRelationshipSource01.txt 7_MultipleRelationship01\MultipleRelationshipQuery01.txt ZoutputZ\outMultipleRelationship01.xml > ZoutputZ\AutoTesterMultipleRelationship01.txt
echo Finish running AutoTester for MultipleRelationship01.
echo Running AutoTester for MultipleRelationship02...
..\AutoTester 8_MultipleRelationship02\MultipleRelationshipSource02.txt 8_MultipleRelationship02\MultipleRelationshipQuery02.txt ZoutputZ\outMultipleRelationship02.xml > ZoutputZ\AutoTesterMultipleRelationship02.txt
echo Finish running AutoTester for MultipleRelationship02.
echo Running AutoTester for Next...
..\AutoTester 9_Next\NEXT_SOURCE_01.txt 9_Next\NEXT_QUERIES_01.txt ZoutputZ\outNext.xml > ZoutputZ\AutoTesterNext.txt
echo Finish running AutoTester for Next.
echo Running AutoTester for NextNextStar...
..\AutoTester 10_NextNextStar\NEXT-NEXT-STAR_SOURCE_01.txt 10_NextNextStar\NEXT-NEXT-STAR_QUERIES_01.txt ZoutputZ\outNextNextStar.xml > ZoutputZ\AutoTesterNextNextStar.txt
echo Finish running AutoTester for NextNextStar.
echo Running AutoTester for NextStar...
..\AutoTester 11_NextStar\NEXT-STAR_SOURCE_01.txt 11_NextStar\NEXT-STAR_QUERIES_01.txt ZoutputZ\outNextStar.xml > ZoutputZ\AutoTesterNextStar.txt
echo Finish running AutoTester for NextStar.
echo Running AutoTester for Pattern...
..\AutoTester 12_Pattern\PATTERN_SOURCE_01.txt 12_Pattern\PATTERN_QUERIES_01.txt ZoutputZ\outPattern.xml > ZoutputZ\AutoTesterPattern.txt
echo Finish running AutoTester for Pattern.
echo Running AutoTester for Tuple...
..\AutoTester 13_Tuple\TUPLE_TESTS_SOURCE_01.txt 13_Tuple\TUPLE_TESTS_QUERIES_01.txt ZoutputZ\outTuple.xml > ZoutputZ\AutoTesterTuple.txt
echo Finish running AutoTester for Tuple.
echo Running AutoTester for With...
..\AutoTester 14_With\WITH_SOURCE_01.txt 14_With\WITH_QUERIES_01.txt ZoutputZ\outWith.xml > ZoutputZ\AutoTesterWith.txt
echo Finish running AutoTester for With.
echo Running AutoTester for Simple01...
..\AutoTester 15_Simple01\Simple01-Source.txt 15_Simple01\Simple01-Queries.txt ZoutputZ\outSimple01.xml > ZoutputZ\AutoTesterSimple01.txt
echo Finish running AutoTester for Simple01.
echo Running AutoTester for Simple02...
..\AutoTester 16_Simple02\Simple02-Source.txt 16_Simple02\Simple02-Queries.txt ZoutputZ\outSimple02.xml > ZoutputZ\AutoTesterSimple02.txt
echo Finish running AutoTester for Simple02.
echo Running AutoTester for Simple03...
..\AutoTester 17_Simple03\Simple03-Source.txt 17_Simple03\Simple03-Queries.txt ZoutputZ\outSimple03.xml > ZoutputZ\AutoTesterSimple03.txt
echo Finish running AutoTester for Simple03.
echo Finish running All Tests.
pause
cls
goto :main