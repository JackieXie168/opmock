#include "fizzbuzz_test.h"
#include "fizzbuzz.h"
#include "sound_stub.h"
#include "opmock.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Captures problem with warning about unexpected call
 */
void test_push_pop_stack()
{
  do_sound_ExpectAndReturn (NULL, 0, NULL);
  char *res = fizzbuzz(3);
  free(res);
  OP_VERIFY();
}

void test_push_pop_stack2()
{
  do_sound_ExpectAndReturn ("", 0, NULL);
  char *res = fizzbuzz(3);
  free(res);
  OP_VERIFY();
}

void test_push_pop_stack3()
{
  // now try to call 2 times but record behavior for 3 times
  // this test should FAIL
  do_sound_ExpectAndReturn (NULL, 0, NULL);
  do_sound_ExpectAndReturn (NULL, 1, NULL);
  do_sound_ExpectAndReturn (NULL, 2, NULL);
  char *res = fizzbuzz(3);
  free(res);
  res = fizzbuzz(3);
  free(res);
  OP_VERIFY();
}

void test_push_pop_stack4()
{
  // same thing for record
  // this test should FAIL
  do_sound_ExpectAndReturn ("", 0, NULL);
  do_sound_ExpectAndReturn ("", 1, NULL);
  do_sound_ExpectAndReturn ("", 2, NULL);
  char *res = fizzbuzz(3);
  free(res);
  res = fizzbuzz(3);
  free(res);
  OP_VERIFY();
}

void test_verify()
{
  do_sound_ExpectAndReturn ("", 0, NULL);
  do_sound_ExpectAndReturn ("", 1, NULL);
  do_sound_ExpectAndReturn ("", 2, NULL);
  char *res = fizzbuzz(3);
  free(res);
  res = fizzbuzz(3);
  free(res);
  OP_VERIFY();
}

void test_verify_with_matcher_cstr()
{
  do_sound_ExpectAndReturn ("Hello World", 0, cmp_cstr);
  int res = do_sound("Hello Kitty");// should complain
  OP_ASSERT_EQUAL_INT(0, res);

  do_sound_ExpectAndReturn ("Hello World", 0, cmp_cstr);
  res = do_sound("Hello World");// should NOT complain
  OP_ASSERT_EQUAL_INT(0, res);

  // should fail the test
  OP_VERIFY();
}

void test_verify_with_matcher_int()
{
  functionWithConstParameters_ExpectAndReturn (1, 0.5, "Youpi", -1, cmp_int, NULL, NULL);
  int param1 = 1;
  int res = functionWithConstParameters(param1, 0.5, "Youpi");
  OP_ASSERT_EQUAL_INT(-1, res);
  OP_VERIFY();// should not fail the test
}

void test_verify_with_matcher_float()
{
  functionWithConstParameters_ExpectAndReturn (1, 0.5, "Youpi", -2, NULL, 
					       cmp_float, NULL);
  int res = functionWithConstParameters(1, 0.5, "Youpi");
  OP_ASSERT_EQUAL_INT(-2, res);
  OP_VERIFY();// should not fail the test
}

/*
 * custom matcher for structure.
 */
static int compare_toto_value(void *val1, void *val2, const char * name, char *buffer)
{
  Toto *toto1 = (Toto *) val1;
  Toto *toto2 = (Toto *) val2;
  if(toto1->foo != toto2->foo) {
	snprintf(buffer, OP_MATCHER_MESSAGE_LENGTH, "parameter '%s.foo' has value '%d', was expecting '%d'",
	   name, toto2->foo, toto1->foo);
    return 1;
  }
  if(toto1->boo != toto2->boo) {
snprintf(buffer, OP_MATCHER_MESSAGE_LENGTH, "parameter '%s.boo' has value '%f', was expecting '%f'",
	   name, toto2->boo, toto1->boo);
    return 1;
  }
  return 0;
}

void test_verify_with_matcher_custom()
{
  Toto my_toto;
  my_toto.foo = 777;
  my_toto.boo = 3.5;

  // pass by value : copy the struct
  functionTotoValue_ExpectAndReturn (my_toto, 0, compare_toto_value);

  Toto toto2;
  toto2.foo = 777;
  toto2.boo = 3.5;
  int res = functionTotoValue(toto2);
  OP_ASSERT_EQUAL_INT(0, res);

  // now try a test where I pass in a non equivalent struct
  functionTotoValue_ExpectAndReturn (my_toto, 0, compare_toto_value);

  toto2.foo = 1234;
  toto2.boo = 3.5;
  res = functionTotoValue(toto2);
  OP_ASSERT_EQUAL_INT(0, res);

  OP_VERIFY();// should fail the test if not failed at the assertion
}

void test_cmp_ptr_with_typedef()
{
	int val1 = 10;

    MyIntPtr ptr1 = &val1;
	takeIntTypedef_ExpectAndReturn (ptr1, 2, cmp_ptr);

    // this test should be a success : both pointer values are equal
    int res = takeIntTypedef (ptr1);
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
	takeIntTypedef_ExpectAndReturn (ptr1, 2, cmp_ptr);

    int res = takeIntTypedef (ptr2);
    OP_ASSERT_EQUAL_INT(2, res);

	OP_VERIFY();
}
