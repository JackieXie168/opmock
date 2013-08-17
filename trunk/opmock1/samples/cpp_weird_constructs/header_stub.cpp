/* OPMOCK GENERATED C++ CODE - DO NOT MODIFY */

#include <stdio.h>

#include "header_stub.hpp"

typedef struct
{
    int  j;
    OPMOCK_MATCHER match_j;
    char check_params;
} ClassNoNamespace_bla_call;

typedef struct
{
    int expectedCalls;
    int actualCalls;
    OPMOCK_ClassNoNamespace_bla_CALLBACK callback;
    OPMOCK_ClassNoNamespace_bla_INST_CALLBACK callbackInst;
    ClassNoNamespace_bla_call calls[MAX_FUNC_CALL];
} ClassNoNamespace_bla_struct;

static ClassNoNamespace_bla_struct ClassNoNamespace_bla_struct_inst;

typedef struct
{
    char *  param;
    OPMOCK_MATCHER match_param;
    int return_value;
    char check_params;
} ClassNoNamespace_imVirtual_call;

typedef struct
{
    int expectedCalls;
    int actualCalls;
    OPMOCK_ClassNoNamespace_imVirtual_CALLBACK callback;
    OPMOCK_ClassNoNamespace_imVirtual_INST_CALLBACK callbackInst;
    ClassNoNamespace_imVirtual_call calls[MAX_FUNC_CALL];
} ClassNoNamespace_imVirtual_struct;

static ClassNoNamespace_imVirtual_struct ClassNoNamespace_imVirtual_struct_inst;

typedef struct
{
    int  i;
    int  j;
    OPMOCK_MATCHER match_i;
    OPMOCK_MATCHER match_j;
    int return_value;
    char check_params;
} space1__Class1_func1_call;

typedef struct
{
    int expectedCalls;
    int actualCalls;
    OPMOCK_space1__Class1_func1_CALLBACK callback;
    OPMOCK_space1__Class1_func1_INST_CALLBACK callbackInst;
    space1__Class1_func1_call calls[MAX_FUNC_CALL];
} space1__Class1_func1_struct;

static space1__Class1_func1_struct space1__Class1_func1_struct_inst;

typedef struct
{
    char *  one;
    char *  two;
    OPMOCK_MATCHER match_one;
    OPMOCK_MATCHER match_two;
    int return_value;
    char check_params;
} space1__Class1_func2_call;

typedef struct
{
    int expectedCalls;
    int actualCalls;
    OPMOCK_space1__Class1_func2_CALLBACK callback;
    OPMOCK_space1__Class1_func2_INST_CALLBACK callbackInst;
    space1__Class1_func2_call calls[MAX_FUNC_CALL];
} space1__Class1_func2_struct;

static space1__Class1_func2_struct space1__Class1_func2_struct_inst;

typedef struct
{
    void * one_array;
    int  another;
    OPMOCK_MATCHER match_one_array;
    OPMOCK_MATCHER match_another;
    char return_value;
    char check_params;
} space1__Class1_func3_call;

typedef struct
{
    int expectedCalls;
    int actualCalls;
    OPMOCK_space1__Class1_func3_CALLBACK callback;
    OPMOCK_space1__Class1_func3_INST_CALLBACK callbackInst;
    space1__Class1_func3_call calls[MAX_FUNC_CALL];
} space1__Class1_func3_struct;

static space1__Class1_func3_struct space1__Class1_func3_struct_inst;

typedef struct
{
    char check_params;
} space1__space2__Class2_func3_call;

typedef struct
{
    int expectedCalls;
    int actualCalls;
    OPMOCK_space1__space2__Class2_func3_CALLBACK callback;
    OPMOCK_space1__space2__Class2_func3_INST_CALLBACK callbackInst;
    space1__space2__Class2_func3_call calls[MAX_FUNC_CALL];
} space1__space2__Class2_func3_struct;

static space1__space2__Class2_func3_struct space1__space2__Class2_func3_struct_inst;

typedef struct
{
    double  val;
    OPMOCK_MATCHER match_val;
    char * return_value;
    char check_params;
} space1__space2__Class2_func4_call;

typedef struct
{
    int expectedCalls;
    int actualCalls;
    OPMOCK_space1__space2__Class2_func4_CALLBACK callback;
    OPMOCK_space1__space2__Class2_func4_INST_CALLBACK callbackInst;
    space1__space2__Class2_func4_call calls[MAX_FUNC_CALL];
} space1__space2__Class2_func4_struct;

static space1__space2__Class2_func4_struct space1__space2__Class2_func4_struct_inst;

typedef struct
{
    double  machin;
    int  bidule;
    OPMOCK_MATCHER match_machin;
    OPMOCK_MATCHER match_bidule;
    int return_value;
    char check_params;
} space3__Class3_func5_call;

typedef struct
{
    int expectedCalls;
    int actualCalls;
    OPMOCK_space3__Class3_func5_CALLBACK callback;
    OPMOCK_space3__Class3_func5_INST_CALLBACK callbackInst;
    space3__Class3_func5_call calls[MAX_FUNC_CALL];
} space3__Class3_func5_struct;

static space3__Class3_func5_struct space3__Class3_func5_struct_inst;

typedef struct
{
    char  j;
    OPMOCK_MATCHER match_j;
    int return_value;
    char check_params;
} space3__Class3_shouldBePrivate_call;

typedef struct
{
    int expectedCalls;
    int actualCalls;
    OPMOCK_space3__Class3_shouldBePrivate_CALLBACK callback;
    OPMOCK_space3__Class3_shouldBePrivate_INST_CALLBACK callbackInst;
    space3__Class3_shouldBePrivate_call calls[MAX_FUNC_CALL];
} space3__Class3_shouldBePrivate_struct;

static space3__Class3_shouldBePrivate_struct space3__Class3_shouldBePrivate_struct_inst;

typedef struct
{
    int  a;
    int  b;
    OPMOCK_MATCHER match_a;
    OPMOCK_MATCHER match_b;
    int return_value;
    char check_params;
} space3__Class3_multiply_call;

typedef struct
{
    int expectedCalls;
    int actualCalls;
    OPMOCK_space3__Class3_multiply_CALLBACK callback;
    OPMOCK_space3__Class3_multiply_INST_CALLBACK callbackInst;
    space3__Class3_multiply_call calls[MAX_FUNC_CALL];
} space3__Class3_multiply_struct;

static space3__Class3_multiply_struct space3__Class3_multiply_struct_inst;


ClassNoNamespace::ClassNoNamespace ()
{
}

ClassNoNamespace::~ClassNoNamespace ()
{
}

void ClassNoNamespace::bla (int  j)
{
    int opmock_i;
    if (ClassNoNamespace_bla_struct_inst.callback != NULL)
    {
        ClassNoNamespace_bla_struct_inst.actualCalls++;
        ClassNoNamespace_bla_struct_inst.callback (j, ClassNoNamespace_bla_struct_inst.actualCalls);
        return;
    }

    else
    if (ClassNoNamespace_bla_struct_inst.callbackInst != NULL)
    {
        ClassNoNamespace_bla_struct_inst.actualCalls++;
        ClassNoNamespace_bla_struct_inst.callbackInst (j, ClassNoNamespace_bla_struct_inst.actualCalls, this);
        return;
    }

    if (ClassNoNamespace_bla_struct_inst.expectedCalls == 0)
    {
        printf ("WARNING : unexpected call of ClassNoNamespace::bla, returning random value.\n");
        return;
    }

    ClassNoNamespace_bla_struct_inst.actualCalls++;

    if (ClassNoNamespace_bla_struct_inst.calls[0].check_params == 1)
    {
        if (ClassNoNamespace_bla_struct_inst.calls[0].match_j) {
            void * val1 = (void *) &ClassNoNamespace_bla_struct_inst.calls[0].j;
            void * val2 = (void *) &j;
            int match_result = ClassNoNamespace_bla_struct_inst.calls[0].match_j(val1, val2, "j");
            if(match_result) {
                printf("    when calling 'ClassNoNamespace::bla' (call %d)\n", ClassNoNamespace_bla_struct_inst.actualCalls);
            }
        }
    }

    for(opmock_i = 1; opmock_i < ClassNoNamespace_bla_struct_inst.expectedCalls; opmock_i++)
    {
        ClassNoNamespace_bla_struct_inst.calls[opmock_i - 1] = ClassNoNamespace_bla_struct_inst.calls[opmock_i];
    }

    ClassNoNamespace_bla_struct_inst.expectedCalls--;
}

