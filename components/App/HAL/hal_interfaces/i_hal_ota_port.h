#ifndef I_HAL_OTA_PORT_H_
#define I_HAL_OTA_PORT_H_

#include <stdint.h>
#include <stddef.h>

typedef struct {
    int8_t (*init)  (void);
    void (*update_reboot) (void);
    int8_t (*write) (const void *data, size_t length);
    void (*reset) (void);
    int8_t (*finish) (void);
    int8_t (*upgrade) (void);
    int8_t (*update_install) (void);
} IOtaPort;

#endif /* I_HAL_OTA_PORT_H_ */