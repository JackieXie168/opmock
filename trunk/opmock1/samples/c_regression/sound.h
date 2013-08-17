#ifndef SOUND_H_ 
#define SOUND_H_


typedef int tStatus;
typedef float ePipDSCP;
typedef char eSGT_FC;
typedef double eFC;
typedef int tUint32;
typedef unsigned int u_int32;
typedef unsigned char u_int8;

typedef struct
{
  int foo;
  double boo;
} Toto;

 
int do_sound(char *sound);
int functionWithConstParameters(int j, const float b, const char *ptr);
int functionWithArray(char * array []);
int functionTotoValue(Toto toto);
int functionTotoPtr(Toto *toto);

tStatus pipDbSgtQosInit (tUint32 vRtrID, const ePipDSCP dscpPerProto[],
                        const eSGT_FC dot1pPerProto[], const eFC fcPerDscp[]);

int withVoidParameter(int one, float two, void (*myfunc)(void), char *bla);
float withAnonymousParameter(int one, float two, char *, double, int x);

// check void parameters (regression in 0.5.6)
extern unsigned long with_void_parameter (void);

// signature with 2 consts in a parameter
u_int32 oak_spi_datatransfer (u_int32 ZF_dev_nbr,
                                 const u_int8* const TxBuffer,
                                 u_int8* const RxBuffer,
                                 u_int32 NrOfBits,
                                 u_int32 TimeoutInmsec,
				 const u_int8** const bla,
				 const unsigned long long ** const bli,
				 const long double *** blo,
				 const float x,
				 long double *** const y,
				 const char * array [],
				 const char array2 [] [5],
				 const char * const array3 [] [5]);

//typedef tUint8 ModeA [6];
typedef unsigned char tUint8;
typedef tUint8 ModeA [6];//creates problems. According to the C standard, I can't affect an array to a pointer and vice-versa
//unfortunately that's the only way to store the address of the first element of an array in Opmock.
//we don't have enough information from the swig xml file to know that this typedef is an array (in which case
//we could just force a cast to a pointer type. The compiler would be happy, and it would work)
// signature with an array typedef. Issue 3437515 in Trac/sourceforge

//int getSomethingIssue_3437515(ModeA paramA); can't work
int getSomethingIssue_3437515(tUint8 paramA [6]);

//typedef of a pointer then use matchers
typedef int * MyIntPtr;
int takeIntTypedef(MyIntPtr onePtr);

const char *func_returns_const(int j);

void anonymous_with_const(const char *, const int *);


#endif