int ClassNoNamespace::imVirtual (const char *  param)
{
    int opmock_i;
    int default_res = ClassNoNamespace_imVirtual_struct_inst.calls[0].return_value;

    if (ClassNoNamespace_imVirtual_struct_inst.callback != NULL)
    {
        ClassNoNamespace_imVirtual_struct_inst.actualCalls++;
        return ClassNoNamespace_imVirtual_struct_inst.callback (param, ClassNoNamespace_imVirtual_struct_inst.actualCalls);
    }

    else
    if (ClassNoNamespace_imVirtual_struct_inst.callbackInst != NULL)
    {
        ClassNoNamespace_imVirtual_struct_inst.actualCalls++;
        return ClassNoNamespace_imVirtual_struct_inst.callbackInst (param, ClassNoNamespace_imVirtual_struct_inst.actualCalls, this);
    }

    if (ClassNoNamespace_imVirtual_struct_inst.expectedCalls == 0)
    {
        printf ("WARNING : unexpected call of ClassNoNamespace::imVirtual, returning random value.\n");
        return default_res;
    }

    ClassNoNamespace_imVirtual_struct_inst.actualCalls++;

    if (ClassNoNamespace_imVirtual_struct_inst.calls[0].check_params == 1)
    {
        if (ClassNoNamespace_imVirtual_struct_inst.calls[0].match_param) {
            void * val1 = (void *) ClassNoNamespace_imVirtual_struct_inst.calls[0].param;
            void * val2 = (void *) param;
            int match_result = ClassNoNamespace_imVirtual_struct_inst.calls[0].match_param(val1, val2, "param");
            if(match_result) {
                printf("    when calling 'ClassNoNamespace::imVirtual' (call %d)\n", ClassNoNamespace_imVirtual_struct_inst.actualCalls);
            }
        }
    }

    for(opmock_i = 1; opmock_i < ClassNoNamespace_imVirtual_struct_inst.expectedCalls; opmock_i++)
    {
        ClassNoNamespace_imVirtual_struct_inst.calls[opmock_i - 1] = ClassNoNamespace_imVirtual_struct_inst.calls[opmock_i];
    }

    ClassNoNamespace_imVirtual_struct_inst.expectedCalls--;
    return default_res;
}

void ClassNoNamespace::bla_MockReset ()
{
    ClassNoNamespace_bla_struct_inst.expectedCalls = 0;
    ClassNoNamespace_bla_struct_inst.actualCalls = 0;
    ClassNoNamespace_bla_struct_inst.callback = NULL;
    ClassNoNamespace_bla_struct_inst.callbackInst = NULL;
}

void ClassNoNamespace::imVirtual_MockReset ()
{
    ClassNoNamespace_imVirtual_struct_inst.expectedCalls = 0;
    ClassNoNamespace_imVirtual_struct_inst.actualCalls = 0;
    ClassNoNamespace_imVirtual_struct_inst.callback = NULL;
    ClassNoNamespace_imVirtual_struct_inst.callbackInst = NULL;
}

void ClassNoNamespace::MockReset ()
{
    ClassNoNamespace::bla_MockReset ();
    ClassNoNamespace::imVirtual_MockReset ();
}

void ClassNoNamespace::bla_MockWithCallback(OPMOCK_ClassNoNamespace_bla_CALLBACK callback)
{
    ClassNoNamespace_bla_struct_inst.callback = callback;
    ClassNoNamespace_bla_struct_inst.callbackInst = NULL;
    ClassNoNamespace_bla_struct_inst.expectedCalls = 0;
    ClassNoNamespace_bla_struct_inst.actualCalls = 0;
}

void ClassNoNamespace::imVirtual_MockWithCallback(OPMOCK_ClassNoNamespace_imVirtual_CALLBACK callback)
{
    ClassNoNamespace_imVirtual_struct_inst.callback = callback;
    ClassNoNamespace_imVirtual_struct_inst.callbackInst = NULL;
    ClassNoNamespace_imVirtual_struct_inst.expectedCalls = 0;
    ClassNoNamespace_imVirtual_struct_inst.actualCalls = 0;
}

void ClassNoNamespace::bla_MockWithInstanceCallback(OPMOCK_ClassNoNamespace_bla_INST_CALLBACK callback)
{
    ClassNoNamespace_bla_struct_inst.callbackInst = callback;
    ClassNoNamespace_bla_struct_inst.callback = NULL;
    ClassNoNamespace_bla_struct_inst.expectedCalls = 0;
    ClassNoNamespace_bla_struct_inst.actualCalls = 0;
}

void ClassNoNamespace::imVirtual_MockWithInstanceCallback(OPMOCK_ClassNoNamespace_imVirtual_INST_CALLBACK callback)
{
    ClassNoNamespace_imVirtual_struct_inst.callbackInst = callback;
    ClassNoNamespace_imVirtual_struct_inst.callback = NULL;
    ClassNoNamespace_imVirtual_struct_inst.expectedCalls = 0;
    ClassNoNamespace_imVirtual_struct_inst.actualCalls = 0;
}

int ClassNoNamespace::bla_VerifyMock()
{
    int result = 1;
    if (ClassNoNamespace_bla_struct_inst.expectedCalls != 0)
    {
        printf("Assertion failed for function `ClassNoNamespace::bla' : bad number of calls (got %d)\n", ClassNoNamespace_bla_struct_inst.actualCalls);
        result = 0;
    }
    return result;
}

int ClassNoNamespace::imVirtual_VerifyMock()
{
    int result = 1;
    if (ClassNoNamespace_imVirtual_struct_inst.expectedCalls != 0)
    {
        printf("Assertion failed for function `ClassNoNamespace::imVirtual' : bad number of calls (got %d)\n", ClassNoNamespace_imVirtual_struct_inst.actualCalls);
        result = 0;
    }
    return result;
}

void ClassNoNamespace::bla_ExpectAndReturn (int  j, OPMOCK_MATCHER match_j)
{
    if(ClassNoNamespace_bla_struct_inst.callback != NULL)
    {
        ClassNoNamespace::bla_MockReset ();
    }

    if(ClassNoNamespace_bla_struct_inst.callbackInst != NULL)
    {
        ClassNoNamespace::bla_MockReset ();
    }

    if(ClassNoNamespace_bla_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting ClassNoNamespace::bla_ExpectAndReturn, call stack overload.\n");
        return;
    }

    ClassNoNamespace_bla_struct_inst.calls[ClassNoNamespace_bla_struct_inst.expectedCalls].j = j;
    ClassNoNamespace_bla_struct_inst.calls[ClassNoNamespace_bla_struct_inst.expectedCalls].match_j = match_j;
    ClassNoNamespace_bla_struct_inst.calls[ClassNoNamespace_bla_struct_inst.expectedCalls].check_params = 1;
    ClassNoNamespace_bla_struct_inst.expectedCalls++;
}

