#ifndef SRL_PORT_H_
#define SRL_PORT_H_

#include "i_hal_srl_port.h"

/**
 * @brief Gets the serial port.
 * 
 * @return Pointer to the serial port.
 */
const ISrlPort * hal_srl_get_port(void);

#endif /* SRL_PORT_H_ */