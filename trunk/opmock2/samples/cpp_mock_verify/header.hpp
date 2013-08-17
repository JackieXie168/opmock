#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>

typedef unsigned int Int32;


namespace space1
{
  class ClassTest
  {
  public:
    int func1(int i, int j);
    int ldpNHResRoute_Walk(double vrId,
			   char prefixType,
			   void **ppNHResRoute,
			   Int32 ** (*pWalkFn)(char * bla,
					       void * boo,
					       void * foo),
			   void *pArg1,
			   void *pArg2);

    // a static operation. Should not be mocked with instance operations
    static int my_static (float my_float);
  };
}

// a simple C like function with references
int & returnReferenceAsC(float & parm1);

#endif
