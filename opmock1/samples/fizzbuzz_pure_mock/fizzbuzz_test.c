#include "fizzbuzz_test.h"
#include "fizzbuzz.h"
#include "sound_stub.h"
#include "opmock.h"

#include <stdlib.h>
#include <string.h>

static int test_fizzbuzz_with_15_callback (char *  sound, int calls)
{
  if((strcmp(sound, "FIZZ") == 0) 
     || (strcmp(sound, "BUZZ") == 0)
     || (strcmp(sound, "FIZZBUZZ") == 0))
    return 0;
  return 1;
}

void test_fizzbuzz_with_3()
{ 
  do_sound_ExpectAndReturn ("FIZZ", 0, cmp_cstr);
  char *res = fizzbuzz(3);
  OP_ASSERT_EQUAL_CSTRING("FIZZ", res);
  free(res);

  OP_VERIFY();
}

void test_fizzbuzz_with_5()
{
  do_sound_ExpectAndReturn ("", 0, NULL);
  char *res = fizzbuzz(5);
  OP_ASSERT_EQUAL_CSTRING("BUZZ", res);
  free(res);

  OP_VERIFY();
}

void test_fizzbuzz_with_15()
{
  do_sound_MockWithCallback (test_fizzbuzz_with_15_callback);
  char *res = fizzbuzz(15);
  OP_ASSERT_EQUAL_CSTRING("FIZZBUZZ", res);
  free(res);

  OP_VERIFY();
}

void test_fizzbuzz_many_3()
{
  int many_3_callback (char *  sound, int calls) { return 0; }
  do_sound_MockWithCallback (many_3_callback);
  
  int i;
  for(i = 1; i < 1000; i++) {
    if((i % 3 == 0) && ((i % 5) != 0)) {   
      char *res = fizzbuzz(i);
      OP_ASSERT_EQUAL_CSTRING("FIZZ", res);
      free(res);
    }
  }

  OP_VERIFY();
}

void test_fizzbuzz_many_5()
{
  int many_5_callback (char *  sound, int calls) { return 0; }
  do_sound_MockWithCallback (many_5_callback);

  int i;
  for(i = 1; i < 1000; i++) {
    if((i % 3 != 0) && ((i % 5) == 0)) {
      char *res = fizzbuzz(i);
      OP_ASSERT_EQUAL_CSTRING("BUZZ", res);
      free(res);
    }
  }

  OP_VERIFY();
}

void test_fizzbuzz_many_3_and_5()
{
  int i;
  for(i = 1; i < 1000; i++) {
    if((i % 3 == 0) && ((i % 5) == 0)) { 
      do_sound_ExpectAndReturn ("", 0, NULL);
      char *res = fizzbuzz(i);
      OP_ASSERT_EQUAL_CSTRING("FIZZBUZZ", res);
      free(res);
    }
  }

  OP_VERIFY();
}

//TODO add negative tests
//with non mutliple of 3 for example
