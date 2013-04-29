#include <stdio.h>
#include <iostream>
#include "opmock.h"

#include "header_stub.hpp"


int main(int argc, char *argv[])
{
	Son son;
	Son_Mock::doSomething_ExpectAndReturn(123);
	int res = son.doSomething();	
 	return 0;
}
