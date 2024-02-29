#ifndef ANA_PORT_H_
#define ANA_PORT_H_

#include "i_hal_ana_port.h"

/**
 * @brief Gets the analog port.
 * 
 * @return Pointer to the analog port.
 */
const IAnaPort * hal_ana_get_port(void);

#endif /* ANA_PORT_H_ */