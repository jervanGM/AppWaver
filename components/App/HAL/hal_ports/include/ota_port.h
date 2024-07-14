#ifndef OTA_PORT_H_
#define OTA_PORT_H_

#include "i_hal_ota_port.h"

/**
 * @brief Gets the OTA port.
 * 
 * @return Pointer to the OTA port.
 */
const IOtaPort * hal_ota_get_port(void);

#endif /* OTA_PORT_H_ */