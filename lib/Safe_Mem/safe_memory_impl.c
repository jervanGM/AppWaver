#include "mem_map.h"
#include "safe_memory.h"

void store_error(uint8_t slot, int8_t value)
{
    error_addresses[slot] = value;
}



int8_t read_error(uint8_t slot)
{
    return error_addresses[slot];
}