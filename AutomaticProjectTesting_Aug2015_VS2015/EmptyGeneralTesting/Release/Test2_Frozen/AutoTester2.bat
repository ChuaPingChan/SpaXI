@echo off
echo Generating Queries for test 2...
python QueryGenerator2.py QuerySet2.xlsx test2query.txt
echo Finish generating queries for test 2.
echo Running AutoTester for test 2...
..\AutoTester test2source.txt test2query.txt out2.xml > AutoTester2.txt
echo Finish running AutoTester for test 2.