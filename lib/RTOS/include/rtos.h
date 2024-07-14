/**
 * @file rtos.h
 * @brief RTOS task and mutex management functions.
 *
 * This header file provides the interface for creating, managing, and manipulating tasks and mutexes 
 * in a FreeRTOS environment. It defines various functions to create periodic and sporadic tasks, 
 * control task states, handle task notifications, and manage mutexes.
 */

#ifndef RTOS_H_
#define RTOS_H_

#include "task_types.h"
#include <stdint.h>

#define MAX_MUTEX 20         /**< Maximum number of mutexes that can be created */
#define MAX_TASK_HANDLE 10   /**< Maximum number of task handles that can be used */

/**
 * @brief Task function type definition.
 *
 * This defines the prototype for the task functions that will be created.
 */
typedef void (*TaskFunction_t)(void *);

/**
 * @brief Create a periodic task.
 *
 * @param[in] task_func Function to execute as the task.
 * @param[in] task_name Name of the task.
 * @param[in] stack_deph Stack depth of the task.
 * @param[in] period Period of the task in ticks.
 * @param[in] priority Priority of the task.
 * @param[in] handle_id Handle ID for the task.
 * @return Task configuration error code.
 * @retval TASK_OK Task created successfully.
 * @retval TASK_MEM_ERR Not enough memory to create the task.
 * @retval TASK_UNKNOWN_ERR Unknown error occurred.
 *
 * This function creates a periodic task with the specified parameters. The task will execute the given
 * function periodically based on the specified period.
 */
ETaskCfgError_t create_task(TaskFunction_t task_func, const char *const task_name, const uint32_t stack_deph, int period, unsigned int priority, uint8_t handle_id);

/**
 * @brief Create a sporadic task.
 *
 * @param[in] task_func Function to execute as the task.
 * @param[in] task_name Name of the task.
 * @param[in] handle_id Handle ID for the task.
 * @return Task configuration error code.
 * @retval TASK_OK Task created successfully.
 * @retval TASK_MEM_ERR Not enough memory to create the task.
 * @retval TASK_UNKNOWN_ERR Unknown error occurred.
 *
 * This function creates a sporadic task with the specified parameters. The task will execute the given
 * function once and will not repeat periodically.
 */
ETaskCfgError_t create_sporadic_task(TaskFunction_t task_func, const char *const task_name, uint8_t handle_id);

/**
 * @brief Suspend a task.
 *
 * @param[in] handle_id Handle ID of the task to suspend.
 *
 * This function suspends the specified task, preventing it from being scheduled until it is resumed.
 */
void suspend_task(uint8_t handle_id);

/**
 * @brief Resume a suspended task.
 *
 * @param[in] handle_id Handle ID of the task to resume.
 *
 * This function resumes the specified task, allowing it to be scheduled again.
 */
void resume_task(uint8_t handle_id);

/**
 * @brief Get the RTOS state of a task.
 *
 * @param[in] handle_id Handle ID of the task.
 * @return Task state as an ETaskState_t value.
 *
 * This function retrieves the current state of the specified task, such as running, suspended, etc.
 */
ETaskState_t get_task_rtos_state(uint8_t handle_id);

/**
 * @brief Get the current RTOS tick count.
 *
 * @return Current RTOS tick count.
 *
 * This function retrieves the current tick count from the RTOS. This can be used for time measurements.
 */
uint32_t get_task_tick_count(void);

/**
 * @brief Get the current RTOS tick count from an ISR.
 *
 * @return Current RTOS tick count from ISR.
 *
 * This function retrieves the current tick count from the RTOS within an interrupt service routine.
 */
uint32_t get_task_tick_count_from_it(void);

/**
 * @brief Notify a task from an ISR.
 *
 * @param[in] handle_id Handle ID of the task to notify.
 *
 * This function sends a notification to the specified task from an ISR. It can be used to unblock tasks
 * waiting for notifications.
 */
void notify_to_task_from_it(uint8_t handle_id);

/**
 * @brief Notify a task from an ISR with a specific value.
 *
 * @param[in] handle_id Handle ID of the task to notify.
 * @param[in] value Value to notify the task with.
 *
 * This function sends a notification with a specific value to the specified task from an ISR. It can be used
 * to send data to a task from an interrupt context.
 */
void notify_to_task_from_it_with_value(uint8_t handle_id, uint32_t value);

/**
 * @brief Wait for an event in the current task.
 *
 * @return Notification value.
 *
 * This function makes the current task wait for an event notification. It blocks the task until a notification
 * is received.
 */
uint32_t task_wait_for_event(void);

/**
 * @brief Delay a task until a specific time.
 *
 * @param[in] PreviousWakeTime Pointer to the previous wake time.
 * @param[in] ms_delay Delay in milliseconds.
 *
 * This function delays the task until the specified time has passed. It is useful for periodic tasks that need
 * to execute at regular intervals.
 */
void task_delay_until(uint32_t *PreviousWakeTime, uint32_t ms_delay);

/**
 * @brief Delay a task for a specific duration.
 *
 * @param[in] ms_delay Delay in milliseconds.
 *
 * This function delays the task for the specified duration. The task will be blocked for the duration of the delay.
 */
void task_delay(uint32_t ms_delay);

/**
 * @brief Create a set of mutexes.
 *
 * This function creates a predefined number of mutexes. Each mutex can be used for mutual exclusion in different
 * parts of the code.
 */
void mutex_create(void);

/**
 * @brief Lock a mutex.
 *
 * @param[in] mutex_id ID of the mutex to lock.
 *
 * This function locks the specified mutex, blocking other tasks from accessing the protected resource until the mutex
 * is unlocked.
 */
void mutex_lock(uint8_t mutex_id);

/**
 * @brief Unlock a mutex.
 *
 * @param[in] mutex_id ID of the mutex to unlock.
 *
 * This function unlocks the specified mutex, allowing other tasks to access the protected resource.
 */
void mutex_unlock(uint8_t mutex_id);

#endif /* RTOS_H_ */
