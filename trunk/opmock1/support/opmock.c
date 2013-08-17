#include "opmock.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

int opmock_test_error;
int opmock_test_run;
int opmock_test_counter;
char op_error_message [OP_MESSAGE_LENGTH];
char op_matcher_message [OP_MATCHER_MESSAGE_LENGTH];

opmock_test_struct opmock_test_array[OP_MAX_TEST];

/* store error messages */
opmock_error_message_struct opmock_error_message_array[OP_MAX_ERROR_MESSAGE];
int opmock_error_message;

/* store global call stack with names of expected functions/operations */
opmock_error_message_struct opmock_call_stack_array[OP_MAX_ERROR_MESSAGE];
int opmock_call_stack;

/* for xml output */
static FILE * report = NULL;

/* array to hold all the reset functions. One function per header file */
#define MAX_MOCK_RESETERS 100

/* array to hold all the verify functions. One function per header file */
#define MAX_MOCK_VERIFY 100

OPMOCK_RESET_CALLBACK opmock_reset_array[MAX_MOCK_RESETERS] = {NULL};
OPMOCK_VERIFY_CALLBACK opmock_verify_array[MAX_MOCK_VERIFY] = {NULL};

void opmock_test_suite_reset()
{
  opmock_test_counter = 0;
  opmock_test_error = 0;
  opmock_test_run = 0;

  /* open a file for xml output, compatible with junit */
  if(report == NULL) {
	report = fopen("./TEST-test.xml", "w");
	if(report) {
		fprintf(report, "<testsuite>\n");
	}
  }
}

void opmock_test_reset()
{
	opmock_error_message = 0;
	opmock_call_stack = 0;
	opmock_reset_all_mocks();
}

/* Internal use only for Opmock generated code */
void opmock_add_reset_callback( OPMOCK_RESET_CALLBACK callback )
{
    int i;

    for( i = 0; i < MAX_MOCK_RESETERS; i++ ) {
        /* Already registered */
        if( opmock_reset_array[i] == callback ) return;

        if( opmock_reset_array[i] == NULL ) {
            opmock_reset_array[i] = callback;
            return;
        }
    }
}

/* Internal use only for Opmock generated code */
void opmock_add_verify_callback(OPMOCK_VERIFY_CALLBACK callback)
{
    int i;

    for( i = 0; i < MAX_MOCK_VERIFY; i++ ) {
        /* Already registered */
        if( opmock_verify_array[i] == callback ) return;

        if( opmock_verify_array[i] == NULL ) {
            opmock_verify_array[i] = callback;
            return;
        }
    }
}

void opmock_reset_all_mocks()
{
    int i;
    for( i = 0; i < MAX_MOCK_RESETERS && opmock_reset_array[i] != NULL; i++ ) {
        (* opmock_reset_array[i]) ();
    }
}

void opmock_verify_all_mocks()
{
    int i;
    for( i = 0; i < MAX_MOCK_VERIFY && opmock_verify_array[i] != NULL; i++ ) {
        (* opmock_verify_array[i]) ();
    }
}


void opmock_register_test(OPMOCK_TEST_CALLBACK test, const char * test_name)
{ 
  opmock_test_array[opmock_test_counter].callback = test;
  opmock_test_array[opmock_test_counter].test_name = test_name;
  opmock_test_counter ++;
}

void opmock_test_suite_run()
{
 	int counter;
 	opmock_test_error = 0;
 	opmock_test_run = 0;
  
 	// reset terminal
	printf("\033[0m");

	for(counter = 0; counter < opmock_test_counter; counter++) {
		int previous_error = opmock_test_error;

		/* Before and after each test, play pre and post-conditions */
		/* TODO allow the use of a custom pre and post condition */
		opmock_test_reset();
		opmock_test_array[counter].callback();
		opmock_test_verify();
		opmock_test_run++;

		/* log the test in the xml output */
		if(report != NULL) {
			fprintf(report, "    <testcase classname=\"test\" name=\"%s\">\n", opmock_test_array[counter].test_name);
		}

		if(opmock_test_error > previous_error) {
			printf("\033[31m");
			printf("\033[1m");
			printf("NOK test '%s'\n", opmock_test_array[counter].test_name);
			printf("\033[0m");
			if(report != NULL) {
				/* Compose a string with all error messages */
				char messages [10000];
				opmock_sprint_error_messages(messages, 10000);
				fprintf(report, "        <failure type=\"Error\">%s", messages);
				fprintf(report, "        </failure>\n");
			} 
		}
		else {
			printf("\033[32m");
			printf("\033[1m");
			printf("OK test '%s'\n", opmock_test_array[counter].test_name);
			printf("\033[0m");
		}
		if(report != NULL) {
			fprintf(report, "    </testcase>\n");
		}	
	}

	// reset terminal
	printf("\033[0m");
	
	// print synthetic result
	if(opmock_test_error > 0)
	{
		printf("\033[31m");
	}
	printf("OPMOCK : %d tests run, %d tests failed.\n", opmock_test_run, opmock_test_error);

	printf("\033[0m");
	printf("\n");

	if(report != NULL) {
		fprintf(report, "</testsuite>\n");
		fclose(report);
	}
}

