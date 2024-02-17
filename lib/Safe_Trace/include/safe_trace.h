#ifndef SAFE_TRACE_H_
#define SAFE_TRACE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "trace_types.h"
extern void safe_trace_implementation(
    ETypeTrace_t trace_type, 
    const char *args[]
);

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


static inline char *to_string(ETypeNameEnum_t type,const void *value) {
    static char _buffer[40];
    switch (type) {
        case TYPE_INT8:
            snprintf(_buffer, sizeof(_buffer), F_INT8, *(const int8_t *)value);
            break;
        case TYPE_UINT8:
            snprintf(_buffer, sizeof(_buffer), F_UINT8, *(const uint8_t *)value);
            break;
        case TYPE_INT16:
            snprintf(_buffer, sizeof(_buffer), F_INT16, *(const int16_t *)value);
            break;
        case TYPE_UINT16:
            snprintf(_buffer, sizeof(_buffer), F_UINT16, *(const uint16_t *)value);
            break;
        case TYPE_INT32:
            snprintf(_buffer, sizeof(_buffer), F_INT32, *(const int32_t *)value);
            break;
        case TYPE_UINT32:
            snprintf(_buffer, sizeof(_buffer), F_UINT32, *(const uint32_t *)value);
            break;
        case TYPE_INT64:
            snprintf(_buffer, sizeof(_buffer), F_INT64, *(const int64_t *)value);
            break;
        case TYPE_UINT64:
            snprintf(_buffer, sizeof(_buffer), F_UINT64, *(const uint64_t *)value);
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

#define TO_STRING(value) to_string(typename(value), &value)


#define TRACE_ERROR(...) \
    do { \
        const char *args[] = {__VA_ARGS__, NULL}; \
        safe_trace(ERROR,args); \
    } while (0)

#define TRACE_WARNING(...) \
    do { \
        const char *args[] = {__VA_ARGS__, NULL}; \
        safe_trace(WARNING,args); \
    } while (0)

#define TRACE_INFO(...) \
    do { \
        const char *args[] = {__VA_ARGS__, NULL}; \
        safe_trace(INFO, args); \
    } while (0)

#define TRACE_DEBUG(...) \
    do { \
        const char *args[] = {__VA_ARGS__, NULL}; \
        safe_trace(DEBUG,args); \
    } while (0)

#endif /* SAFE_TRACE_H_ */