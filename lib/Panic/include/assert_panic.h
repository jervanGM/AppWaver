#ifndef ASSERT_PANIC_H_
#define ASSERT_PANIC_H_
#include <stdio.h>
#include <stdbool.h>
#include "gen_types.h"
extern void assert_panic_implementation(
    c_uint32_t const u32_line,
    char const * const pch_file,
    char const * const pch_info
);

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

#define ASSERT_PANIC(condition, message) \
    do { \
        assert_panic((condition), __LINE__, __FILE__, (char const *)(message)); \
    } while (0)


#endif /* ASSERT_PANIC_H_ */