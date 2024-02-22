#ifndef ANA_PORT_H_
#define ANA_PORT_H_

#include "i_hal_ana_port.h"

const IAnaPort * hal_ana_get_port(void);

static void ana_port_init(void);

static void ana_port_reset(void);

static void ana_port_read(uint8_t channel,uint32_t * data);

static void ana_port_write(uint8_t channel,uint32_t data);

// Implementación de la interfaz de la HAL del ADC
static const IAnaPort ana_port_interface = {
    .init = ana_port_init,
    .reset = ana_port_reset,
    .read = ana_port_read,
    .write = ana_port_write
};

#endif /* ANA_PORT_H_ */