void ClassNoNamespace::imVirtual_ExpectAndReturn (const char *  param, int to_return, OPMOCK_MATCHER match_param)
{
    if(ClassNoNamespace_imVirtual_struct_inst.callback != NULL)
    {
        ClassNoNamespace::imVirtual_MockReset ();
    }

    if(ClassNoNamespace_imVirtual_struct_inst.callbackInst != NULL)
    {
        ClassNoNamespace::imVirtual_MockReset ();
    }

    if(ClassNoNamespace_imVirtual_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting ClassNoNamespace::imVirtual_ExpectAndReturn, call stack overload.\n");
        return;
    }

    ClassNoNamespace_imVirtual_struct_inst.calls[ClassNoNamespace_imVirtual_struct_inst.expectedCalls].param = (char *) param;
    ClassNoNamespace_imVirtual_struct_inst.calls[ClassNoNamespace_imVirtual_struct_inst.expectedCalls].match_param = match_param;
    ClassNoNamespace_imVirtual_struct_inst.calls[ClassNoNamespace_imVirtual_struct_inst.expectedCalls].return_value = to_return;
    ClassNoNamespace_imVirtual_struct_inst.calls[ClassNoNamespace_imVirtual_struct_inst.expectedCalls].check_params = 1;
    ClassNoNamespace_imVirtual_struct_inst.expectedCalls++;
}

void ClassNoNamespace::bla_Return ()
{
    if(ClassNoNamespace_bla_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting ClassNoNamespace::bla_Return, call stack overload.\n");
        return;
    }

    ClassNoNamespace_bla_struct_inst.calls[ClassNoNamespace_bla_struct_inst.expectedCalls].check_params = 0;
    ClassNoNamespace_bla_struct_inst.expectedCalls++;
}

void ClassNoNamespace::imVirtual_Return (int to_return)
{
    if(ClassNoNamespace_imVirtual_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting ClassNoNamespace::imVirtual_Return, call stack overload.\n");
        return;
    }

    ClassNoNamespace_imVirtual_struct_inst.calls[ClassNoNamespace_imVirtual_struct_inst.expectedCalls].return_value = to_return;
    ClassNoNamespace_imVirtual_struct_inst.calls[ClassNoNamespace_imVirtual_struct_inst.expectedCalls].check_params = 0;
    ClassNoNamespace_imVirtual_struct_inst.expectedCalls++;
}

space1::Class1::Class1 ()
{
}

space1::Class1::~Class1 ()
{
}

int space1::Class1::func1 (int  i, int  j)
{
    int opmock_i;
    int default_res = space1__Class1_func1_struct_inst.calls[0].return_value;

    if (space1__Class1_func1_struct_inst.callback != NULL)
    {
        space1__Class1_func1_struct_inst.actualCalls++;
        return space1__Class1_func1_struct_inst.callback (i, j, space1__Class1_func1_struct_inst.actualCalls);
    }

    else
    if (space1__Class1_func1_struct_inst.callbackInst != NULL)
    {
        space1__Class1_func1_struct_inst.actualCalls++;
        return space1__Class1_func1_struct_inst.callbackInst (i, j, space1__Class1_func1_struct_inst.actualCalls, this);
    }

    if (space1__Class1_func1_struct_inst.expectedCalls == 0)
    {
        printf ("WARNING : unexpected call of space1::Class1::func1, returning random value.\n");
        return default_res;
    }

    space1__Class1_func1_struct_inst.actualCalls++;

    if (space1__Class1_func1_struct_inst.calls[0].check_params == 1)
    {
        if (space1__Class1_func1_struct_inst.calls[0].match_i) {
            void * val1 = (void *) &space1__Class1_func1_struct_inst.calls[0].i;
            void * val2 = (void *) &i;
            int match_result = space1__Class1_func1_struct_inst.calls[0].match_i(val1, val2, "i");
            if(match_result) {
                printf("    when calling 'space1::Class1::func1' (call %d)\n", space1__Class1_func1_struct_inst.actualCalls);
            }
        }
        if (space1__Class1_func1_struct_inst.calls[0].match_j) {
            void * val1 = (void *) &space1__Class1_func1_struct_inst.calls[0].j;
            void * val2 = (void *) &j;
            int match_result = space1__Class1_func1_struct_inst.calls[0].match_j(val1, val2, "j");
            if(match_result) {
                printf("    when calling 'space1::Class1::func1' (call %d)\n", space1__Class1_func1_struct_inst.actualCalls);
            }
        }
    }

    for(opmock_i = 1; opmock_i < space1__Class1_func1_struct_inst.expectedCalls; opmock_i++)
    {
        space1__Class1_func1_struct_inst.calls[opmock_i - 1] = space1__Class1_func1_struct_inst.calls[opmock_i];
    }

    space1__Class1_func1_struct_inst.expectedCalls--;
    return default_res;
}

int space1::Class1::func2 (char *  one, char *  two)
{
    int opmock_i;
    int default_res = space1__Class1_func2_struct_inst.calls[0].return_value;

    if (space1__Class1_func2_struct_inst.callback != NULL)
    {
        space1__Class1_func2_struct_inst.actualCalls++;
        return space1__Class1_func2_struct_inst.callback (one, two, space1__Class1_func2_struct_inst.actualCalls);
    }

    else
    if (space1__Class1_func2_struct_inst.callbackInst != NULL)
    {
        space1__Class1_func2_struct_inst.actualCalls++;
        return space1__Class1_func2_struct_inst.callbackInst (one, two, space1__Class1_func2_struct_inst.actualCalls, this);
    }

    if (space1__Class1_func2_struct_inst.expectedCalls == 0)
    {
        printf ("WARNING : unexpected call of space1::Class1::func2, returning random value.\n");
        return default_res;
    }

    space1__Class1_func2_struct_inst.actualCalls++;

    if (space1__Class1_func2_struct_inst.calls[0].check_params == 1)
    {
        if (space1__Class1_func2_struct_inst.calls[0].match_one) {
            void * val1 = (void *) space1__Class1_func2_struct_inst.calls[0].one;
            void * val2 = (void *) one;
            int match_result = space1__Class1_func2_struct_inst.calls[0].match_one(val1, val2, "one");
            if(match_result) {
                printf("    when calling 'space1::Class1::func2' (call %d)\n", space1__Class1_func2_struct_inst.actualCalls);
            }
        }
        if (space1__Class1_func2_struct_inst.calls[0].match_two) {
            void * val1 = (void *) space1__Class1_func2_struct_inst.calls[0].two;
            void * val2 = (void *) two;
            int match_result = space1__Class1_func2_struct_inst.calls[0].match_two(val1, val2, "two");
            if(match_result) {
                printf("    when calling 'space1::Class1::func2' (call %d)\n", space1__Class1_func2_struct_inst.actualCalls);
            }
        }
    }

    for(opmock_i = 1; opmock_i < space1__Class1_func2_struct_inst.expectedCalls; opmock_i++)
    {
        space1__Class1_func2_struct_inst.calls[opmock_i - 1] = space1__Class1_func2_struct_inst.calls[opmock_i];
    }

    space1__Class1_func2_struct_inst.expectedCalls--;
    return default_res;
}

