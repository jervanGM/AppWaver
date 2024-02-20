#ifndef SAFE_TRACE_H_
#define SAFE_TRACE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "trace_types.h"
#include "gen_types.h"

/**
 * @file safe_trace.h
 * @brief Header file containing functions and macros for safe tracing.
 */

/**
 * @brief Implementation function for safe trace.
 *
 * This function performs the actual trace based on the provided trace type and arguments.
 *
 * @param trace_type The type of trace to be performed.
 * @param args An array of strings containing the trace arguments.
 */
extern void safe_trace_implementation(
    ETypeTrace_t trace_type, 
    const char *args[]
);

/**
 * @brief Perform a safe trace.
 *
 * This function performs a safe trace with the given trace type and arguments.
 * If the trace type is not within the valid range (DEBUG to ERROR), an error trace is performed.
 *
 * @param trace_type The type of trace to be performed.
 * @param args An array of strings containing the trace arguments.
 */
static inline void safe_trace(ETypeTrace_t trace_type, const char *args[]) {

    if(trace_type >= DEBUG && trace_type <= ERROR)
    {
        safe_trace_implementation(trace_type,args);
    }
    else
    {
        safe_trace_implementation(ERROR, (const char *[]){"INVALID TRACE TYPE", NULL});
    }

}

/**
 * @brief Convert a value to a string representation.
 *
 * This function converts a value of a given type to its string representation.
 *
 * @param type The type of the value to be converted.
 * @param value A pointer to the value to be converted.
 * @return A pointer to the string representation of the value.
 */
static inline char *to_string(EtypenameEnum_t type,const void *value) {
    static char _buffer[40];
    // Cases for various types with corresponding formatting
    switch (type) {
        case TYPE_INT8:
            snprintf(_buffer, sizeof(_buffer), F_INT8, *(const c_int8_t *)value);
            break;
        case TYPE_UINT8:
            snprintf(_buffer, sizeof(_buffer), F_UINT8, *(const c_uint8_t *)value);
            break;
        case TYPE_INT16:
            snprintf(_buffer, sizeof(_buffer), F_INT16, *(const c_int16_t *)value);
            break;
        case TYPE_UINT16:
            snprintf(_buffer, sizeof(_buffer), F_UINT16, *(const c_uint16_t *)value);
            break;
        case TYPE_INT32:
            snprintf(_buffer, sizeof(_buffer), F_INT32, *(const c_int32_t *)value);
            break;
        case TYPE_UINT32:
            snprintf(_buffer, sizeof(_buffer), F_UINT32, *(const c_uint32_t *)value);
            break;
        case TYPE_INT64:
            snprintf(_buffer, sizeof(_buffer), F_INT64, *(const c_int64_t *)value);
            break;
        case TYPE_UINT64:
            snprintf(_buffer, sizeof(_buffer), F_UINT64, *(const c_uint64_t *)value);
            break;
        case TYPE_FLOAT:
            snprintf(_buffer, sizeof(_buffer), F_FLOAT, *(const float *)value);
            break;
        case TYPE_DOUBLE:
            snprintf(_buffer, sizeof(_buffer), F_DOUBLE, *(const double *)value);
            break;
        case TYPE_BOOL:
            snprintf(_buffer, sizeof(_buffer), F_BOOL, *(const _Bool *)value ? "true" : "false");
            break;
        default:
            //#error "Unsupported type for TO_STRING macro"
            break;
    }

    return _buffer;
}

/**
 * @brief Macro to convert a value to a string.
 *
 * This macro converts a value to a string using the `to_string` function.
 *
 * @param value The value to be converted.
 * @return A string representation of the value.
 */
#define TO_STRING(value) to_string(typename(value), &value)

/**
 * @brief Macro for performing an error trace.
 *
 * This macro performs an error trace with the provided arguments.
 *
 * @param ... The arguments for the error trace.
 */
#define TRACE_ERROR(...) \
    do { \
        const char *args[] = {__VA_ARGS__, NULL}; \
        safe_trace(ERROR,args); \
    } while (0)

/**
 * @brief Macro for performing a warning trace.
 *
 * This macro performs a warning trace with the provided arguments.
 *
 * @param ... The arguments for the warning trace.
 */
#define TRACE_WARNING(...) \
    do { \
        const char *args[] = {__VA_ARGS__, NULL}; \
        safe_trace(WARNING,args); \
    } while (0)

/**
 * @brief Macro for performing an information trace.
 *
 * This macro performs an information trace with the provided arguments.
 *
 * @param ... The arguments for the information trace.
 */
#define TRACE_INFO(...) \
    do { \
        const char *args[] = {__VA_ARGS__, NULL}; \
        safe_trace(INFO, args); \
    } while (0)

/**
 * @brief Macro for performing a debug trace.
 *
 * This macro performs a debug trace with the provided arguments.
 *
 * @param ... The arguments for the debug trace.
 */
#define TRACE_DEBUG(...) \
    do { \
        const char *args[] = {__VA_ARGS__, NULL}; \
        safe_trace(DEBUG,args); \
    } while (0)

#endif /* SAFE_TRACE_H_ */