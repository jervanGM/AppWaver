#include "assert_panic.h"

void assert_panic_implementation
(
    uint32_t const u32_line,
    char const * const pch_file,
    char const * const pch_info
)
{
    printf("***********************************ASSERT PANIC EXECUTED***********************************\n");
    printf("PANIC INFO: %s\n" "file: %s\n" "line: %u\n",pch_info, pch_file, (unsigned int)u32_line);
    printf("****************************************RESTARTING*****************************************\n");
    fflush(0);
    //For debugging
    assert(0);
    abort();
}