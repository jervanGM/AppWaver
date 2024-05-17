#ifndef SERIAL_CODEC_H_
#define SERIAL_CODEC_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "i_serial_data.h"

void serial_init();

bool serial_connected();

SSerialCmd_t serial_process_cmd();

void serial_deinit();

#endif /* SERIAL_CODEC_H_ */