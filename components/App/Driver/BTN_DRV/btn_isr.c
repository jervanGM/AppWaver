#include "rtos.h"
#include "btn_isr.h"

void IRAM_ATTR button_it(void *arg) {
    // Notificar a la tarea que manejará la acción del botón
    notify_to_task_from_it(BTN_HANDLER_ID);
}
