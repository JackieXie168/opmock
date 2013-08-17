#include <stdio.h>
#include "header.hpp"




int main(int argc, char *argv[])
{
  
  opmock_Mother<int> mmother;
  mmother.method1(1);
  mmother.method2(2);

  Mother<char *> mother;
  mother.method1((char * )"bla");
  mother.method2((char * )"blu");

  Mother<int> mother2;
  mother2.template_callback(5, 6);


  return 0;
}
