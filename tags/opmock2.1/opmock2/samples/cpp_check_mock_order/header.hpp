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
    int func2(int a);
    int func3(int c);
    void sideEffect(char * buffer);

  };
}

// test for cmp_ptr matcher in c++
typedef int * MyIntPtr;

namespace space2
{
  class Test2
  {
  public:
     int takeIntTypedef(MyIntPtr onePtr);
  };
}

#endif
