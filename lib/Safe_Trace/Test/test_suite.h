#ifndef TEST_SUITE_H_
#define TEST_SUITE_H_

#include "unity.h"

extern void trace_test_suite();
extern void setUp(void);
extern void tearDown(void);

static inline void run_test_suites()
{
    trace_test_suite();
}

#define UNITY_TEST_RESET() \
    void resetTest(void) \
    {   \
        tearDown(); \
        setUp();    \
    }

#define UNITY_TEST_SUITE() \
    int main() { \
        UNITY_BEGIN(); \
        run_test_suites(); \
        return UNITY_END(); \
    }

#endif /* TEST_SUITE_H_ */