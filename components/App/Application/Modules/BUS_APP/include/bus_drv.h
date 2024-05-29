#ifndef BUS_DRV_H_
#define BUS_DRV_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "i_bus_data.h"

void bus_init();

void devices_init();

void measure_raw_data(uint8_t *raw_data);

void write_temp_moist_cmd(ESht4xHeaterCmd_t cmd);

void bus_deinit();

#endif /* BUS_DRV_H_ */