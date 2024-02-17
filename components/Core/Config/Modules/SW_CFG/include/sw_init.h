#ifndef SW_INIT_H_
#define SW_INIT_H_

#define ANA_T_PRIOR 5
#define DIGI_T_PRIOR 5
#define FLASH_T_PRIOR 5
#define SERIAL_RX_T_PRIOR 5
#define WIRELESS_T_PRIOR 5
#define POWER_T_PRIOR 5
#define IND_T_PRIOR 5

#define ANA_T_PERIOD 10
#define DIGI_T_PERIOD 100
#define FLASH_T_PERIOD 100
#define SERIAL_RX_T_PERIOD 100
#define WIRELESS_T_PERIOD 100
#define POWER_T_PERIOD 100
#define IND_T_PERIOD 100

void systemConfig();

void taskConfig();

void otaConfig();

void openThreadInit();

void hwInit();

#endif /* SW_INIT_H_ */