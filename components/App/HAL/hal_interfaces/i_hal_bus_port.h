#ifndef I_HAL_BUS_PORT_H_
#define I_HAL_BUS_PORT_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
typedef struct {
    int8_t (*init)(void);
    int8_t (*write_reg)(uint8_t dev_addrs, uint8_t *data, size_t len);
    int8_t (*read_reg)(uint8_t dev_addrs, uint8_t *data, size_t len);
    int8_t (*deinit)(void);
} IBusPort;

#endif /* I_HAL_BUS_PORT_H_ */