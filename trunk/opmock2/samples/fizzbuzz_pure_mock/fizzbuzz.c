#include "fizzbuzz.h"
#include "sound.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char * fizzbuzz (int i)
{
  char *result = (char *) calloc(1, 20);
  
  if (!(i % 3)) strcpy(result, "FIZZ");
  if (!(i % 5)) strcat(result, "BUZZ");
  
  if(!strlen(result)) sprintf(result, "%d", i);

  int res = do_sound(result); 
  if(res != 0) { 
    sprintf(result, "ERROR"); 
  } 
  return result;
}

