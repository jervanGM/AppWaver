#ifndef MEM_MAP_H_
#define MEM_MAP_H_
#include "esp_attr.h"
//Error memory map
#define ERROR_ADDR_COUNT 20

// Direcciones de memoria útiles desde 0x3FC8_F405 hasta 0x3FCD_FFFF
static const unsigned long error_addresses[ERROR_ADDR_COUNT] = {
    0x3FC8F405, 0x3FC8F406, 0x3FC8F407, 0x3FC8F408, 0x3FC8F409,
    0x3FC8F40A, 0x3FC8F40B, 0x3FC8F40C, 0x3FC8F40D, 0x3FC8F40E,
    0x3FC8F40F, 0x3FC8F41F, 0x3FC8F42F, 0x3FC8F43F, 0x3FC8F44F,
    0x3FC8F45F, 0x3FC8F46F, 0x3FC8F47F, 0x3FC8F48F, 0x3FC8F49F
};

#endif /* MEM_MAP_H_ */