#include <stdio.h>

#include "opmock.h"
#include "tests.hpp"

int main(int argc, char *argv[])
{
	opmock_test_suite_reset();
	opmock_register_test(test_mock_1, "test_mock_1");
	opmock_register_test(test_mock_2, "test_mock_2");
	opmock_register_test(test_mock_3, "test_mock_3");
	opmock_register_test(test_mock_4, "test_mock_4");
	opmock_register_test(test_mock_5, "test_mock_5");
    opmock_register_test(test_cmp_ptr_with_typedef, "test_cmp_ptr_with_typedef");
    opmock_register_test(test_cmp_ptr_with_typedef_fail, "test_cmp_ptr_with_typedef_fail");
  
  opmock_test_suite_run();

  return 0;
}
