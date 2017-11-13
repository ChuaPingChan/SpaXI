Welcome, I am SpaXI, the static program analyzer of Team 11. (Turn up your volume, I do talk)

To get me started, 
- execute SpaXI.bat

Before running any of the tests, why not start off by receiving a compliment?
To receive a praise from me, 
- enter [c]

To run all the tests that I owned,
- enter [a]
Sit back and watch the magic unfold.
All the results will be directed to [TestResult].
Output from cmd will be directed to [TestResult\cmd]
A summary will be generated at the end.
*Python has to be installed for summary to be generated.
*Python can be installed at https://www.python.org/

If you are interested in a specific test, you just need to give me the test number:
[0] Run Sample Test
[1] Run Simple01 Test
[2] Run Simple02 Test
[3] Run Simple03 Test
[4] Run FocusTest\Sequential
[5] Run FocusTest\Loop
[6] Run FocusTest\InterProcedural
[7] Run Validation Test
[8] Run Stress Test
All the results will be directed to [TestResult].
Output from cmd will be directed to [TestResult\cmd]

If you want me to analyse your personal program,
- enter [s]
Don't worry, I will guide you along.

That's all! Thank you! Have a great day ahead!

*Stress tests are used to test my upper limits of processing. Some queries are impossible for me to deliver under 5s.

======================================================================
My shortcomings
======================================================================
I am able to generate a ".\Summary.txt" after the system test is completed using a Python script. However, if you are afraid of snakes and don't have Python installed on your computer, the tests will still run fine, only without the summary file generated at the end.

Should I fail to run as expected, try the following:
1) Open the SPA project by double-clicking the solution file called "..\Code11\EmptyGeneralTesting.sln" using Visual Studio 2015.
2) Build the solution in release mode. The "AutoTester.exe" file will be generated in "..\Code11\Release\AutoTester.exe".
3) Copy the "AutoTester.exe" into this directory.
4) Run AutoTester in the command prompt with this command:
	AutoTester [Source File] [Query File] [Output File]
	
If a message occurs upon launching, it is probably because I have lost my voice (ate too many snacks), then:
- Run SpaXI_Voiceless.bat instead.
	
I apologise for any inconvenience caused.
