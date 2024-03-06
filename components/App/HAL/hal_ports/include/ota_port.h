#ifndef OTA_PORT_H_
#define OTA_PORT_H_

#include "i_hal_ota_port.h"

/**
 * @brief Gets the wireless port.
 * 
 * @return Pointer to the wireless port.
 */
const IOtaPort * hal_ota_get_port(void);

#endif /* OTA_PORT_H_ */