#include <stdio.h>
#include <iostream>
#include "opmock.h"

#include "header_stub.hpp"

class ToTest
{
private:
  space3::Class3 oneClass3;
public:
  int doSomething(int a);
};

int ToTest::doSomething(int a)
{
  int result = oneClass3.multiply(a, a);
  return result;
}

static int class3_callback (int  a, int  b, int calls, space3::Class3 * ptr)
{
  // perform a side effect on the class itself
  std::cout << "Calling class3_callback a=" << a << " b=" << b << " calls=" << calls << " value=" << ptr->attribute1 << std::endl;
  ptr->attribute1 = 42;
  return 1234567;
}

int main(int argc, char *argv[])
{
  // initialize the mock class
  // this works for all instances, even instances I've not created 
  space3::Class3_Mock::multiply_ExpectAndReturn (4, 4, 16, cmp_int, cmp_int);
  
  ToTest class1;
  int res = class1.doSomething(4);
  
  if(res != 16) printf("resultat en echec\n");

  space3::Class3_Mock::multiply_ExpectAndReturn (4, 4, 42, cmp_int, cmp_int);
  res = class1.doSomething(4);

  printf("resultat 2 %d\n", res);
  
  // now use an instance callback - meaning that I need to get
  // a pointer on the class I want to mock
  space3::Class3 class3;
  class3.attribute1 = -777;

  space3::Class3_Mock::multiply_MockWithInstanceCallback(class3_callback);
  int res2 = class3.multiply(2, 24);

  std::cout << "Result instance mock : " << res2 << std::endl;
  std::cout << "attribute value in class : " << class3.attribute1 << std::endl;

  return 0;
}