/* these 2 variables are used for approximate
 * comparisons of floating point values.
 */
static float mo_float_delta = 0.00001;
static double mo_double_delta = 0.00001;

int cmp_char(void *a, void *b, const char * name, char *message)
{
  char my_a = *((char *)a);
  char my_b = *((char *)b);
  if(my_a == my_b) {
    return 0;
  }
	snprintf(message, OP_MATCHER_MESSAGE_LENGTH, 
		 " parameter '%s' has value '%c', was expecting '%c'",
	         name, my_b, my_a);
  return -1;
}

int cmp_int(void *a, void *b, const char * name, char *message)
{
  int my_a = *((int *)a);
  int my_b = *((int *)b);
  if(my_a == my_b) {
    return 0;
  }
  snprintf(message, OP_MATCHER_MESSAGE_LENGTH, 
		 " parameter '%s' has value '%d', was expecting '%d'",
	         name, my_b, my_a);
  return -1;
}

int cmp_byte(void *a, void *b, const char * name, char *message)
{
  char my_a = *((char *)a);
  char my_b = *((char *)b);
  if(my_a == my_b) {
    return 0;
  }
	snprintf(message, OP_MATCHER_MESSAGE_LENGTH, 
		 " parameter '%s' has value '%d', was expecting '%d'",
	         name, my_b, my_a);
  return -1;
}

int cmp_short(void *a, void *b, const char * name, char *message)
{
  short my_a = *((short *)a);
  short my_b = *((short *)b);
  if(my_a == my_b) {
    return 0;
  }
  snprintf(message, OP_MATCHER_MESSAGE_LENGTH,
     " parameter '%s' has value '%d', was expecting '%d'",
           name, my_b, my_a);
  return -1;
}

int cmp_long(void *a, void *b, const char * name, char *message)
{
  long my_a = *((long *)a);
  long my_b = *((long *)b);

  if(my_a == my_b) {
    return 0;
  }
  snprintf(message, OP_MATCHER_MESSAGE_LENGTH, 
		 " parameter '%s' has value '%ld', was expecting '%ld'",
	         name, my_b, my_a);
  return -1;
}

int cmp_float(void *a, void *b, const char * name, char *message)
{
  float my_a = *((float *)a);
  float my_b = *((float *)b);

  if(my_a == my_b) {
    return 0;
  }
  snprintf(message, OP_MATCHER_MESSAGE_LENGTH, 
		 " parameter '%s' has value '%f', was expecting '%f'",
	         name, my_b, my_a);
  return -1;
}

int cmp_double(void *a, void *b, const char * name, char *message)
{
  double my_a = *((double *)a);
  double my_b = *((double *)b);

  if(my_a == my_b) {
    return 0;
  }
  snprintf(message, OP_MATCHER_MESSAGE_LENGTH, 
		 " parameter '%s' has value '%f', was expecting '%f'",
	         name, my_b, my_a);
  return -1;
}

int cmp_ptr(void *a, void *b, const char * name, char *message)
{
	void * my_a = *((void **)a);
	void * my_b = *((void **)b);
 
  if(my_a == my_b) {
    return 0;
  }
  snprintf(message, OP_MATCHER_MESSAGE_LENGTH,
                " parameter '%s' has value '%p', was expecting '%p'",
                 name, my_b, my_a);
  return -1;
}

unsigned int cmp_buffer(char *a, char *b, unsigned int length)
{
	unsigned int i;
	for(i = 0 ; i < length ; i++)
	{
		if(a[i] != b[i])
			return 1;
	}
	return 0;
}

/**
 * Test if 2 C strings are equal, as defined by strcmp.
 * @param a pointer on first string
 * @param b pointer on second string
 * @return 0 if the strings are equal, negative value if a < b,
 * positive value if a > b.
 */
int cmp_cstr(void *a, void *b, const char * name, char *message)
{ 
    char * my_a = *((char **)a);
	char * my_b = *((char **)b);

  int res = strcmp((const char *) my_a, (const char *) my_b);
  if(res == 0) {
    return res;
  }
  snprintf(message, OP_MATCHER_MESSAGE_LENGTH, " parameter '%s' has value '%s', was expecting '%s'",
	 name, (const char *) my_b, (const char *) my_a);
  return -1;
}

