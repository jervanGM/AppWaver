#ifndef ACC_ISR_H_
#define ACC_ISR_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <esp_attr.h>

#define ACC_IT_HANDLER_ID 9

#define ACT_IT1 1
#define ACT_IT2 2

/**
 * @brief Interrupt service routine for accelerometer 1.
 *
 * This function is called when an interrupt from accelerometer 1 occurs.
 * It notifies a task identified by ACC_IT_HANDLER_ID.
 *
 * @param arg Pointer to argument (not used in this function).
 */
void IRAM_ATTR acc1_it(void *arg);

/**
 * @brief Interrupt service routine for accelerometer 2.
 *
 * This function is called when an interrupt from accelerometer 2 occurs.
 * It notifies a task identified by ACC_IT_HANDLER_ID.
 *
 * @param arg Pointer to argument (not used in this function).
 */
void IRAM_ATTR acc2_it(void *arg);

#endif /* ACC_ISR_H_ */