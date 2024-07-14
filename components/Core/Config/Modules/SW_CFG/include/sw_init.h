#ifndef SW_INIT_H_
#define SW_INIT_H_

#define ANA_T_PRIOR 5
#define DIGI_T_PRIOR 5
#define EXT_MEM_T_PRIOR 2
#define SERIAL_RX_T_PRIOR 2
#define WIRELESS_T_PRIOR 2
#define POWER_T_PRIOR 4
#define IND_T_PRIOR 3
#define CONTROL_T_PRIOR 6

#define ANA_T_PERIOD 100
#define DIGI_T_PERIOD 100
#define EXT_MEM_T_PERIOD 1000
#define SERIAL_RX_T_PERIOD 1500
#define WIRELESS_T_PERIOD 1000
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
#define SPORADIC_ACC_IT_HANDLER 9

/**
 * @brief Initializes the hardware.
 * 
 * @details This function initializes various hardware components:
 *          - Disables the watchdog timer to prevent system resets.
 *          - Initializes GPIO ports for buttons and accelerometers.
 *          - Enables interrupts for GPIO ports.
 * 
 *          If the GPIO configuration port initialization fails, 
 *          it asserts with a panic message.
 */
void hwInit();

/**
 * @brief Configures various tasks in the system.
 * 
 * @details This function configures the following tasks:
 *          - Analog Task
 *          - Control Task
 *          - Power Task
 *          - Indication Task
 *          - Wireless Task
 *          - External Memory Task
 *          - Serial Task
 * 
 *          Additionally, for advanced configurations:
 *          - Bus Task (if ADVANCED is defined)
 * 
 *          It also initializes mutexes and creates sporadic tasks for button and accelerometer tasks.
 */
void taskConfig();

/**
 * @brief Configures the system.
 * 
 * @details This function calls `hwInit()` to initialize hardware components
 *          and `taskConfig()` to configure various tasks in the system.
 */
void systemConfig();

#endif /* SW_INIT_H_ */