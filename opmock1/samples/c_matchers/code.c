#include "code.h"
#include "dep.h"

float super_function (int arg1, float arg2)
{
	FooStruct foos;
	foos.foo = arg1;
  	foos.boo = arg2;
	foos.multiply = 10;

	callInOut(&foos);

	return foos.boo;
}