char space1::Class1::func3 (char * one_array[], int  another)
{
    int opmock_i;
    char default_res = space1__Class1_func3_struct_inst.calls[0].return_value;

    if (space1__Class1_func3_struct_inst.callback != NULL)
    {
        space1__Class1_func3_struct_inst.actualCalls++;
        return space1__Class1_func3_struct_inst.callback (one_array, another, space1__Class1_func3_struct_inst.actualCalls);
    }

    else
    if (space1__Class1_func3_struct_inst.callbackInst != NULL)
    {
        space1__Class1_func3_struct_inst.actualCalls++;
        return space1__Class1_func3_struct_inst.callbackInst (one_array, another, space1__Class1_func3_struct_inst.actualCalls, this);
    }

    if (space1__Class1_func3_struct_inst.expectedCalls == 0)
    {
        printf ("WARNING : unexpected call of space1::Class1::func3, returning random value.\n");
        return default_res;
    }

    space1__Class1_func3_struct_inst.actualCalls++;

    if (space1__Class1_func3_struct_inst.calls[0].check_params == 1)
    {
        if (space1__Class1_func3_struct_inst.calls[0].match_one_array) {
            void * val1 = (void *) space1__Class1_func3_struct_inst.calls[0].one_array;
            void * val2 = (void *) one_array;
            int match_result = space1__Class1_func3_struct_inst.calls[0].match_one_array(val1, val2, "one_array");
            if(match_result) {
                printf("    when calling 'space1::Class1::func3' (call %d)\n", space1__Class1_func3_struct_inst.actualCalls);
            }
        }
        if (space1__Class1_func3_struct_inst.calls[0].match_another) {
            void * val1 = (void *) &space1__Class1_func3_struct_inst.calls[0].another;
            void * val2 = (void *) &another;
            int match_result = space1__Class1_func3_struct_inst.calls[0].match_another(val1, val2, "another");
            if(match_result) {
                printf("    when calling 'space1::Class1::func3' (call %d)\n", space1__Class1_func3_struct_inst.actualCalls);
            }
        }
    }

    for(opmock_i = 1; opmock_i < space1__Class1_func3_struct_inst.expectedCalls; opmock_i++)
    {
        space1__Class1_func3_struct_inst.calls[opmock_i - 1] = space1__Class1_func3_struct_inst.calls[opmock_i];
    }

    space1__Class1_func3_struct_inst.expectedCalls--;
    return default_res;
}

void space1::Class1::func1_MockReset ()
{
    space1__Class1_func1_struct_inst.expectedCalls = 0;
    space1__Class1_func1_struct_inst.actualCalls = 0;
    space1__Class1_func1_struct_inst.callback = NULL;
    space1__Class1_func1_struct_inst.callbackInst = NULL;
}

void space1::Class1::func2_MockReset ()
{
    space1__Class1_func2_struct_inst.expectedCalls = 0;
    space1__Class1_func2_struct_inst.actualCalls = 0;
    space1__Class1_func2_struct_inst.callback = NULL;
    space1__Class1_func2_struct_inst.callbackInst = NULL;
}

void space1::Class1::func3_MockReset ()
{
    space1__Class1_func3_struct_inst.expectedCalls = 0;
    space1__Class1_func3_struct_inst.actualCalls = 0;
    space1__Class1_func3_struct_inst.callback = NULL;
    space1__Class1_func3_struct_inst.callbackInst = NULL;
}

void space1::Class1::MockReset ()
{
    space1::Class1::func1_MockReset ();
    space1::Class1::func2_MockReset ();
    space1::Class1::func3_MockReset ();
}

void space1::Class1::func1_MockWithCallback(OPMOCK_space1__Class1_func1_CALLBACK callback)
{
    space1__Class1_func1_struct_inst.callback = callback;
    space1__Class1_func1_struct_inst.callbackInst = NULL;
    space1__Class1_func1_struct_inst.expectedCalls = 0;
    space1__Class1_func1_struct_inst.actualCalls = 0;
}

void space1::Class1::func2_MockWithCallback(OPMOCK_space1__Class1_func2_CALLBACK callback)
{
    space1__Class1_func2_struct_inst.callback = callback;
    space1__Class1_func2_struct_inst.callbackInst = NULL;
    space1__Class1_func2_struct_inst.expectedCalls = 0;
    space1__Class1_func2_struct_inst.actualCalls = 0;
}

void space1::Class1::func3_MockWithCallback(OPMOCK_space1__Class1_func3_CALLBACK callback)
{
    space1__Class1_func3_struct_inst.callback = callback;
    space1__Class1_func3_struct_inst.callbackInst = NULL;
    space1__Class1_func3_struct_inst.expectedCalls = 0;
    space1__Class1_func3_struct_inst.actualCalls = 0;
}

void space1::Class1::func1_MockWithInstanceCallback(OPMOCK_space1__Class1_func1_INST_CALLBACK callback)
{
    space1__Class1_func1_struct_inst.callbackInst = callback;
    space1__Class1_func1_struct_inst.callback = NULL;
    space1__Class1_func1_struct_inst.expectedCalls = 0;
    space1__Class1_func1_struct_inst.actualCalls = 0;
}

void space1::Class1::func2_MockWithInstanceCallback(OPMOCK_space1__Class1_func2_INST_CALLBACK callback)
{
    space1__Class1_func2_struct_inst.callbackInst = callback;
    space1__Class1_func2_struct_inst.callback = NULL;
    space1__Class1_func2_struct_inst.expectedCalls = 0;
    space1__Class1_func2_struct_inst.actualCalls = 0;
}

void space1::Class1::func3_MockWithInstanceCallback(OPMOCK_space1__Class1_func3_INST_CALLBACK callback)
{
    space1__Class1_func3_struct_inst.callbackInst = callback;
    space1__Class1_func3_struct_inst.callback = NULL;
    space1__Class1_func3_struct_inst.expectedCalls = 0;
    space1__Class1_func3_struct_inst.actualCalls = 0;
}

int space1::Class1::func1_VerifyMock()
{
    int result = 1;
    if (space1__Class1_func1_struct_inst.expectedCalls != 0)
    {
        printf("Assertion failed for function `space1::Class1::func1' : bad number of calls (got %d)\n", space1__Class1_func1_struct_inst.actualCalls);
        result = 0;
    }
    return result;
}

int space1::Class1::func2_VerifyMock()
{
    int result = 1;
    if (space1__Class1_func2_struct_inst.expectedCalls != 0)
    {
        printf("Assertion failed for function `space1::Class1::func2' : bad number of calls (got %d)\n", space1__Class1_func2_struct_inst.actualCalls);
        result = 0;
    }
    return result;
}

int space1::Class1::func3_VerifyMock()
{
    int result = 1;
    if (space1__Class1_func3_struct_inst.expectedCalls != 0)
    {
        printf("Assertion failed for function `space1::Class1::func3' : bad number of calls (got %d)\n", space1__Class1_func3_struct_inst.actualCalls);
        result = 0;
    }
    return result;
}

void space1::Class1::func1_ExpectAndReturn (int  i, int  j, int to_return, OPMOCK_MATCHER match_i, OPMOCK_MATCHER match_j)
{
    if(space1__Class1_func1_struct_inst.callback != NULL)
    {
        space1::Class1::func1_MockReset ();
    }

    if(space1__Class1_func1_struct_inst.callbackInst != NULL)
    {
        space1::Class1::func1_MockReset ();
    }

    if(space1__Class1_func1_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space1::Class1::func1_ExpectAndReturn, call stack overload.\n");
        return;
    }

    space1__Class1_func1_struct_inst.calls[space1__Class1_func1_struct_inst.expectedCalls].i = i;
    space1__Class1_func1_struct_inst.calls[space1__Class1_func1_struct_inst.expectedCalls].j = j;
    space1__Class1_func1_struct_inst.calls[space1__Class1_func1_struct_inst.expectedCalls].match_i = match_i;
    space1__Class1_func1_struct_inst.calls[space1__Class1_func1_struct_inst.expectedCalls].match_j = match_j;
    space1__Class1_func1_struct_inst.calls[space1__Class1_func1_struct_inst.expectedCalls].return_value = to_return;
    space1__Class1_func1_struct_inst.calls[space1__Class1_func1_struct_inst.expectedCalls].check_params = 1;
    space1__Class1_func1_struct_inst.expectedCalls++;
}

