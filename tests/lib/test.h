#ifndef INC_TEST_H
#define INC_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Test result. */
typedef enum {
    PASS,
    FAILURE
} result_t;

/* Default test prototype. */
typedef result_t (*FTestProc)(void);

typedef struct {
    const char *psz_desc;
    FTestProc p_func;
} test_t;

#define TEST_CASE(desc,f) {desc, f},
#define TEST_SUITE_BEGIN(group) test_t TEST_##group[]={
#define TEST_SUITE_RUN(group) test_run(TEST_##group, (sizeof TEST_##group / sizeof TEST_##group[0]))
#define TEST_SUITE_END() };

/* Assertions. */
#define assert(cdt) {\
    if (!(cdt)) return FAILURE; \
}

#define assert_success(p) assert((p)==WHAD_SUCCESS)
#define assert_error(p) assert((p)==WHAD_ERROR)
#define assert_eq(a,e) \
    do { \
        if ((e) != (a)) { \
            return FAILURE; \
        } \
    } while (0)
#define assert_buf_eq(a,e,s) assert(!memcmp(a,e,s))

/* Main exposed function. */
bool test_run(test_t *p_test_suite, int count);

#ifdef __cplusplus
}
#endif


#endif /* INC_TEST_H */
