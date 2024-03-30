#ifndef IO_PORT_H_
#define IO_PORT_H_


#include "i_hal_io_port.h"

/**
 * @brief Gets the analog port.
 * 
 * @return Pointer to the analog port.
 */
const IIOPort * hal_io_get_port(void);

#endif /* IO_PORT_H_ */