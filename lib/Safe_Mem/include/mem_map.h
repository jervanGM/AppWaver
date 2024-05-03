#ifndef MEM_MAP_H_
#define MEM_MAP_H_
#include "esp_attr.h"
#include <stdint.h>
//Error memory map
#define ERROR_ADDR_COUNT 20

int8_t error_addresses[ERROR_ADDR_COUNT] = {0};

#endif /* MEM_MAP_H_ */