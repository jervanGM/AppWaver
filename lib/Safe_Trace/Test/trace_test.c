#include "trace_test.h"
#include "safe_trace.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_info_1()
{
    TRACE_INFO("PERDI LA ZAPATILLA");
}

void trace_test_suite()
{
    RUN_TEST(test_info_1);
}