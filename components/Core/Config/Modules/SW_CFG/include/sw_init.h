#ifndef SW_INIT_H_
#define SW_INIT_H_

#define ANA_T_PRIOR 5
#define DIGI_T_PRIOR 5
#define EXT_MEM_T_PRIOR 5
#define SERIAL_RX_T_PRIOR 5
#define WIRELESS_T_PRIOR 5
#define POWER_T_PRIOR 3
#define IND_T_PRIOR 2
#define CONTROL_T_PRIOR 5

#define ANA_T_PERIOD 100
#define DIGI_T_PERIOD 100
#define EXT_MEM_T_PERIOD 100
#define SERIAL_RX_T_PERIOD 100
#define WIRELESS_T_PERIOD 100
#define POWER_T_PERIOD 300
#define IND_T_PERIOD 500
#define CONTROL_T_PERIOD 10

#define ANA_T_HANDLER 0
#define CONTROL_T_HANDLER 1
#define WIRELESS_T_HANDLER 2
#define SPORADIC_BUTTON_HANDLER 3
#define IND_T_HANDLER 4
#define POWER_T_HANDLER 5
#define EXT_MEM_T_HANDLER 6
#define SERIAL_RX_T_HANDLER 7
#define DIGI_T_HANDLER 8

void systemConfig();

void taskConfig();

void hwInit();

#endif /* SW_INIT_H_ */