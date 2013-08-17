/* OPMOCK GENERATED C++ CODE - DO NOT MODIFY */

#ifndef HEADER_STUB_HPP_
#define HEADER_STUB_HPP_

#include "header.h"

#include "opmock.h"
#define MAX_FUNC_CALL 100






class ClassNoNamespace;
namespace space1 { class Class1; }
namespace space1 { namespace space2 { class Class2; } }
namespace space3 { class Class3; }

typedef void (* OPMOCK_ClassNoNamespace_bla_CALLBACK)(int  j, int calls);
typedef void (* OPMOCK_ClassNoNamespace_bla_INST_CALLBACK)(int  j, int calls, ClassNoNamespace * ptr);
typedef int (* OPMOCK_ClassNoNamespace_imVirtual_CALLBACK)(const char *  param, int calls);
typedef int (* OPMOCK_ClassNoNamespace_imVirtual_INST_CALLBACK)(const char *  param, int calls, ClassNoNamespace * ptr);

typedef int (* OPMOCK_space1__Class1_func1_CALLBACK)(int  i, int  j, int calls);
typedef int (* OPMOCK_space1__Class1_func1_INST_CALLBACK)(int  i, int  j, int calls, space1::Class1 * ptr);
typedef int (* OPMOCK_space1__Class1_func2_CALLBACK)(char *  one, char *  two, int calls);
typedef int (* OPMOCK_space1__Class1_func2_INST_CALLBACK)(char *  one, char *  two, int calls, space1::Class1 * ptr);
typedef char (* OPMOCK_space1__Class1_func3_CALLBACK)(char * one_array[], int  another, int calls);
typedef char (* OPMOCK_space1__Class1_func3_INST_CALLBACK)(char * one_array[], int  another, int calls, space1::Class1 * ptr);

typedef void (* OPMOCK_space1__space2__Class2_func3_CALLBACK)(int calls);
typedef void (* OPMOCK_space1__space2__Class2_func3_INST_CALLBACK)(int calls, space1::space2::Class2 * ptr);
typedef char * (* OPMOCK_space1__space2__Class2_func4_CALLBACK)(double  val, int calls);
typedef char * (* OPMOCK_space1__space2__Class2_func4_INST_CALLBACK)(double  val, int calls, space1::space2::Class2 * ptr);

typedef int (* OPMOCK_space3__Class3_func5_CALLBACK)(double  machin, int  bidule, int calls);
typedef int (* OPMOCK_space3__Class3_func5_INST_CALLBACK)(double  machin, int  bidule, int calls, space3::Class3 * ptr);
typedef int (* OPMOCK_space3__Class3_shouldBePrivate_CALLBACK)(char  j, int calls);
typedef int (* OPMOCK_space3__Class3_shouldBePrivate_INST_CALLBACK)(char  j, int calls, space3::Class3 * ptr);
typedef int (* OPMOCK_space3__Class3_multiply_CALLBACK)(int  a, int  b, int calls);
typedef int (* OPMOCK_space3__Class3_multiply_INST_CALLBACK)(int  a, int  b, int calls, space3::Class3 * ptr);

class ClassNoNamespace
{
  public:
    ClassNoNamespace ();

    ~ClassNoNamespace ();

    void bla (int  j);
    virtual int imVirtual (const char *  param);

    static void bla_MockReset();
    static void imVirtual_MockReset();

    static void MockReset ();

    static void bla_MockWithCallback(OPMOCK_ClassNoNamespace_bla_CALLBACK callback);
    static void imVirtual_MockWithCallback(OPMOCK_ClassNoNamespace_imVirtual_CALLBACK callback);

    void bla_MockWithInstanceCallback(OPMOCK_ClassNoNamespace_bla_INST_CALLBACK callback);
    void imVirtual_MockWithInstanceCallback(OPMOCK_ClassNoNamespace_imVirtual_INST_CALLBACK callback);

    static int bla_VerifyMock();    static int imVirtual_VerifyMock();
    static void bla_ExpectAndReturn (int  j, OPMOCK_MATCHER match_j);
    static void imVirtual_ExpectAndReturn (const char *  param, int to_return, OPMOCK_MATCHER match_param);

    static void bla_Return ();
    static void imVirtual_Return (int to_return);

};

namespace space1
{
class Class1
{
  public:
    Class1 ();

    ~Class1 ();

