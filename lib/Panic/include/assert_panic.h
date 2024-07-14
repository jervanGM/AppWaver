/**
 * @file assert_panic.h
 * @brief Declarations and inline function for assert panic handling.
 */

#ifndef ASSERT_PANIC_H_
#define ASSERT_PANIC_H_

#include <stdio.h>
#include <stdbool.h>
#include "gen_types.h"

/**
 * @brief Implementation function for assert panic.
 *
 * This function is called when an assertion fails.
 *
 * @param[in] u32_line Line number where the assertion failed.
 * @param[in] pch_file File name where the assertion failed.
 * @param[in] pch_info Additional information about the assertion failure.
 */
extern void assert_panic_implementation(
    c_uint32_t const u32_line,
    char const * const pch_file,
    char const * const pch_info
);

/**
 * @brief Inline function to check a condition and call panic implementation if the condition is false.
 *
 * @param[in] a_cond Condition to check.
 * @param[in] u32_line Line number where the assertion is being checked.
 * @param[in] pch_file File name where the assertion is being checked.
 * @param[in] pch_info Additional information about the assertion.
 */
static inline void assert_panic(bool const a_cond,
                                c_uint32_t const u32_line,
                                char const * const pch_file,
                                char const * const pch_info)
{
    if (!a_cond)
    {
        assert_panic_implementation(u32_line, pch_file, pch_info);
    }
}

/**
 * @brief Macro to check a condition and invoke panic if the condition is false.
 *
 * @param[in] condition Condition to check.
 * @param[in] message Additional information about the assertion.
 */
#define ASSERT_PANIC(condition, message) \
    do { \
        assert_panic((condition), __LINE__, __FILE__, (char const *)(message)); \
    } while (0)

#endif /* ASSERT_PANIC_H_ */
