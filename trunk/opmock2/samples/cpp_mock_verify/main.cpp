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
  opmock_register_test(test_mock_6, "test_mock_6");
  opmock_register_test(test_mock_7, "test_mock_7");
  opmock_test_suite_run();

  return 0;
}
