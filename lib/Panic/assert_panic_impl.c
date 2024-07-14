/**
 * @file assert_panic.c
 * @brief Implementation of the assert panic handling function.
 */

#include "assert_panic.h"

/**
 * @brief Implementation function for assert panic.
 *
 * This function is called when an assertion fails. It prints out the file name,
 * line number, and additional information about the assertion, then aborts the program.
 *
 * @param[in] u32_line Line number where the assertion failed.
 * @param[in] pch_file File name where the assertion failed.
 * @param[in] pch_info Additional information about the assertion failure.
 */
void assert_panic_implementation(
    c_uint32_t const u32_line,
    char const * const pch_file,
    char const * const pch_info
)
{
    printf("***********************************ASSERT PANIC EXECUTED***********************************\n");
    printf("PANIC INFO: %s\n" "file: %s\n" "line: %u\n", pch_info, pch_file, (unsigned int)u32_line);
    printf("****************************************REBOOTING*****************************************\n");
    fflush(0);
    // For debugging
    assert(0);
    abort();
}
