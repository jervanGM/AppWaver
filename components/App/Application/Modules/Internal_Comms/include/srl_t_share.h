#ifndef SRL_T_SHARE_H_
#define SRL_T_SHARE_H_

#include <stdbool.h>
#include "i_serial_data.h"

#define SRL_CTRL_M_ID 13

void set_task_serial_info(SSrlTaskInfo_t task_info);

void set_task_serial_status(ESrlTaskStatus_t status);

void set_serial_connection_status(ESrlConnStatus_t status);

void set_serial_command(SSerialCmd_t command);

void serial_controller_read(SSerialMsg_t *msg);

#endif /* SRL_T_SHARE_H_ */