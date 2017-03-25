/*
 * Example program for opmock unit testing framework parts
 */
#include "opmock.h"

static void test_bidule()
{
  int truc = 5;
  OP_ASSERT_EQUAL_INT(5, truc);
  OP_ASSERT_EQUAL_INT(4, truc);
}

static void test2()
{
  OP_ASSERT_EQUAL_FLOAT(1.0, 1.0);
  OP_ASSERT_EQUAL_FLOAT(1.0, 2.0);
}

static void test3()
{
  OP_ASSERT_EQUAL_CSTRING("wazoo", "wazoo");
  OP_ASSERT_EQUAL_CSTRING("wazoo", "baloo");
}

static void test4()
{
  OP_ASSERT_TRUE(1);
  OP_ASSERT_TRUE(0);
}

static void test5()
{
  OP_ASSERT_FALSE(0);
  OP_ASSERT_FALSE(1);
}

static void test6()
{
  OP_ASSERT_EQUAL_CHAR('a', 'a');
  OP_ASSERT_EQUAL_CHAR('a', 'b');
}

static void test7()
{
  OP_ASSERT_EQUAL_INT(1, 1);
}

static void test8()
{
  OP_ASSERT_EQUAL_CSTRING("toto", "toto");
}

int main (int argc, char **argv)
{
  opmock_test_reset();
  opmock_register_test(test_bidule, "test_bidule");
  opmock_register_test(test2, "test2");
  opmock_register_test(test3, "test3");
  opmock_register_test(test4, "test4");
  opmock_register_test(test5, "test5");
  opmock_register_test(test6, "test6");
  opmock_register_test(test7, "test7");
  opmock_register_test(test8, "test8");

  opmock_run_all_tests();
  return 0;
}