void space1::Class1::func2_ExpectAndReturn (char *  one, char *  two, int to_return, OPMOCK_MATCHER match_one, OPMOCK_MATCHER match_two)
{
    if(space1__Class1_func2_struct_inst.callback != NULL)
    {
        space1::Class1::func2_MockReset ();
    }

    if(space1__Class1_func2_struct_inst.callbackInst != NULL)
    {
        space1::Class1::func2_MockReset ();
    }

    if(space1__Class1_func2_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space1::Class1::func2_ExpectAndReturn, call stack overload.\n");
        return;
    }

    space1__Class1_func2_struct_inst.calls[space1__Class1_func2_struct_inst.expectedCalls].one = one;
    space1__Class1_func2_struct_inst.calls[space1__Class1_func2_struct_inst.expectedCalls].two = two;
    space1__Class1_func2_struct_inst.calls[space1__Class1_func2_struct_inst.expectedCalls].match_one = match_one;
    space1__Class1_func2_struct_inst.calls[space1__Class1_func2_struct_inst.expectedCalls].match_two = match_two;
    space1__Class1_func2_struct_inst.calls[space1__Class1_func2_struct_inst.expectedCalls].return_value = to_return;
    space1__Class1_func2_struct_inst.calls[space1__Class1_func2_struct_inst.expectedCalls].check_params = 1;
    space1__Class1_func2_struct_inst.expectedCalls++;
}

void space1::Class1::func3_ExpectAndReturn (char * one_array[], int  another, char to_return, OPMOCK_MATCHER match_one_array, OPMOCK_MATCHER match_another)
{
    if(space1__Class1_func3_struct_inst.callback != NULL)
    {
        space1::Class1::func3_MockReset ();
    }

    if(space1__Class1_func3_struct_inst.callbackInst != NULL)
    {
        space1::Class1::func3_MockReset ();
    }

    if(space1__Class1_func3_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space1::Class1::func3_ExpectAndReturn, call stack overload.\n");
        return;
    }

    space1__Class1_func3_struct_inst.calls[space1__Class1_func3_struct_inst.expectedCalls].one_array = (void *) one_array;
    space1__Class1_func3_struct_inst.calls[space1__Class1_func3_struct_inst.expectedCalls].another = another;
    space1__Class1_func3_struct_inst.calls[space1__Class1_func3_struct_inst.expectedCalls].match_one_array = match_one_array;
    space1__Class1_func3_struct_inst.calls[space1__Class1_func3_struct_inst.expectedCalls].match_another = match_another;
    space1__Class1_func3_struct_inst.calls[space1__Class1_func3_struct_inst.expectedCalls].return_value = to_return;
    space1__Class1_func3_struct_inst.calls[space1__Class1_func3_struct_inst.expectedCalls].check_params = 1;
    space1__Class1_func3_struct_inst.expectedCalls++;
}

void space1::Class1::func1_Return (int to_return)
{
    if(space1__Class1_func1_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space1::Class1::func1_Return, call stack overload.\n");
        return;
    }

    space1__Class1_func1_struct_inst.calls[space1__Class1_func1_struct_inst.expectedCalls].return_value = to_return;
    space1__Class1_func1_struct_inst.calls[space1__Class1_func1_struct_inst.expectedCalls].check_params = 0;
    space1__Class1_func1_struct_inst.expectedCalls++;
}

void space1::Class1::func2_Return (int to_return)
{
    if(space1__Class1_func2_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space1::Class1::func2_Return, call stack overload.\n");
        return;
    }

    space1__Class1_func2_struct_inst.calls[space1__Class1_func2_struct_inst.expectedCalls].return_value = to_return;
    space1__Class1_func2_struct_inst.calls[space1__Class1_func2_struct_inst.expectedCalls].check_params = 0;
    space1__Class1_func2_struct_inst.expectedCalls++;
}

void space1::Class1::func3_Return (char to_return)
{
    if(space1__Class1_func3_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space1::Class1::func3_Return, call stack overload.\n");
        return;
    }

    space1__Class1_func3_struct_inst.calls[space1__Class1_func3_struct_inst.expectedCalls].return_value = to_return;
    space1__Class1_func3_struct_inst.calls[space1__Class1_func3_struct_inst.expectedCalls].check_params = 0;
    space1__Class1_func3_struct_inst.expectedCalls++;
}

space1::space2::Class2::Class2 ()
{
}

space1::space2::Class2::~Class2 ()
{
}

void space1::space2::Class2::func3 ()
{
    int opmock_i;
    if (space1__space2__Class2_func3_struct_inst.callback != NULL)
    {
        space1__space2__Class2_func3_struct_inst.actualCalls++;
        space1__space2__Class2_func3_struct_inst.callback (space1__space2__Class2_func3_struct_inst.actualCalls);
        return;
    }

    else
    if (space1__space2__Class2_func3_struct_inst.callbackInst != NULL)
    {
        space1__space2__Class2_func3_struct_inst.actualCalls++;
        space1__space2__Class2_func3_struct_inst.callbackInst (space1__space2__Class2_func3_struct_inst.actualCalls, this);
        return;
    }

    if (space1__space2__Class2_func3_struct_inst.expectedCalls == 0)
    {
        printf ("WARNING : unexpected call of space1::space2::Class2::func3, returning random value.\n");
        return;
    }

    space1__space2__Class2_func3_struct_inst.actualCalls++;

    if (space1__space2__Class2_func3_struct_inst.calls[0].check_params == 1)
    {
    }

    for(opmock_i = 1; opmock_i < space1__space2__Class2_func3_struct_inst.expectedCalls; opmock_i++)
    {
        space1__space2__Class2_func3_struct_inst.calls[opmock_i - 1] = space1__space2__Class2_func3_struct_inst.calls[opmock_i];
    }

    space1__space2__Class2_func3_struct_inst.expectedCalls--;
}

char * space1::space2::Class2::func4 (double  val)
{
    int opmock_i;
    char * default_res = space1__space2__Class2_func4_struct_inst.calls[0].return_value;

    if (space1__space2__Class2_func4_struct_inst.callback != NULL)
    {
        space1__space2__Class2_func4_struct_inst.actualCalls++;
        return space1__space2__Class2_func4_struct_inst.callback (val, space1__space2__Class2_func4_struct_inst.actualCalls);
    }

    else
    if (space1__space2__Class2_func4_struct_inst.callbackInst != NULL)
    {
        space1__space2__Class2_func4_struct_inst.actualCalls++;
        return space1__space2__Class2_func4_struct_inst.callbackInst (val, space1__space2__Class2_func4_struct_inst.actualCalls, this);
    }

    if (space1__space2__Class2_func4_struct_inst.expectedCalls == 0)
    {
        printf ("WARNING : unexpected call of space1::space2::Class2::func4, returning random value.\n");
        return default_res;
    }

    space1__space2__Class2_func4_struct_inst.actualCalls++;

    if (space1__space2__Class2_func4_struct_inst.calls[0].check_params == 1)
    {
        if (space1__space2__Class2_func4_struct_inst.calls[0].match_val) {
            void * val1 = (void *) &space1__space2__Class2_func4_struct_inst.calls[0].val;
            void * val2 = (void *) &val;
            int match_result = space1__space2__Class2_func4_struct_inst.calls[0].match_val(val1, val2, "val");
            if(match_result) {
                printf("    when calling 'space1::space2::Class2::func4' (call %d)\n", space1__space2__Class2_func4_struct_inst.actualCalls);
            }
        }
    }

    for(opmock_i = 1; opmock_i < space1__space2__Class2_func4_struct_inst.expectedCalls; opmock_i++)
    {
        space1__space2__Class2_func4_struct_inst.calls[opmock_i - 1] = space1__space2__Class2_func4_struct_inst.calls[opmock_i];
    }

    space1__space2__Class2_func4_struct_inst.expectedCalls--;
    return default_res;
}

void space1::space2::Class2::func3_MockReset ()
{
    space1__space2__Class2_func3_struct_inst.expectedCalls = 0;
    space1__space2__Class2_func3_struct_inst.actualCalls = 0;
    space1__space2__Class2_func3_struct_inst.callback = NULL;
    space1__space2__Class2_func3_struct_inst.callbackInst = NULL;
}

void space1::space2::Class2::func4_MockReset ()
{
    space1__space2__Class2_func4_struct_inst.expectedCalls = 0;
    space1__space2__Class2_func4_struct_inst.actualCalls = 0;
    space1__space2__Class2_func4_struct_inst.callback = NULL;
    space1__space2__Class2_func4_struct_inst.callbackInst = NULL;
}

