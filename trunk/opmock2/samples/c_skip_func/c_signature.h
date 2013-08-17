#include <stdio.h>
#include <complex.h>


typedef int footype;
typedef footype * footype2;
typedef int arrayTypedef[8];
typedef double mydouble;
typedef mydouble *ptrdouble;
typedef ptrdouble * ptrptrdouble;
typedef int (*fptr)(int,int);

struct Something
{
	void *ptr;
	double dval;
	int ival;
};

/* 
 * functions returning a primitive types
 */
int function1a();
signed int function1b();//converted to int
unsigned int function1c();

long function2a();
signed long function2b();//converted to long
unsigned long function2c();

double function3();

char function4a();
unsigned char function4b();
signed char function4c();

long long function5a();
signed long long function5b();//converted to long long
unsigned long long function5c();

void function6();

float function7();

short function8a();
signed short function8b();//converted to short
unsigned short function8c();

signed function9();//signed is converted to int

long double function10();

_Bool function11();//from c99

float complex function12();//from c99. Is converted to _Complex float

double complex function13();//from c99. Is converted to _Complex double 

long double complex function14();//from c99. Is converted to _Complex long double 

/* 
 * functions returning a pointer type
 */
void * function15();
int * function16a();
unsigned int *function16b();
long double complex *function17();
long ***function18();

/* 
 * functions returning a typedefed type
 */
footype function19();
footype *function20();
footype2 function21();
footype2 *function22();
ptrdouble function23();
ptrptrdouble function24();

/* 
 * functions returning a function pointer type
 */
fptr function25();
int (*function26(int n))(int, int);
double ** (*function27(int n))(int, int);

/*
 * functions returning const 
 */
const int function28();
const double ** (*function29(int n))(int, int);
void (*function29b(int n))(int, int);
/*
 * functions returning volatile
 */
volatile int function30();

/*
 * functions with parameters
 */
int function31(int i, char j, double t, unsigned long long w);
int function32(int i, char j, ptrptrdouble t, unsigned long long ** w);
void function33(arrayTypedef td);
void function34(void);
void function35(const volatile unsigned long long param, const int param2);
int function36(int i, float, char c, double);
void function37(int parm1[], char parm2 [][20]);
void function38(char ** parm2 [][20][30][40]);
char function39(int (*pt2Func)(float, char, char), char parm2);

/*
 * functions with extern.The extern must be stripped. 
 */
extern int function40(char a);

// function without return value : defaults to int
// note that this should raise a compiler warning and should be fixed
// in the code!
//function41();

// variadic function
int function42(int c, char v, ...);


// check that macros are expanded by clang
#ifdef HAS_FUNC
int one_has_func(char i);
#endif