    int func1 (int  i, int  j);
    int func2 (char *  one, char *  two);
    char func3 (char * one_array[], int  another);

    static void func1_MockReset();
    static void func2_MockReset();
    static void func3_MockReset();

    static void MockReset ();

    static void func1_MockWithCallback(OPMOCK_space1__Class1_func1_CALLBACK callback);
    static void func2_MockWithCallback(OPMOCK_space1__Class1_func2_CALLBACK callback);
    static void func3_MockWithCallback(OPMOCK_space1__Class1_func3_CALLBACK callback);

    void func1_MockWithInstanceCallback(OPMOCK_space1__Class1_func1_INST_CALLBACK callback);
    void func2_MockWithInstanceCallback(OPMOCK_space1__Class1_func2_INST_CALLBACK callback);
    void func3_MockWithInstanceCallback(OPMOCK_space1__Class1_func3_INST_CALLBACK callback);

    static int func1_VerifyMock();    static int func2_VerifyMock();    static int func3_VerifyMock();
    static void func1_ExpectAndReturn (int  i, int  j, int to_return, OPMOCK_MATCHER match_i, OPMOCK_MATCHER match_j);
    static void func2_ExpectAndReturn (char *  one, char *  two, int to_return, OPMOCK_MATCHER match_one, OPMOCK_MATCHER match_two);
    static void func3_ExpectAndReturn (char * one_array[], int  another, char to_return, OPMOCK_MATCHER match_one_array, OPMOCK_MATCHER match_another);

    static void func1_Return (int to_return);
    static void func2_Return (int to_return);
    static void func3_Return (char to_return);

};
}

namespace space1
{
namespace space2
{
class Class2
{
  public:
    Class2 ();

    ~Class2 ();

    void func3 ();
    char * func4 (double  val);

    static void func3_MockReset();
    static void func4_MockReset();

    static void MockReset ();

    static void func3_MockWithCallback(OPMOCK_space1__space2__Class2_func3_CALLBACK callback);
    static void func4_MockWithCallback(OPMOCK_space1__space2__Class2_func4_CALLBACK callback);

    void func3_MockWithInstanceCallback(OPMOCK_space1__space2__Class2_func3_INST_CALLBACK callback);
    void func4_MockWithInstanceCallback(OPMOCK_space1__space2__Class2_func4_INST_CALLBACK callback);

    static int func3_VerifyMock();    static int func4_VerifyMock();
    static void func3_ExpectAndReturn ();
    static void func4_ExpectAndReturn (double  val, char * to_return, OPMOCK_MATCHER match_val);

    static void func3_Return ();
    static void func4_Return (char * to_return);

};
}
}

namespace space3
{
class Class3
{
  public:
    Class3 ();

    ~Class3 ();

    int func5 (double  machin, int  bidule);
    int shouldBePrivate (char  j);
    int multiply (int  a, int  b);

    static void func5_MockReset();
    static void shouldBePrivate_MockReset();
    static void multiply_MockReset();

    static void MockReset ();

    static void func5_MockWithCallback(OPMOCK_space3__Class3_func5_CALLBACK callback);
    static void shouldBePrivate_MockWithCallback(OPMOCK_space3__Class3_shouldBePrivate_CALLBACK callback);
    static void multiply_MockWithCallback(OPMOCK_space3__Class3_multiply_CALLBACK callback);

    void func5_MockWithInstanceCallback(OPMOCK_space3__Class3_func5_INST_CALLBACK callback);
    void shouldBePrivate_MockWithInstanceCallback(OPMOCK_space3__Class3_shouldBePrivate_INST_CALLBACK callback);
    void multiply_MockWithInstanceCallback(OPMOCK_space3__Class3_multiply_INST_CALLBACK callback);

    static int func5_VerifyMock();    static int shouldBePrivate_VerifyMock();    static int multiply_VerifyMock();
    static void func5_ExpectAndReturn (double  machin, int  bidule, int to_return, OPMOCK_MATCHER match_machin, OPMOCK_MATCHER match_bidule);
    static void shouldBePrivate_ExpectAndReturn (char  j, int to_return, OPMOCK_MATCHER match_j);
    static void multiply_ExpectAndReturn (int  a, int  b, int to_return, OPMOCK_MATCHER match_a, OPMOCK_MATCHER match_b);

    static void func5_Return (int to_return);
    static void shouldBePrivate_Return (int to_return);
    static void multiply_Return (int to_return);

};
}


#endif