void space1::space2::Class2::MockReset ()
{
    space1::space2::Class2::func3_MockReset ();
    space1::space2::Class2::func4_MockReset ();
}

void space1::space2::Class2::func3_MockWithCallback(OPMOCK_space1__space2__Class2_func3_CALLBACK callback)
{
    space1__space2__Class2_func3_struct_inst.callback = callback;
    space1__space2__Class2_func3_struct_inst.callbackInst = NULL;
    space1__space2__Class2_func3_struct_inst.expectedCalls = 0;
    space1__space2__Class2_func3_struct_inst.actualCalls = 0;
}

void space1::space2::Class2::func4_MockWithCallback(OPMOCK_space1__space2__Class2_func4_CALLBACK callback)
{
    space1__space2__Class2_func4_struct_inst.callback = callback;
    space1__space2__Class2_func4_struct_inst.callbackInst = NULL;
    space1__space2__Class2_func4_struct_inst.expectedCalls = 0;
    space1__space2__Class2_func4_struct_inst.actualCalls = 0;
}

void space1::space2::Class2::func3_MockWithInstanceCallback(OPMOCK_space1__space2__Class2_func3_INST_CALLBACK callback)
{
    space1__space2__Class2_func3_struct_inst.callbackInst = callback;
    space1__space2__Class2_func3_struct_inst.callback = NULL;
    space1__space2__Class2_func3_struct_inst.expectedCalls = 0;
    space1__space2__Class2_func3_struct_inst.actualCalls = 0;
}

void space1::space2::Class2::func4_MockWithInstanceCallback(OPMOCK_space1__space2__Class2_func4_INST_CALLBACK callback)
{
    space1__space2__Class2_func4_struct_inst.callbackInst = callback;
    space1__space2__Class2_func4_struct_inst.callback = NULL;
    space1__space2__Class2_func4_struct_inst.expectedCalls = 0;
    space1__space2__Class2_func4_struct_inst.actualCalls = 0;
}

int space1::space2::Class2::func3_VerifyMock()
{
    int result = 1;
    if (space1__space2__Class2_func3_struct_inst.expectedCalls != 0)
    {
        printf("Assertion failed for function `space1::space2::Class2::func3' : bad number of calls (got %d)\n", space1__space2__Class2_func3_struct_inst.actualCalls);
        result = 0;
    }
    return result;
}

int space1::space2::Class2::func4_VerifyMock()
{
    int result = 1;
    if (space1__space2__Class2_func4_struct_inst.expectedCalls != 0)
    {
        printf("Assertion failed for function `space1::space2::Class2::func4' : bad number of calls (got %d)\n", space1__space2__Class2_func4_struct_inst.actualCalls);
        result = 0;
    }
    return result;
}

void space1::space2::Class2::func3_ExpectAndReturn ()
{
    if(space1__space2__Class2_func3_struct_inst.callback != NULL)
    {
        space1::space2::Class2::func3_MockReset ();
    }

    if(space1__space2__Class2_func3_struct_inst.callbackInst != NULL)
    {
        space1::space2::Class2::func3_MockReset ();
    }

    if(space1__space2__Class2_func3_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space1::space2::Class2::func3_ExpectAndReturn, call stack overload.\n");
        return;
    }

    space1__space2__Class2_func3_struct_inst.calls[space1__space2__Class2_func3_struct_inst.expectedCalls].check_params = 1;
    space1__space2__Class2_func3_struct_inst.expectedCalls++;
}

void space1::space2::Class2::func4_ExpectAndReturn (double  val, char * to_return, OPMOCK_MATCHER match_val)
{
    if(space1__space2__Class2_func4_struct_inst.callback != NULL)
    {
        space1::space2::Class2::func4_MockReset ();
    }

    if(space1__space2__Class2_func4_struct_inst.callbackInst != NULL)
    {
        space1::space2::Class2::func4_MockReset ();
    }

    if(space1__space2__Class2_func4_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space1::space2::Class2::func4_ExpectAndReturn, call stack overload.\n");
        return;
    }

    space1__space2__Class2_func4_struct_inst.calls[space1__space2__Class2_func4_struct_inst.expectedCalls].val = val;
    space1__space2__Class2_func4_struct_inst.calls[space1__space2__Class2_func4_struct_inst.expectedCalls].match_val = match_val;
    space1__space2__Class2_func4_struct_inst.calls[space1__space2__Class2_func4_struct_inst.expectedCalls].return_value = to_return;
    space1__space2__Class2_func4_struct_inst.calls[space1__space2__Class2_func4_struct_inst.expectedCalls].check_params = 1;
    space1__space2__Class2_func4_struct_inst.expectedCalls++;
}

void space1::space2::Class2::func3_Return ()
{
    if(space1__space2__Class2_func3_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space1::space2::Class2::func3_Return, call stack overload.\n");
        return;
    }

    space1__space2__Class2_func3_struct_inst.calls[space1__space2__Class2_func3_struct_inst.expectedCalls].check_params = 0;
    space1__space2__Class2_func3_struct_inst.expectedCalls++;
}

void space1::space2::Class2::func4_Return (char * to_return)
{
    if(space1__space2__Class2_func4_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space1::space2::Class2::func4_Return, call stack overload.\n");
        return;
    }

    space1__space2__Class2_func4_struct_inst.calls[space1__space2__Class2_func4_struct_inst.expectedCalls].return_value = to_return;
    space1__space2__Class2_func4_struct_inst.calls[space1__space2__Class2_func4_struct_inst.expectedCalls].check_params = 0;
    space1__space2__Class2_func4_struct_inst.expectedCalls++;
}

space3::Class3::Class3 ()
{
}

space3::Class3::~Class3 ()
{
}

int space3::Class3::func5 (double  machin, int  bidule)
{
    int opmock_i;
    int default_res = space3__Class3_func5_struct_inst.calls[0].return_value;

    if (space3__Class3_func5_struct_inst.callback != NULL)
    {
        space3__Class3_func5_struct_inst.actualCalls++;
        return space3__Class3_func5_struct_inst.callback (machin, bidule, space3__Class3_func5_struct_inst.actualCalls);
    }

    else
    if (space3__Class3_func5_struct_inst.callbackInst != NULL)
    {
        space3__Class3_func5_struct_inst.actualCalls++;
        return space3__Class3_func5_struct_inst.callbackInst (machin, bidule, space3__Class3_func5_struct_inst.actualCalls, this);
    }

    if (space3__Class3_func5_struct_inst.expectedCalls == 0)
    {
        printf ("WARNING : unexpected call of space3::Class3::func5, returning random value.\n");
        return default_res;
    }

    space3__Class3_func5_struct_inst.actualCalls++;

    if (space3__Class3_func5_struct_inst.calls[0].check_params == 1)
    {
        if (space3__Class3_func5_struct_inst.calls[0].match_machin) {
            void * val1 = (void *) &space3__Class3_func5_struct_inst.calls[0].machin;
            void * val2 = (void *) &machin;
            int match_result = space3__Class3_func5_struct_inst.calls[0].match_machin(val1, val2, "machin");
            if(match_result) {
                printf("    when calling 'space3::Class3::func5' (call %d)\n", space3__Class3_func5_struct_inst.actualCalls);
            }
        }
        if (space3__Class3_func5_struct_inst.calls[0].match_bidule) {
            void * val1 = (void *) &space3__Class3_func5_struct_inst.calls[0].bidule;
            void * val2 = (void *) &bidule;
            int match_result = space3__Class3_func5_struct_inst.calls[0].match_bidule(val1, val2, "bidule");
            if(match_result) {
                printf("    when calling 'space3::Class3::func5' (call %d)\n", space3__Class3_func5_struct_inst.actualCalls);
            }
        }
    }

    for(opmock_i = 1; opmock_i < space3__Class3_func5_struct_inst.expectedCalls; opmock_i++)
    {
        space3__Class3_func5_struct_inst.calls[opmock_i - 1] = space3__Class3_func5_struct_inst.calls[opmock_i];
    }

    space3__Class3_func5_struct_inst.expectedCalls--;
    return default_res;
}

