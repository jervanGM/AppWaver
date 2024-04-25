#ifndef TASK_TYPES_H_
#define TASK_TYPES_H_

typedef enum{
    TASK_OK,               
    TASK_MEM_ERR,         
    TASK_UNKNOWN_ERR,
    TASK_WARNING
} ETaskCfgError_t;

typedef enum{
    TASK_RUNNING,               
    TASK_READY,         
    TASK_BLOCKED,
    TASK_SUSPENDED,
    TASK_DELETED,
    TASK_INVALID
} ETaskState_t;

#endif /* TASK_TYPES_H_ */