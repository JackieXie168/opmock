#ifndef _C_SIGNATURE_H
#define _C_SIGNATURE_H

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

char functionvar1(int c, char v, ...);

#endif