int space3::Class3::shouldBePrivate (char  j)
{
    int opmock_i;
    int default_res = space3__Class3_shouldBePrivate_struct_inst.calls[0].return_value;

    if (space3__Class3_shouldBePrivate_struct_inst.callback != NULL)
    {
        space3__Class3_shouldBePrivate_struct_inst.actualCalls++;
        return space3__Class3_shouldBePrivate_struct_inst.callback (j, space3__Class3_shouldBePrivate_struct_inst.actualCalls);
    }

    else
    if (space3__Class3_shouldBePrivate_struct_inst.callbackInst != NULL)
    {
        space3__Class3_shouldBePrivate_struct_inst.actualCalls++;
        return space3__Class3_shouldBePrivate_struct_inst.callbackInst (j, space3__Class3_shouldBePrivate_struct_inst.actualCalls, this);
    }

    if (space3__Class3_shouldBePrivate_struct_inst.expectedCalls == 0)
    {
        printf ("WARNING : unexpected call of space3::Class3::shouldBePrivate, returning random value.\n");
        return default_res;
    }

    space3__Class3_shouldBePrivate_struct_inst.actualCalls++;

    if (space3__Class3_shouldBePrivate_struct_inst.calls[0].check_params == 1)
    {
        if (space3__Class3_shouldBePrivate_struct_inst.calls[0].match_j) {
            void * val1 = (void *) &space3__Class3_shouldBePrivate_struct_inst.calls[0].j;
            void * val2 = (void *) &j;
            int match_result = space3__Class3_shouldBePrivate_struct_inst.calls[0].match_j(val1, val2, "j");
            if(match_result) {
                printf("    when calling 'space3::Class3::shouldBePrivate' (call %d)\n", space3__Class3_shouldBePrivate_struct_inst.actualCalls);
            }
        }
    }

    for(opmock_i = 1; opmock_i < space3__Class3_shouldBePrivate_struct_inst.expectedCalls; opmock_i++)
    {
        space3__Class3_shouldBePrivate_struct_inst.calls[opmock_i - 1] = space3__Class3_shouldBePrivate_struct_inst.calls[opmock_i];
    }

    space3__Class3_shouldBePrivate_struct_inst.expectedCalls--;
    return default_res;
}

int space3::Class3::multiply (int  a, int  b)
{
    int opmock_i;
    int default_res = space3__Class3_multiply_struct_inst.calls[0].return_value;

    if (space3__Class3_multiply_struct_inst.callback != NULL)
    {
        space3__Class3_multiply_struct_inst.actualCalls++;
        return space3__Class3_multiply_struct_inst.callback (a, b, space3__Class3_multiply_struct_inst.actualCalls);
    }

    else
    if (space3__Class3_multiply_struct_inst.callbackInst != NULL)
    {
        space3__Class3_multiply_struct_inst.actualCalls++;
        return space3__Class3_multiply_struct_inst.callbackInst (a, b, space3__Class3_multiply_struct_inst.actualCalls, this);
    }

    if (space3__Class3_multiply_struct_inst.expectedCalls == 0)
    {
        printf ("WARNING : unexpected call of space3::Class3::multiply, returning random value.\n");
        return default_res;
    }

    space3__Class3_multiply_struct_inst.actualCalls++;

    if (space3__Class3_multiply_struct_inst.calls[0].check_params == 1)
    {
        if (space3__Class3_multiply_struct_inst.calls[0].match_a) {
            void * val1 = (void *) &space3__Class3_multiply_struct_inst.calls[0].a;
            void * val2 = (void *) &a;
            int match_result = space3__Class3_multiply_struct_inst.calls[0].match_a(val1, val2, "a");
            if(match_result) {
                printf("    when calling 'space3::Class3::multiply' (call %d)\n", space3__Class3_multiply_struct_inst.actualCalls);
            }
        }
        if (space3__Class3_multiply_struct_inst.calls[0].match_b) {
            void * val1 = (void *) &space3__Class3_multiply_struct_inst.calls[0].b;
            void * val2 = (void *) &b;
            int match_result = space3__Class3_multiply_struct_inst.calls[0].match_b(val1, val2, "b");
            if(match_result) {
                printf("    when calling 'space3::Class3::multiply' (call %d)\n", space3__Class3_multiply_struct_inst.actualCalls);
            }
        }
    }

    for(opmock_i = 1; opmock_i < space3__Class3_multiply_struct_inst.expectedCalls; opmock_i++)
    {
        space3__Class3_multiply_struct_inst.calls[opmock_i - 1] = space3__Class3_multiply_struct_inst.calls[opmock_i];
    }

    space3__Class3_multiply_struct_inst.expectedCalls--;
    return default_res;
}

void space3::Class3::func5_MockReset ()
{
    space3__Class3_func5_struct_inst.expectedCalls = 0;
    space3__Class3_func5_struct_inst.actualCalls = 0;
    space3__Class3_func5_struct_inst.callback = NULL;
    space3__Class3_func5_struct_inst.callbackInst = NULL;
}

void space3::Class3::shouldBePrivate_MockReset ()
{
    space3__Class3_shouldBePrivate_struct_inst.expectedCalls = 0;
    space3__Class3_shouldBePrivate_struct_inst.actualCalls = 0;
    space3__Class3_shouldBePrivate_struct_inst.callback = NULL;
    space3__Class3_shouldBePrivate_struct_inst.callbackInst = NULL;
}

void space3::Class3::multiply_MockReset ()
{
    space3__Class3_multiply_struct_inst.expectedCalls = 0;
    space3__Class3_multiply_struct_inst.actualCalls = 0;
    space3__Class3_multiply_struct_inst.callback = NULL;
    space3__Class3_multiply_struct_inst.callbackInst = NULL;
}

void space3::Class3::MockReset ()
{
    space3::Class3::func5_MockReset ();
    space3::Class3::shouldBePrivate_MockReset ();
    space3::Class3::multiply_MockReset ();
}

void space3::Class3::func5_MockWithCallback(OPMOCK_space3__Class3_func5_CALLBACK callback)
{
    space3__Class3_func5_struct_inst.callback = callback;
    space3__Class3_func5_struct_inst.callbackInst = NULL;
    space3__Class3_func5_struct_inst.expectedCalls = 0;
    space3__Class3_func5_struct_inst.actualCalls = 0;
}

void space3::Class3::shouldBePrivate_MockWithCallback(OPMOCK_space3__Class3_shouldBePrivate_CALLBACK callback)
{
    space3__Class3_shouldBePrivate_struct_inst.callback = callback;
    space3__Class3_shouldBePrivate_struct_inst.callbackInst = NULL;
    space3__Class3_shouldBePrivate_struct_inst.expectedCalls = 0;
    space3__Class3_shouldBePrivate_struct_inst.actualCalls = 0;
}

void space3::Class3::multiply_MockWithCallback(OPMOCK_space3__Class3_multiply_CALLBACK callback)
{
    space3__Class3_multiply_struct_inst.callback = callback;
    space3__Class3_multiply_struct_inst.callbackInst = NULL;
    space3__Class3_multiply_struct_inst.expectedCalls = 0;
    space3__Class3_multiply_struct_inst.actualCalls = 0;
}

void space3::Class3::func5_MockWithInstanceCallback(OPMOCK_space3__Class3_func5_INST_CALLBACK callback)
{
    space3__Class3_func5_struct_inst.callbackInst = callback;
    space3__Class3_func5_struct_inst.callback = NULL;
    space3__Class3_func5_struct_inst.expectedCalls = 0;
    space3__Class3_func5_struct_inst.actualCalls = 0;
}

