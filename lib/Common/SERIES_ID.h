#ifndef SERIES_ID_H_
#define SERIES_ID_H_

#include "sdkconfig.h"

/*Used to select the distributed board type.*/

//Yggwave Series
#ifdef CONFIG_IDF_TARGET_ESP32C6
#define ADVANCED
#endif

//ESpikerbox Series
#ifdef CONFIG_IDF_TARGET_ESP32C3
#define BASIC 
#endif

#endif /* SERIES_ID_H_ */