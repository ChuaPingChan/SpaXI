@echo off
echo Generating queries for test 1...
python QueryGenerator1.py QuerySet1.xlsx test1query.txt
echo Finish generating queries for test 1.
echo Running AutoTester for test 1...
..\AutoTester test1source.txt test1query.txt out1.xml > AutoTester1.txt
echo Finish running AutoTester for test 1.