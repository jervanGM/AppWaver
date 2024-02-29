#ifndef MEM_MAP_H_
#define MEM_MAP_H_

//Error memory map
#define ERROR_ADDR_COUNT 20

// Arreglo para almacenar las direcciones de memoria de los errores
static const unsigned long error_addresses[ERROR_ADDR_COUNT] = {
    0x00010000, 0x00010004, 0x00010008, 0x0001000C, 0x00010010,
    0x00010014, 0x00010018, 0x0001001C, 0x00010020, 0x00010024,
    0x00010028, 0x0001002C, 0x00010030, 0x00010034, 0x00010038,
    0x0001003C, 0x00010040, 0x00010044, 0x00010048, 0x0001004C
};

#endif /* MEM_MAP_H_ */