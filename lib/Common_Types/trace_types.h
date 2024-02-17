#ifndef TRACE_TYPES_H_
#define TRACE_TYPES_H_

#define F_UINT8 "%u"
#define F_UINT16 "%u"
#define F_UINT32 "%lu"
#define F_UINT64 "%llu"
#define F_INT8 "%d"
#define F_INT16 "%d"
#define F_INT32 "%ld"
#define F_INT64 "%lld"
#define F_FLOAT "%f"
#define F_DOUBLE "%lf"
#define F_BOOL "%s"

typedef enum {
    TYPE_BOOL,
    TYPE_CHAR,
    TYPE_INT,
    TYPE_UINT,
    TYPE_INT8,
    TYPE_UINT8,
    TYPE_INT16,
    TYPE_UINT16,
    TYPE_INT32,
    TYPE_UINT32,
    TYPE_INT64,
    TYPE_UINT64,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_LONG_DOUBLE,
    TYPE_POINTER_TO_CHAR,
    TYPE_POINTER_TO_VOID,
    TYPE_POINTER_TO_INT,
    TYPE_OTHER
} ETypeNameEnum_t;

#define typename(x) _Generic((x),                                                     \
            _Bool: TYPE_BOOL,                  char: TYPE_CHAR,                             \
              int: TYPE_INT,                     unsigned int: TYPE_UINT,            \
          int8_t: TYPE_INT8,                     uint8_t: TYPE_UINT8,                      \
         int16_t: TYPE_INT16,                   uint16_t: TYPE_UINT16,                     \
         int32_t: TYPE_INT32,                   uint32_t: TYPE_UINT32,                     \
         int64_t: TYPE_INT64,                   uint64_t: TYPE_UINT64,                     \
            float: TYPE_FLOAT,                         double: TYPE_DOUBLE,                    \
      long double: TYPE_LONG_DOUBLE,                   char *: TYPE_POINTER_TO_CHAR,           \
           void *: TYPE_POINTER_TO_VOID,                int *: TYPE_POINTER_TO_INT,            \
          default: TYPE_OTHER)

typedef enum{
    DEBUG,
    INFO,
    WARNING,
    ERROR
} ETypeTrace_t;

#endif /* TRACE_TYPES_H_ */