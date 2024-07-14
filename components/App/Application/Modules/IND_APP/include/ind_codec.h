#ifndef IND_CODEC_H_
#define IND_CODEC_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i_ind_data.h"

/**
 * @brief Initializes the indicator subsystem.
 */
void ind_init();

/**
 * @brief Sets the state of the specified indicator.
 *
 * @param id Indicator ID
 * @param state Indicator state
 */
void set_indicator_state(EIndId_t id, EIndSts_t state);

#endif /* IND_CODEC_H_ */