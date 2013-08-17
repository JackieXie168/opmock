#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <iostream>

#define MAX_FUNC_CALL 100

// A function template, outside of namespace
// with some references to spice up. That's the one we want to mock
//celle ci est supposee etre incluse
template <typename X, typename Y>
X templateFunctionNoNamespace_renamed(X &x, Y y)
{
  return x + y;
}



//template <X, Y>
//typedef X (* templateFunctionNoNamespace_CALLBACK)(X & x, Y y, int calls);
// templates of typedef are not supported by C++ :-(



// the struct to store calls to this template function
// il me faut absolument la liste des parametres,
// depuis le header...
template <typename X, typename Y>
struct templateFunctionNoNamespace_call
{
  X * x;
  Y y;
  X return_value;
  char check_params;
};

// cette structure doit forcement etre instanciee
// au moment du test. Je ne peux pas la déclarer en static
// car je ne connais pas le type associé.
template <typename X, typename Y>
struct templateFunctionNoNamespace_struct
{
  int expectedCalls;
  int actualCalls;
  char useRealImpl;
  // can't use templates with typedefs
  // so specify the callback signature directly!
  X (* callback)(X & x, Y y, int calls);
  templateFunctionNoNamespace_call<X, Y> calls[MAX_FUNC_CALL];
};


// I can't use the global struct to record parameters
// because it is not parameterized yet
// means that the function templates have to be declared in the test file itself
// after the struct is created.
/*
template <typename X, typename Y>
X templateFunctionNoNamespace(X &x, Y y)
{
  return x + y;
  }*/

#endif
