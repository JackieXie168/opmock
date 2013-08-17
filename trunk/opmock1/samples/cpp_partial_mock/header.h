#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>

// one template class used for simple template parameters
template <typename T>
class Foo {
public:
  T i;
};

typedef int Int32;

struct Youpi
{
  int blo;
};

struct Bouba
{
  double foo;
};

namespace space1
{
  class Class1
  {
  public:
	// These 2 constructors should be skipped when generating code
	Class1(int i);
	Class1(double j);

    int func1(int i, int j);

    // an overloaded function. Defines 2 times the same symbol!
    int func1(float a, char *b);
    
    // a very complex signature : passing a pointer to function
    // as a parameter. Note that I've given name to the parameters,
    // but the original code had a mix of anonymous parameters (K&R style) and names parameters
    int ldpNHResRoute_Walk(double vrId,
			   char prefixType,
			   void **ppNHResRoute,
			   Int32 ** (*pWalkFn)(char * bla,
					       void * boo,
					       void * foo),
			   void *pArg1,
			   void *pArg2);
    
    struct Youpi *funcFunc(void (*toto)(int bla));
    void *funcFunc2(struct Bouba * (*titi)(int blu));
    
    // a signature with a template parameter
    //int ** funcWithTemplateParam (vector < vector <int *> > param1, stuff<foo> param2);

    // a signature taking references
    char takesReferences(int & bla, float & foo);

    // a signature returning a reference
    int & returnReference(float bidule);

    // a signature taking an array parameter
    void withArray(char bla []);

    // a signature taking a template parameter
    // as a reference. Passing directly the object is possible
    // but then I can't compare it as I don't have a != overload
    int functionWithTParam(int j, Foo<float> & foo);
  };
}

// a simple C like function with references
int & returnReferenceAsC(float & parm1);

typedef char Boolean;

namespace OTDRProxy
{
  typedef struct {
    int bla;
  } T_ConfigLine;
  
  typedef struct {
    char *foo;
  } InvocationAsync;

  class Configuration_ske {
  public:
    int boo;
  };
  
  class OTDRConfigurationItf : public virtual OTDRProxy::Configuration_ske 
  {
  public:
    
    OTDRConfigurationItf () {}
    ~OTDRConfigurationItf () {}
    
    // Operation ConfigLine
    virtual void ConfigLine(const OTDRProxy::T_ConfigLine& configLine,
  			    Boolean& result,
  			    OTDRProxy::InvocationAsync& invocation);  
  protected:
    
  private:
    
    // copy constructor
    OTDRConfigurationItf (OTDRConfigurationItf const &other);
    // assignment operator
    OTDRConfigurationItf& operator=(OTDRConfigurationItf const &other);
  };
}

// A function template, outside of namespace
// with some references to spice up
template <typename X, typename Y>
X templateFunctionNoNamespace_renamed(X &x, Y y)
{
  return x + y;
}

// exactly the same template function, but the mocked version this time
// I shall be able to behave exactly the original one, and even
// call the original version if required.
// This is an exercise to write the generated code.
template <typename X, typename Y>
X templateFunctionNoNamespace (X &x, Y y)
{
  return x + y;
}

// A function template, inside nested namespace
namespace ftemp1
{
  namespace ftemp2
  {
    template <typename U, typename V>
    U templateFunctionWithNamespace(U &x, V y)
    {
      return x * y;
    }
  }
}

// A simple class template
namespace template1
{
template <typename T, typename V>
class TemplateB {
 public:
  void yahoo(T & param, V *param2) {
    printf("Hello World\n");
  }
};
}

// a somewhat complex template template class
/*
template <typename T, typename U=float, template <typename X=int, typename Y=int> class TemplateB>
  class TemplateA {
 private:
 U parameterU;
 T * parameterT;
 TemplateB * <X, Y> parameterV;
 public:
 T & operation1(T & param1, U * param2, TemplateB * <X, Y> param3) {
   parameterU = *param2;
   parameterT = param1;// must have a copy constructor
   parameterV = param3;
   return param1;
 }
};
*/




#endif
