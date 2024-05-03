#ifndef MEM_PORT_H_
#define MEM_PORT_H_

#include "i_hal_mem_port.h"

/**
 * @brief Gets the external memory port.
 * 
 * @return Pointer to the external memory port.
 */
const IMemPort * hal_ext_mem_get_port(void);

#endif /* MEM_PORT_H_ */