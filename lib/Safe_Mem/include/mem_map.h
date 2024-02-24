#ifndef MEM_MAP_H_
#define MEM_MAP_H_
#include "esp_attr.h"
//Error memory map
#define ERROR_ADDR_COUNT 20

// Direcciones de memoria útiles desde 0x3FC8_B404 hasta 0x3FCD_FFFF
static const unsigned long error_addresses[ERROR_ADDR_COUNT] = {
    0x3FC8B404, 0x3FC8B405, 0x3FC8B406, 0x3FC8B407, 0x3FC8B408,
    0x3FC8B409, 0x3FC8B40A, 0x3FC8B40B, 0x3FC8B40C, 0x3FC8B40D,
    0x3FC8B40E, 0x3FC8B40F, 0x3FC8B41F, 0x3FC8B42F, 0x3FC8B43F,
    0x3FC8B44F, 0x3FC8B45F, 0x3FC8B46F, 0x3FC8B47F, 0x3FC8B48F
};

#endif /* MEM_MAP_H_ */