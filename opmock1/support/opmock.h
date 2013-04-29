#ifndef OPMOCK_H_
#define OPMOCK_H_

#include <stdio.h>
#include <string.h>

#define OP_MESSAGE_LENGTH 500
#define OP_MATCHER_MESSAGE_LENGTH 10000
#define OP_MAX_TEST 1000
#define OP_ERROR_MESSAGE_LENGTH 2000
#define OP_MAX_ERROR_MESSAGE 100
#define MAX_FUNC_CALL 100

/*
 * Your own matchers must implement this interface.
 * A matcher must return 0 if the two values are considered equal.
 * The definition of equality can vary depending on the object types.
 * For primitive types (like int, float...), it's the actual equality.
 * For your own complex types, it could be the equality of some struct
 * or class members.
 * The two parameters are always void pointers. They must be cast by
 * the matcher to the actual type. Have a look to opmock.c for some examples.
 */
typedef int (* OPMOCK_MATCHER)(void *  a, void * b, const char * name, char * message);

/*
 * Callback definition for a test
 */
typedef void (* OPMOCK_TEST_CALLBACK)();
typedef void (* OPMOCK_VERIFY_CALLBACK)();

/*
 * Macros for easy writing of tests
 */
#define OP_ASSERT_EQUAL_INT(expected, actual) \
	do { \
  if((int)(expected) != (int)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %d != %d", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message); \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_INT(expected, actual) \
do { \
  if((int)(expected) == (int)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %d == %d", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message); \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_EQUAL_UINT(expected, actual) \
do { \
  if((unsigned int)(expected) != (unsigned int)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %u != %u", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message); \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_UINT(expected, actual) \
do { \
  if((unsigned int)(expected) == (unsigned int)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %u == %u", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message); \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_EQUAL_SHORT(expected, actual) \
do { \
  if((short)(expected) != (short)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %hi != %hi", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message); \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_SHORT(expected, actual) \
do { \
  if((short)(expected) == (short)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %hi == %hi", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message); \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_EQUAL_USHORT(expected, actual) \
do { \
  if((unsigned short)(expected) != (unsigned short)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %hu != %hu", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message); \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_USHORT(expected, actual) \
do { \
  if((unsigned short)(expected) == (unsigned short)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %hu == %hu", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message); \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_EQUAL_LONG(expected, actual) \
do { \
  if((long)(expected) != (long)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %ld != %ld", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message); \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_LONG(expected, actual) \
do { \
  if((long)(expected) == (long)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %ld == %ld", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message); \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_EQUAL_ULONG(expected, actual) \
do { \
  if((unsigned long)(expected) != (unsigned long)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %lu != %lu", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message); \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_ULONG(expected, actual) \
do { \
  if((unsigned long)(expected) == (unsigned long)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %lu == %lu", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message); \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_EQUAL_FLOAT(expected, actual) \
do { \
  if((expected) != (actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %f != %f", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++;                                                \
    opmock_print_error_messages();                                      \
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_FLOAT(expected, actual) \
do { \
  if((expected) == (actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %f == %f", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++;                                                \
    opmock_print_error_messages();                                      \
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_EQUAL_CSTRING(expected, actual) \
do { \
  if(strcmp((expected), (actual)) != 0) {					\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected '%s' != '%s'", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();								\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_CSTRING(expected, actual) \
do { \
  if(strcmp((expected), (actual)) == 0) {					\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected '%s' == '%s'", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();								\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_TRUE(expected) \
do { \
  if(!((expected))) {							\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d", __BASE_FILE__, __LINE__); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages(); 								\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_FALSE(expected) \
do { \
  if((expected)) {							\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d", __BASE_FILE__, __LINE__); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_EQUAL_CHAR(expected, actual) \
do { \
  if((char)(expected) != (char)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected '%c' != '%c'", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_CHAR(expected, actual) \
do { \
  if((char)(expected) == (char)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected '%c' == '%c'", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_EQUAL_UCHAR(expected, actual)	\
do { \
  if((unsigned char)(expected) != (unsigned char)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected '%cu' != '%cu'", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_UCHAR(expected, actual) \
do { \
  if((unsigned char)(expected) == (unsigned char)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected '%cu' == '%cu'", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_EQUAL_BYTE(expected, actual) \
do { \
  if((char)(expected) != (char)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %d != %d", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_BYTE(expected, actual) \
do { \
  if((char)(expected) == (char)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %d == %d", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_EQUAL_UBYTE(expected, actual) \
do { \
  if((unsigned char)(expected) != (unsigned char)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %u != %u", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_UBYTE(expected, actual) \
do { \
  if((unsigned char)(expected) == (unsigned char)(actual)) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, expected %u == %u", __BASE_FILE__, __LINE__, (expected), (actual)); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_EQUAL_BUFFER(expected, actual, length) \
do { \
    if(cmp_buffer((char *) (expected), (char *) (actual), (length)) != 0) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, buffers are not equal", __BASE_FILE__, __LINE__); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )

#define OP_ASSERT_NOT_EQUAL_BUFFER(expected, actual, length) \
do { \
    if(cmp_buffer((char *) (expected), (char *) (actual), (length)) == 0) {						\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : ASSERT failed in file %s at line %d, buffers are equal", __BASE_FILE__, __LINE__); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++; \
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )


#define OP_VERIFY()						\
do { \
  opmock_test_verify(); \
  if (opmock_get_number_of_errors() != 0) {					\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : Verify failed in file %s at line %d", __BASE_FILE__, __LINE__); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++;						\
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )
	

#define OP_VERIFY_NO_ORDER()						\
do { \
  opmock_test_verify(); \
  if (opmock_get_number_of_errors_no_order() != 0) {					\
    snprintf(op_error_message, OP_MESSAGE_LENGTH, "ERROR : Verify failed in file %s at line %d", __BASE_FILE__, __LINE__); \
    opmock_add_error_message((char *) op_error_message);                \
    opmock_test_error++;						\
    opmock_print_error_messages();						\
    return;								\
  } \
} while ( 0 )
						


/*
 * Helper struct when playing tests as a suite
 */
typedef struct
{
  OPMOCK_TEST_CALLBACK callback;
  const char *test_name;
} opmock_test_struct;

/*
 * Simple struct to create an array of error messages
 */
typedef struct
{
  char message [OP_ERROR_MESSAGE_LENGTH];
} opmock_error_message_struct;

/*
 * Some global variables to hold common counters
 * NOTICE : storing references to globals in a header file
 * is a very bad practice. This is acceptable here *only* because the C and header
 * files will *always* be used in the same build. This saves some extern declarations
 * in the test files.
 */
extern int opmock_test_error;
extern int opmock_test_run;
extern int opmock_test_counter;
extern char op_error_message [OP_MESSAGE_LENGTH];


#ifdef __cplusplus
extern "C" {
#endif

/*
 * Reset the test framework before registering a test suite
 */
void opmock_test_suite_reset();

/*
 * Reset the mocks, callbacks, errors, and counters before running a single test
 */
void opmock_test_reset();

/*
 * Verify the mocks calls and all errors in the scope of a single test
 */
void opmock_test_verify();

/*
 * Register a single test. Call opmock_reset_test once before registering a list of tests.
 */
void opmock_register_test(OPMOCK_TEST_CALLBACK test, const char * test_name);

/*
 * Utility functions to avoid global variable exposure
 */
char * get_matcher_message();
void opmock_add_error_message(char *error_message);
void opmock_add_call(char * operation);
char * opmock_get_current_call();
void opmock_pop_call();
void opmock_print_error_messages();
void opmock_sprint_error_messages(char *messages, int max_size);
int opmock_get_number_of_errors();
int opmock_get_number_of_errors_no_order();
void opmock_add_verify_callback(OPMOCK_VERIFY_CALLBACK callback);

/*
 * Signature to register MockReset function
 */
typedef void (* OPMOCK_RESET_CALLBACK)();
void opmock_add_reset_callback ( OPMOCK_RESET_CALLBACK function );
void opmock_reset_all_mocks ();
void opmock_verify_all_mocks ();

/*
 * Run all tests and get a report of success and failures
 */
void opmock_test_suite_run();

int cmp_char(void *a, void *b, const char * name, char * message);
int cmp_byte(void *a, void *b, const char * name, char *message);
int cmp_int(void *a, void *b, const char * name, char * message);
int cmp_short(void *a, void *b, const char * name, char * message);
int cmp_long(void *a, void *b, const char * name, char * message);
int cmp_float(void *a, void *b, const char * name, char * message);
int cmp_double(void *a, void *b, const char * name, char * message);
int cmp_ptr(void *a, void *b, const char * name, char * message);
int cmp_cstr(void *a, void *b, const char * name, char * message);
int cmp_float_delta(void *a, void *b, const char * name, char * message);
int cmp_double_delta(void *a, void *b, const char * name, char * message);

/* this function is special : it's not a matcher as it takes an additional parameter, length
 * returns 0 if buffers are equal, otherwise the index where the first difference is found.
*/
unsigned int cmp_buffer(char *a, char *b, unsigned int length);

void set_float_delta(float delta);
void set_double_delta(double delta);

#ifdef __cplusplus
}
#endif

#endif
