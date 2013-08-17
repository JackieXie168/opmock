#include <stdio.h>

#include "opmock.h"
#include "fizzbuzz_test.h"

int main(int argc, char *argv[])
{
  opmock_test_suite_reset();
  opmock_register_test(test_push_pop_stack, "test_push_pop_stack");
  opmock_register_test(test_push_pop_stack2, "test_push_pop_stack2");
  opmock_register_test(test_push_pop_stack3, "test_push_pop_stack3");
  opmock_register_test(test_push_pop_stack4, "test_push_pop_stack4");
  opmock_register_test(test_verify, "test_verify");
  opmock_register_test(test_verify_with_matcher_cstr, "test_verify_with_matcher_cstr");
  opmock_register_test(test_verify_with_matcher_int, "test_verify_with_matcher_int");
  opmock_register_test(test_verify_with_matcher_float, "test_verify_with_matcher_float");
  opmock_register_test(test_verify_with_matcher_custom, "test_verify_with_matcher_custom");
  opmock_register_test(test_cmp_ptr_with_typedef, "test_cmp_ptr_with_typedef");
  opmock_register_test(test_cmp_ptr_with_typedef_fail, "test_cmp_ptr_with_typedef_fail");
  opmock_test_suite_run();

  return 0;
}
