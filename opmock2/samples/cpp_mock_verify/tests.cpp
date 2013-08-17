#include "tests.hpp"
#include "header_stub.hpp"
#include "opmock.h"

void test_mock_1()
{
	// test a C++ mock with expect and return
	// this test should SUCCEED
	space1::ClassTest_Mock::func1_ExpectAndReturn(2, 3, 6, cmp_int, cmp_int);

	// exercise code
	space1::ClassTest test;
	int res = test.func1(2 ,3);

	// assertions
	OP_ASSERT_EQUAL_INT(6, res);

	// optional : check that all parameters are ok
	// and that the number of calls is ok
	OP_VERIFY();
}

void test_mock_2()
{
	// test a C++ mock with expect and return
	// this verify phase of this test should FAIL
	// (bad parameters). But the assertion should be OK
	// as the mock returns a correct result.
	space1::ClassTest_Mock::func1_ExpectAndReturn(2, 3, 6, cmp_int, cmp_int);

	// exercise code
	space1::ClassTest test;
	int res = test.func1(5 ,3);

	OP_ASSERT_EQUAL_INT(6, res);
	OP_VERIFY();
}

void test_mock_3()
{
	// this test should SUCCEED
	// the implemented function is supposed to be multiply (i,j)
	space1::ClassTest_Mock::func1_ExpectAndReturn(2, 3, 6, cmp_int, cmp_int);
	space1::ClassTest_Mock::func1_ExpectAndReturn(3, 4, 12, cmp_int, cmp_int);
	space1::ClassTest_Mock::func1_ExpectAndReturn(5, 6, 30, cmp_int, cmp_int);

	// exercise code
	space1::ClassTest test;
	int res = test.func1(2 ,3);
	OP_ASSERT_EQUAL_INT(6, res);

	res = test.func1(3 ,4);
	OP_ASSERT_EQUAL_INT(12, res);

	res = test.func1(5 ,6);
	OP_ASSERT_EQUAL_INT(30, res);

	OP_VERIFY();
}

void test_mock_4()
{
	// this test should SUCCEED
	// the implemented function is supposed to be multiply (i,j)
	// I will pass in wrong parameters but a NULL matcher
	// so this should not fail the test
	space1::ClassTest_Mock::func1_ExpectAndReturn(2, 3, 6, NULL, NULL);
	space1::ClassTest_Mock::func1_ExpectAndReturn(3, 4, 12, NULL, NULL);
	space1::ClassTest_Mock::func1_ExpectAndReturn(5, 6, 30, NULL, NULL);

	// exercise code
	space1::ClassTest test;
	int res = test.func1(21 ,14);
	OP_ASSERT_EQUAL_INT(6, res);

	res = test.func1(45 ,77);
	OP_ASSERT_EQUAL_INT(12, res);

	res = test.func1(34 ,90);
	OP_ASSERT_EQUAL_INT(30, res);

	OP_VERIFY();
}

void test_mock_5()
{
	// this test should FAIL
	// I configure no mock but then call the mocked function
	space1::ClassTest test;
	int res = test.func1(2 ,3);
	OP_ASSERT_EQUAL_INT(6, res);

	// should never go here because the first assertion fails
        // (default return value can be 0 because this is an int)
	res = test.func1(3 ,4);
	OP_ASSERT_EQUAL_INT(12, res);

	OP_VERIFY();
}

void test_mock_6()
{
	// this test should FAIL
	// The assertion is NOK, I should get a report displaying all errors till
        // the line where the assertion was triggered
        space1::ClassTest_Mock::func1_ExpectAndReturn(2, 3, 6, cmp_int, cmp_int);
	space1::ClassTest test;
	int res = test.func1(2 ,3);
	OP_ASSERT_EQUAL_INT(7, res);

	// should never go through this line
	OP_VERIFY();
}

//configure a mock, but don't call it
//this test should FAIL in the VERIFY phase
void test_mock_7()
{
	space1::ClassTest_Mock::func1_ExpectAndReturn(2, 3, 6, cmp_int, cmp_int);
	OP_VERIFY();
}
