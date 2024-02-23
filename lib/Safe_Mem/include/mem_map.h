#ifndef MEM_MAP_H_
#define MEM_MAP_H_

//Error memory map
#define ERROR_ADDR_COUNT 20

// Arreglo para almacenar las direcciones de memoria de los errores
static const unsigned long error_addresses[ERROR_ADDR_COUNT] = {
    0x3FF00001, 0x3FF00002, 0x3FF00003, 0x3FF00004, 0x3FF00005,
    0x3FF00006, 0x3FF00007, 0x3FF00008, 0x3FF00009, 0x3FF00010,
    0x3FF00011, 0x3FF00012, 0x3FF00013, 0x3FF00014, 0x3FF00015,
    0x3FF00016, 0x3FF00017, 0x3FF00018, 0x3FF00019, 0x3FF00020
};

#endif /* MEM_MAP_H_ */