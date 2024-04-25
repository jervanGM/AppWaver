#ifndef BTN_ISR_H_
#define BTN_ISR_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <esp_attr.h>

#define BTN_HANDLER_ID 3

void IRAM_ATTR button_it(void *arg);

#endif /* BTN_ISR_H_ */






