@echo off
echo Generating Queries for test 5...
python QueryGenerator5.py QuerySet5.xlsx test5query.txt
echo Finish generating queries for test 5.
echo Running AutoTester for test 5...
..\AutoTester test5source.txt test5query.txt out5.xml > AutoTester5.txt
echo Finish running AutoTester for test 5.