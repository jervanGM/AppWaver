#ifndef BTN_ISR_H_
#define BTN_ISR_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <esp_attr.h>

#define BTN_HANDLER_ID 3

/**
 * @brief Interrupt service routine (ISR) for button press events.
 *
 * This ISR is triggered upon a button press event and notifies the corresponding
 * task handler to handle the button action.
 *
 * @param arg Pointer to arguments passed to the ISR (unused in this function).
 *
 */
void IRAM_ATTR button_it(void *arg);

#endif /* BTN_ISR_H_ */






