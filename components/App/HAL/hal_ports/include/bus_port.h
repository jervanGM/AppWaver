#ifndef BUS_PORT_H_
#define BUS_PORT_H_

#include "i_hal_bus_port.h"

/**
 * @brief Gets the bus port.
 * 
 * @return Pointer to the bus port.
 */
const IBusPort * hal_bus_get_port(void);

#endif /* BUS_PORT_H_ */