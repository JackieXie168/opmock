#include "fizzbuzz_test.h"
#include "fizzbuzz.h"
#include "opmock.h"
#include <stdlib.h>

void test_fizzbuzz_with_3()
{ 
  char *res = fizzbuzz(3);
  OP_ASSERT_EQUAL_CSTRING("FIZZ", res);
  free(res);
}

void test_fizzbuzz_with_5()
{
  char *res = fizzbuzz(5);
  OP_ASSERT_EQUAL_CSTRING("BUZZ", res);
  free(res);
}

void test_fizzbuzz_with_15()
{
  char *res = fizzbuzz(15);
  OP_ASSERT_EQUAL_CSTRING("FIZZBUZZ", res);
  free(res);
}

void test_fizzbuzz_many_3()
{
  int i;
  for(i = 1; i < 1000; i++) {
    if((i % 3 == 0) && ((i % 5) != 0)) {   
      char *res = fizzbuzz(i);
      OP_ASSERT_EQUAL_CSTRING("FIZZ", res);
      free(res);
    }
  }
}

void test_fizzbuzz_many_5()
{
  int i;
  for(i = 1; i < 1000; i++) {
    if((i % 3 != 0) && ((i % 5) == 0)) {
      char *res = fizzbuzz(i);
      OP_ASSERT_EQUAL_CSTRING("BUZZ", res);
      free(res);
    }
  }
}

void test_fizzbuzz_many_3_and_5()
{
  int i;
  for(i = 1; i < 1000; i++) {
    if((i % 3 == 0) && ((i % 5) == 0)) {      
      char *res = fizzbuzz(i);
      OP_ASSERT_EQUAL_CSTRING("FIZZBUZZ", res);
      free(res);
    }
  }
}
