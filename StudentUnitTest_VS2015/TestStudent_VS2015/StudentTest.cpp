#include "stdafx.h"
#include "CppUnitTest.h"
#include "Student.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestStudent_VS2015
{		
	TEST_CLASS(TestStudent)
	{
	public:
		
		TEST_METHOD(testConstructor)
		{
			Student stu("Tan Meng Chee", "94-1111B-13");

			// check that the object is constructed correctly - Note 6
			std::string student_name = stu.getStuName();
			Assert::AreEqual (student_name, (std::string)"Tan Meng Chee");

			std::string student_number = stu.getStuNumber();
			Assert::AreEqual (student_number, (std::string)"94-1111B-13");

			return;
		}

		TEST_METHOD(testAssignAndRetrieveGrades)
		{
			// create a student
			Student stu("Jimmy", "946302B");

			// assign a few grades to this student
			stu.assignGrade("cs2102", 60);
			stu.assignGrade("cs2103", 70);
			stu.assignGrade("cs3215", 80);

			// verify that the assignment is correct - Note 7
			Assert::AreEqual(60, stu.getGrade("cs2102"));
			Assert::AreEqual(70, stu.getGrade("cs2103"));

			// attempt to retrieve a course that does not exist
			Assert::AreEqual(-1, stu.getGrade("cs21002"));

			return;
		}

	};
}