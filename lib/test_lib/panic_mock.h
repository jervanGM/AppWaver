#ifndef PANIC_MOCK_H_
#define PANIC_MOCK_H_
 
#include <stdbool.h>

void mark_panic();

void reset_panic();

bool is_panic_executed();

#endif /* PANIC_MOCK_H_ */
