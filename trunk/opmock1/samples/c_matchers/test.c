#include "test.h"
#include "code.h"
#include "dep_stub.h"
#include "opmock.h"


/*
 * This is the callback function for the first test.
 * We need it to perform a side effect on parameters.
 */
void callInOut_CALLBACK (FooStruct * foo, int calls)
{
	foo->boo = foo->boo * foo->foo * foo->multiply;//perform a side effect on in-out parameter
}

/*
 * super_function will in turn call a mocked dependency, callInOut
 * The usual way to fill in output parameters is to use a callback :
 * mocks can't perform side effects on their parameters as they don't have
 * any built-in 'intelligence' (excepted recording and checking parameters and calls)
 */
void test_super_function_with_callback()
{
	// configure the callback
	callInOut_MockWithCallback (callInOut_CALLBACK);

	float res = super_function (10, 1.5);
	OP_ASSERT_EQUAL_FLOAT(150.0, res);
}

/*
 * A custom matcher performing at the same time a side effect on the input parameter
 */
static int custom_matcher(void *val1, void *val2, const char * name, char *buffer)
{
  FooStruct *toto1 = *(FooStruct **) val1;
  FooStruct *toto2 = *(FooStruct **) val2;

	// here we check the input parameters
	// this is what a standard matcher does, but in our case could be optional,
	// because we are more interested in performing a side effect on the parameter.

  if(toto1->foo != toto2->foo) {
	snprintf(buffer, OP_MATCHER_MESSAGE_LENGTH, "parameter '%s.foo' has value '%d', was expecting '%d'",
	   name, toto2->foo, toto1->foo);
    return 1;
  }
  if(toto1->boo != toto2->boo) {
snprintf(buffer, OP_MATCHER_MESSAGE_LENGTH, "parameter '%s.boo' has value '%f', was expecting '%f'",
	   name, toto2->boo, toto1->boo);
    return 1;
  }

	if(toto1->multiply != toto2->multiply) {
snprintf(buffer, OP_MATCHER_MESSAGE_LENGTH, "parameter '%s.multiply' has value '%d', was expecting '%d'",
	   name, toto2->multiply, toto1->multiply);
    return 1;
  }

  // perform the side effect on the output parameter!
	// the "expected" parameter is always val1
	// the "actual" parameter is always val2. It's on this one we perform a side effect.
	toto2->boo = toto2->boo * toto2->foo * toto2->multiply;

  return 0;
}

void test_super_function_with_matcher()
{
	// configure the mock with a custom matcher
	// we can also check the input parameters of the mock,
	// so let's specify what's expected. This is optional, as what we really intend to
	// do is perform a side effect on a the struct.
	// we could also check input parameters in a callback but it is harder,
	// as a callback does not have a state machine like a mock has. Only the 'calls'
	// parameter can be used to adapt the callback behavior.
	FooStruct input;
	input.foo = 20;
	input.boo = 1.5;
	input.multiply = 10;

	callInOut_ExpectAndReturn (&input, custom_matcher);

	float res = super_function (20, 1.5);
	OP_ASSERT_EQUAL_FLOAT(300.0, res);
	OP_VERIFY();
}

#define MYMULT(x, y) (x)*(y)

void test_super_function_with_expanded_macro()
{
	// configure the callback
	callInOut_MockWithCallback (callInOut_CALLBACK);

	float res = super_function (10, 1.5);
	OP_ASSERT_EQUAL_FLOAT(MYMULT(15.0, 10.0), res);
}

void test_cmp_string()
{
	// that's a visual test : I want to check that the printf is correct
	// and it must fail
	const char *expected = "expected";
	const char *actual = "actual";
	OP_ASSERT_EQUAL_CSTRING(expected, actual);
}
