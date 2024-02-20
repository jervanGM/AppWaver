#ifndef I_HAL_ANA_PORT_H_
#define I_HAL_ANA_PORT_H_
#include <stdint.h>

typedef struct {
    void            (*init)  (void);
    void            (*reset) (void);
    void            (*write) (c_uint8_t channel,c_uint32_t data);
    void            (*read)  (c_uint8_t channel,c_uint32_t * data);
} IAnaPort;

#endif /* I_HAL_ANA_PORT_H_ */