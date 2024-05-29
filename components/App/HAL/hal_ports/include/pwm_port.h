#ifndef PWM_PORT_H_
#define PWM_PORT_H_

#include "i_hal_pwm_port.h"

/**
 * @brief Gets the pwm port.
 * 
 * @return Pointer to the pwm port.
 */
const IPwmPort * hal_pwm_get_port(void);

#endif /* PWM_PORT_H_ */