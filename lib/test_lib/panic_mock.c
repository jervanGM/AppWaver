#include "panic_mock.h"

static bool is_panic = false;

void mark_panic() {
    is_panic = true;
}

void reset_panic() {
    is_panic = false;
}

bool is_panic_executed() {
    return is_panic;
}