#ifndef WLS_PORT_H_
#define WLS_PORT_H_

#include "i_hal_wls_port.h"

/**
 * @brief Gets the wireless port.
 * 
 * @return Pointer to the wireless port.
 */
const IWlsPort * hal_wls_get_port(void);

#endif /* WLS_PORT_H_ */