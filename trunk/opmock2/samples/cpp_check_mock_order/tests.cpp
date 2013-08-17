#include "tests.hpp"
#include "header.hpp"
#include "header_stub.hpp"
#include "opmock.h"

/*
static int func1 (int i, int j, int calls)
{

  if((strcmp(sound, "FIZZ") == 0) 
     || (strcmp(sound, "BUZZ") == 0)
     || (strcmp(sound, "FIZZBUZZ") == 0))
    return 0;
  return 1;

return 0;
}
*/

void test_mock_1()
{
	// test a C++ mock with expect and return. I call functions in the order 1, 2, 3
	// I pass in correct parameters
	// this test should SUCCEED
	space1::ClassTest_Mock::func1_ExpectAndReturn(2, 3, 6, cmp_int, cmp_int);
	space1::ClassTest_Mock::func2_ExpectAndReturn(77, -1, cmp_int);
	space1::ClassTest_Mock::func3_ExpectAndReturn(13, 42, cmp_int);

	// exercise code
	space1::ClassTest test;
	// first call
	int res = test.func1(2 ,3);

	// assertions
	OP_ASSERT_EQUAL_INT(6, res);

	//2nd call
	res = test.func2(77);
	OP_ASSERT_EQUAL_INT(-1, res);

	//3rd call
	res = test.func3(13);
	OP_ASSERT_EQUAL_INT(42, res);

	// optional : check that all parameters are ok
	// and that the number of calls is ok
	OP_VERIFY();
}

void test_mock_2()
{
	// this is the same test than test 1,
	// with the difference that we call functions in a wrong order
	// this should be captured, so the test should FAIL
	space1::ClassTest_Mock::func1_ExpectAndReturn(2, 3, 6, cmp_int, cmp_int);
	space1::ClassTest_Mock::func2_ExpectAndReturn(77, -1, cmp_int);
	space1::ClassTest_Mock::func3_ExpectAndReturn(13, 42, cmp_int);

	space1::ClassTest test;

	int res = test.func1(2 ,3);
	OP_ASSERT_EQUAL_INT(6, res);

	// call to func3 should fail
	res = test.func3(13);
	OP_ASSERT_EQUAL_INT(42, res);

	res = test.func2(77);
	OP_ASSERT_EQUAL_INT(-1, res);

	OP_VERIFY();
}

/* we call functions in a wrong order but with correct parameters
using the macro OP_VERIFY_NO_ORDER this test should PASS */
void test_mock_3()
{
	space1::ClassTest_Mock::func1_ExpectAndReturn(2, 3, 6, cmp_int, cmp_int);
	space1::ClassTest_Mock::func2_ExpectAndReturn(77, -1, cmp_int);
	space1::ClassTest_Mock::func3_ExpectAndReturn(13, 42, cmp_int);

	space1::ClassTest test;

	int res = test.func1(2 ,3);
	OP_ASSERT_EQUAL_INT(6, res);

	// call to func3 would fail with OP_VERIFY but should be ok here
	res = test.func3(13);
	OP_ASSERT_EQUAL_INT(42, res);

	res = test.func2(77);
	OP_ASSERT_EQUAL_INT(-1, res);

	OP_VERIFY_NO_ORDER();
}

/* a test for buffer comparison
 * This test should FAIL
 */
void test_mock_4()
{
	char buffer1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	char buffer2[10] = {1, 2, 3, 4, 5, 42, 7, 8, 9, 10};

	OP_ASSERT_EQUAL_BUFFER(buffer1, buffer2, 10);
}

/* a test for buffer comparison
 * This test should PASS
 */
void test_mock_5()
{
	char buffer1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	char buffer2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	OP_ASSERT_EQUAL_BUFFER(buffer1, buffer2, 10);
}

void test_cmp_ptr_with_typedef()
{
	int val1 = 10;

    MyIntPtr ptr1 = &val1;
	space2::Test2_Mock::takeIntTypedef_ExpectAndReturn (ptr1, 2, cmp_ptr);

    // this test should be a success : both pointer values are equal
	space2::Test2 oneclass;
    int res = oneclass.takeIntTypedef (ptr1);
    OP_ASSERT_EQUAL_INT(2, res);

	OP_VERIFY();
}

// this test should be a failure : we're going to pass 2 different pointers
void test_cmp_ptr_with_typedef_fail()
{
	int val1 = 10;
    int val2 = 20;

    MyIntPtr ptr1 = &val1;
    MyIntPtr ptr2 = &val2;
	space2::Test2_Mock::takeIntTypedef_ExpectAndReturn (ptr1, 2, cmp_ptr);

    space2::Test2 oneclass;
    int res = oneclass.takeIntTypedef (ptr2);
    OP_ASSERT_EQUAL_INT(2, res);

	OP_VERIFY();
}
