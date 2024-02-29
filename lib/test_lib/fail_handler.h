#ifndef FAIL_HANDLER_H_
#define FAIL_HANDLER_H_
 
#include <signal.h>
#include <stdbool.h>

void Test_OK_Handler(int signo)
{
    TEST_ASSERT(true);
    exit(UNITY_END());
}

void TEST_Fail_Handler(int signo)
{
    TEST_ASSERT(false);
    exit(UNITY_END());
}

#endif /* SAFE_TRACE_H_ */