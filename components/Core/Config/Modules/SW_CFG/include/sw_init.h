#ifndef SW_INIT_H_
#define SW_INIT_H_

#define ANA_T_PRIOR 5
#define DIGI_T_PRIOR 5
#define FLASH_T_PRIOR 5
#define SERIAL_RX_T_PRIOR 5
#define WIRELESS_T_PRIOR 5
#define POWER_T_PRIOR 3
#define IND_T_PRIOR 2
#define CONTROL_T_PRIOR 5

#define ANA_T_PERIOD 100
#define DIGI_T_PERIOD 100
#define FLASH_T_PERIOD 100
#define SERIAL_RX_T_PERIOD 100
#define WIRELESS_T_PERIOD 100
#define POWER_T_PERIOD 300
#define IND_T_PERIOD 500
#define CONTROL_T_PERIOD 10

#define SPORADIC_BUTTON_HANDLER 0

void systemConfig();

void taskConfig();

void hwInit();

#endif /* SW_INIT_H_ */