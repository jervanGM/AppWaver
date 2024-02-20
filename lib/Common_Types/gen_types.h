#ifndef GEN_TYPES_H_
#define GEN_TYPES_H_

#include <stdint.h>

#define GEN_TYPES_CAST(TYPE, VALUE) ((TYPE)(VALUE))

#define G_INT8_C(VALUE) GEN_TYPES_CAST(c_int8_t,VALUE)
#define G_INT16_C(VALUE) GEN_TYPES_CAST(c_int16_t,VALUE)
#define G_INT32_C(VALUE) GEN_TYPES_CAST(c_int32_t,VALUE)
#define G_INT64_C(VALUE) GEN_TYPES_CAST(c_int64_t,VALUE)

#define G_UINT8_C(VALUE) GEN_TYPES_CAST(c_uint8_t,VALUE)
#define G_UINT16_C(VALUE) GEN_TYPES_CAST(c_uint16_t,VALUE)
#define G_UINT32_C(VALUE) GEN_TYPES_CAST(c_uint32_t,VALUE)
#define G_UINT64_C(VALUE) GEN_TYPES_CAST(c_uint64_t,VALUE)

#define G_FLOAT32_C(VALUE) VALUE##F
#define G_FLOAT64_C(VALUE) VALUE

typedef signed char c_int8_t;
typedef unsigned char c_uint8_t;
typedef short c_int16_t;
typedef unsigned short c_uint16_t;
typedef long c_int32_t;
typedef unsigned long c_uint32_t;
typedef long long c_int64_t;
typedef unsigned long long c_uint64_t;

#endif /* GEN_TYPES_H_ */