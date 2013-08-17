#include "fizzbuzz.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char * fizzbuzz (int i)
{
  char *result = (char *) calloc(1, 20);
  
  if (!(i % 3)) strcpy(result, "FIZZ");
  if (!(i % 5)) strcat(result, "BUZZ");
  
  if(!strlen(result)) sprintf(result, "%d", i);
  return result;
}

