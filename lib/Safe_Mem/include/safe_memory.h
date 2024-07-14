/**
 * @file safe_memory.h
 * @brief Declarations and inline functions for safe memory operations.
 */

#ifndef SAFE_MEMORY_H_
#define SAFE_MEMORY_H_

#include <stdint.h>
#include "safe_trace.h"

/** Maximum number of error addresses. */
#define MAX_ERROR_ADRESSES 20

/**
 * @brief Stores an error value in the specified slot.
 *
 * @param[in] slot The slot number where the error value will be stored.
 * @param[in] value The error value to store.
 */
extern void store_error(uint8_t slot, int8_t value);

/**
 * @brief Reads an error value from the specified slot.
 *
 * @param[in] slot The slot number to read the error value from.
 * @return The error value from the specified slot.
 */
extern int8_t read_error(uint8_t slot);

/**
 * @brief Safely stores an error value in the specified slot if within bounds.
 *
 * @param[in] slot The slot number where the error value will be stored.
 * @param[in] value The error value to store.
 */
static inline void store_error_in_slot(uint8_t slot, int8_t value)
{
    if (slot < MAX_ERROR_ADRESSES)
    {
        store_error(slot, value);
    }
    else
    {
        TRACE_ERROR("STORE ERROR: MEMORY SLOT INDEX OUT OF BOUNDS");
    }
}

/**
 * @brief Safely reads an error value from the specified slot if within bounds.
 *
 * @param[in] slot The slot number to read the error value from.
 * @return The error value from the specified slot, or -1 if out of bounds.
 */
static inline int8_t read_error_from_slot(uint8_t slot)
{
    if (slot < MAX_ERROR_ADRESSES)
    {
        return read_error(slot);
    }
    else
    {
        TRACE_ERROR("READ ERROR: MEMORY SLOT INDEX OUT OF BOUNDS");
    }
    return -1;
}

#endif /* SAFE_MEMORY_H_ */
