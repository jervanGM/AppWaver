#include "mem_map.h"
#include "safe_memory.h"

void store_error(uint8_t slot, int8_t value)
{
    int8_t* memoryAddress = (int8_t*)error_addresses[slot];
    *memoryAddress = value;
}



int8_t read_error(uint8_t slot)
{
    const int8_t* memoryAddress = (int8_t*)error_addresses[slot];
    return *((int8_t *)memoryAddress);
}