
#ifndef PERIF_DEFS_H_
#define PERIF_DEFS_H_

#include "SERIES_ID.h"
/*Set pins for each board.*/

#ifdef BASIC

#define ADC_PLANT 2
#define SD_CLK 4
#define SD_MISO 5
#define SD_MOSI 6
#define SD_CS 7
#define BUTTON_IT 21
#define SYSTEM_OFF 20

#endif

#ifdef ADVANCED

#define ADC_PLANT 0
#define ADC_SOLAR_V 1
#define ADC_SOLAR_I 2
#define ADC_SOIL_IN 3
#define SOIL_OUT 4
#define SENSORS_OFF 5
#define I2C_SDA 6
#define I2C_SCL 7
#define ACC_IT2 8
#define ACC_IT1 14
#define BUTTON_IT 17
#define SD_CMD 18
#define SD_CLK 19
#define SD_DAT0 20
#define SD_DAT1 21
#define SD_DAT2 22
#define SD_DAT3 23
#define SYSTEM_OFF 16

#endif
// #define ADVANCED

#define BASIC

#endif /* PERIF_DEFS_H_ */