void space3::Class3::shouldBePrivate_MockWithInstanceCallback(OPMOCK_space3__Class3_shouldBePrivate_INST_CALLBACK callback)
{
    space3__Class3_shouldBePrivate_struct_inst.callbackInst = callback;
    space3__Class3_shouldBePrivate_struct_inst.callback = NULL;
    space3__Class3_shouldBePrivate_struct_inst.expectedCalls = 0;
    space3__Class3_shouldBePrivate_struct_inst.actualCalls = 0;
}

void space3::Class3::multiply_MockWithInstanceCallback(OPMOCK_space3__Class3_multiply_INST_CALLBACK callback)
{
    space3__Class3_multiply_struct_inst.callbackInst = callback;
    space3__Class3_multiply_struct_inst.callback = NULL;
    space3__Class3_multiply_struct_inst.expectedCalls = 0;
    space3__Class3_multiply_struct_inst.actualCalls = 0;
}

int space3::Class3::func5_VerifyMock()
{
    int result = 1;
    if (space3__Class3_func5_struct_inst.expectedCalls != 0)
    {
        printf("Assertion failed for function `space3::Class3::func5' : bad number of calls (got %d)\n", space3__Class3_func5_struct_inst.actualCalls);
        result = 0;
    }
    return result;
}

int space3::Class3::shouldBePrivate_VerifyMock()
{
    int result = 1;
    if (space3__Class3_shouldBePrivate_struct_inst.expectedCalls != 0)
    {
        printf("Assertion failed for function `space3::Class3::shouldBePrivate' : bad number of calls (got %d)\n", space3__Class3_shouldBePrivate_struct_inst.actualCalls);
        result = 0;
    }
    return result;
}

int space3::Class3::multiply_VerifyMock()
{
    int result = 1;
    if (space3__Class3_multiply_struct_inst.expectedCalls != 0)
    {
        printf("Assertion failed for function `space3::Class3::multiply' : bad number of calls (got %d)\n", space3__Class3_multiply_struct_inst.actualCalls);
        result = 0;
    }
    return result;
}

void space3::Class3::func5_ExpectAndReturn (double  machin, int  bidule, int to_return, OPMOCK_MATCHER match_machin, OPMOCK_MATCHER match_bidule)
{
    if(space3__Class3_func5_struct_inst.callback != NULL)
    {
        space3::Class3::func5_MockReset ();
    }

    if(space3__Class3_func5_struct_inst.callbackInst != NULL)
    {
        space3::Class3::func5_MockReset ();
    }

    if(space3__Class3_func5_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space3::Class3::func5_ExpectAndReturn, call stack overload.\n");
        return;
    }

    space3__Class3_func5_struct_inst.calls[space3__Class3_func5_struct_inst.expectedCalls].machin = machin;
    space3__Class3_func5_struct_inst.calls[space3__Class3_func5_struct_inst.expectedCalls].bidule = bidule;
    space3__Class3_func5_struct_inst.calls[space3__Class3_func5_struct_inst.expectedCalls].match_machin = match_machin;
    space3__Class3_func5_struct_inst.calls[space3__Class3_func5_struct_inst.expectedCalls].match_bidule = match_bidule;
    space3__Class3_func5_struct_inst.calls[space3__Class3_func5_struct_inst.expectedCalls].return_value = to_return;
    space3__Class3_func5_struct_inst.calls[space3__Class3_func5_struct_inst.expectedCalls].check_params = 1;
    space3__Class3_func5_struct_inst.expectedCalls++;
}

void space3::Class3::shouldBePrivate_ExpectAndReturn (char  j, int to_return, OPMOCK_MATCHER match_j)
{
    if(space3__Class3_shouldBePrivate_struct_inst.callback != NULL)
    {
        space3::Class3::shouldBePrivate_MockReset ();
    }

    if(space3__Class3_shouldBePrivate_struct_inst.callbackInst != NULL)
    {
        space3::Class3::shouldBePrivate_MockReset ();
    }

    if(space3__Class3_shouldBePrivate_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space3::Class3::shouldBePrivate_ExpectAndReturn, call stack overload.\n");
        return;
    }

    space3__Class3_shouldBePrivate_struct_inst.calls[space3__Class3_shouldBePrivate_struct_inst.expectedCalls].j = j;
    space3__Class3_shouldBePrivate_struct_inst.calls[space3__Class3_shouldBePrivate_struct_inst.expectedCalls].match_j = match_j;
    space3__Class3_shouldBePrivate_struct_inst.calls[space3__Class3_shouldBePrivate_struct_inst.expectedCalls].return_value = to_return;
    space3__Class3_shouldBePrivate_struct_inst.calls[space3__Class3_shouldBePrivate_struct_inst.expectedCalls].check_params = 1;
    space3__Class3_shouldBePrivate_struct_inst.expectedCalls++;
}

void space3::Class3::multiply_ExpectAndReturn (int  a, int  b, int to_return, OPMOCK_MATCHER match_a, OPMOCK_MATCHER match_b)
{
    if(space3__Class3_multiply_struct_inst.callback != NULL)
    {
        space3::Class3::multiply_MockReset ();
    }

    if(space3__Class3_multiply_struct_inst.callbackInst != NULL)
    {
        space3::Class3::multiply_MockReset ();
    }

    if(space3__Class3_multiply_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space3::Class3::multiply_ExpectAndReturn, call stack overload.\n");
        return;
    }

    space3__Class3_multiply_struct_inst.calls[space3__Class3_multiply_struct_inst.expectedCalls].a = a;
    space3__Class3_multiply_struct_inst.calls[space3__Class3_multiply_struct_inst.expectedCalls].b = b;
    space3__Class3_multiply_struct_inst.calls[space3__Class3_multiply_struct_inst.expectedCalls].match_a = match_a;
    space3__Class3_multiply_struct_inst.calls[space3__Class3_multiply_struct_inst.expectedCalls].match_b = match_b;
    space3__Class3_multiply_struct_inst.calls[space3__Class3_multiply_struct_inst.expectedCalls].return_value = to_return;
    space3__Class3_multiply_struct_inst.calls[space3__Class3_multiply_struct_inst.expectedCalls].check_params = 1;
    space3__Class3_multiply_struct_inst.expectedCalls++;
}

void space3::Class3::func5_Return (int to_return)
{
    if(space3__Class3_func5_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space3::Class3::func5_Return, call stack overload.\n");
        return;
    }

    space3__Class3_func5_struct_inst.calls[space3__Class3_func5_struct_inst.expectedCalls].return_value = to_return;
    space3__Class3_func5_struct_inst.calls[space3__Class3_func5_struct_inst.expectedCalls].check_params = 0;
    space3__Class3_func5_struct_inst.expectedCalls++;
}

void space3::Class3::shouldBePrivate_Return (int to_return)
{
    if(space3__Class3_shouldBePrivate_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space3::Class3::shouldBePrivate_Return, call stack overload.\n");
        return;
    }

    space3__Class3_shouldBePrivate_struct_inst.calls[space3__Class3_shouldBePrivate_struct_inst.expectedCalls].return_value = to_return;
    space3__Class3_shouldBePrivate_struct_inst.calls[space3__Class3_shouldBePrivate_struct_inst.expectedCalls].check_params = 0;
    space3__Class3_shouldBePrivate_struct_inst.expectedCalls++;
}

void space3::Class3::multiply_Return (int to_return)
{
    if(space3__Class3_multiply_struct_inst.expectedCalls >= MAX_FUNC_CALL)
    {
        printf("WARNING : aborting space3::Class3::multiply_Return, call stack overload.\n");
        return;
    }

    space3__Class3_multiply_struct_inst.calls[space3__Class3_multiply_struct_inst.expectedCalls].return_value = to_return;
    space3__Class3_multiply_struct_inst.calls[space3__Class3_multiply_struct_inst.expectedCalls].check_params = 0;
    space3__Class3_multiply_struct_inst.expectedCalls++;
}

