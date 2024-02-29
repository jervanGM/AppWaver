#ifndef SAFE_MEMORY_H_
#define SAFE_MEMORY_H_

#include <stdint.h>
#include "safe_trace.h"

#define MAX_ERROR_ADRESSES 20

extern void store_error(uint8_t slot, int8_t value);
extern int8_t read_error(uint8_t slot);

static inline void store_error_in_slot(uint8_t slot, int8_t value)
{
    if(slot < MAX_ERROR_ADRESSES)
    {
        store_error(slot, value);
    }
    else
    {
        TRACE_ERROR("STORE ERROR: MEMORY SLOT INDEX OUT OF BOUNDS");
    }
}

static inline int8_t read_error_from_slot(uint8_t slot)
{
    if(slot < MAX_ERROR_ADRESSES)
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