void set_float_delta(float delta)
{
  mo_float_delta = delta; 
}

void set_double_delta(double delta)
{
  mo_double_delta = delta; 
}

int cmp_float_delta(void *a, void *b, const char * name, char *message)
{
	float my_a = *((float *)a);
	float my_b = *((float *)b);
	float delta = fabsf (my_a - my_b);

	if(delta <  mo_float_delta) {
		return 0;
	}
	snprintf(message, OP_MATCHER_MESSAGE_LENGTH, 
		 " parameter '%s' has value '%f', was expecting '%f'",
	         name, my_b, my_a);
	return -1;
}

int cmp_double_delta(void *a, void *b, const char * name, char *message)
{
	double my_a = *((double *)a);
	double my_b = *((double *)b);
	double delta = fabs (my_a - my_b);

	if(delta <  mo_double_delta) {
		return 0;
	}
	snprintf(message, OP_MATCHER_MESSAGE_LENGTH, 
		 " parameter '%s' has value '%f', was expecting '%f'",
	         name, my_b, my_a);
	return -1;
}

char * get_matcher_message()
{
	return op_matcher_message;
}

void opmock_add_error_message(char * error_message)
{
	if(opmock_error_message < OP_MAX_ERROR_MESSAGE)
	{
		snprintf(opmock_error_message_array[opmock_error_message].message, OP_ERROR_MESSAGE_LENGTH, "%s", error_message);		
	}
	else
	{
		snprintf(opmock_error_message_array[OP_MAX_ERROR_MESSAGE -1].message, 
			OP_ERROR_MESSAGE_LENGTH, "Too many error messages (%d), can't store all of them.", opmock_error_message);
	}
	opmock_error_message++;
}

void opmock_add_call(char * operation)
{
	if(opmock_call_stack < OP_MAX_ERROR_MESSAGE)
	{
		snprintf(opmock_call_stack_array[opmock_call_stack].message, OP_ERROR_MESSAGE_LENGTH, "%s", operation);
		opmock_call_stack++;		
	}
	else
	{
		snprintf(opmock_call_stack_array[OP_MAX_ERROR_MESSAGE -1].message, 
			OP_ERROR_MESSAGE_LENGTH, "Too many calls (%d), can't store all of them.", opmock_call_stack);
	}
}

char * opmock_get_current_call()
{
	return opmock_call_stack_array[0].message;
}

void opmock_pop_call()
{
	if(opmock_call_stack > 0) {
		int index;
		for(index = 1 ;index <= opmock_call_stack; index ++) {
			strcpy(opmock_call_stack_array[index-1].message, opmock_call_stack_array[index].message); 
		}
		opmock_call_stack--;
	}
}


void opmock_print_error_messages()
{
	int i;
	int max = opmock_error_message < OP_MAX_ERROR_MESSAGE ? opmock_error_message : OP_MAX_ERROR_MESSAGE;
	for(i=0; i < max; i++)
	{
		if(strstr(opmock_error_message_array[i].message, "ERROR"))
		{
			printf("\033[31m");
		}
		else if(strstr(opmock_error_message_array[i].message, "WARNING"))
		{
			//printf("\033[33m");
			printf("\033[35m");
		}
		printf("%s\n", opmock_error_message_array[i].message);
	}
}

void opmock_sprint_error_messages(char *messages, int max_size)
{
	int i;
	int max = opmock_error_message < OP_MAX_ERROR_MESSAGE ? opmock_error_message : OP_MAX_ERROR_MESSAGE;
	strcpy(messages, "");
	int sum = 0;

	for(i = 0; i < max; i++)
	{
		int len = strlen(opmock_error_message_array[i].message)+1;/* +1 for the NULL terminating byte */
		sum += len;
		if(max_size > (sum+1)) {
			strcat(messages, opmock_error_message_array[i].message);
			if(i < max)
				strcat(messages, "\n");
		}
	}
}

int opmock_get_number_of_errors()
{
	return opmock_error_message;
}

/* get the number of errors/warnings in a test, but skipping all errors
 * related to call ordering. Useful in case one wants to run a verify phase
 * but check only parameters.
 */
int opmock_get_number_of_errors_no_order()
{
	int real_errors = 0;
	int i;
	for(i = 0; i < opmock_error_message; i++) {
		if (strstr (opmock_error_message_array[i].message, "WARNING : got call to") == NULL)
		{
			real_errors++;
		}
	}
	return real_errors;
}

void opmock_test_verify()
{
	opmock_verify_all_mocks();
}
