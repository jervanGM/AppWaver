#include "dsp.h"
#include "ana_port.h"

uint8_t getDSPData()
{
    uint32_t data;
    const IAnaPort *port = HAL_ANA_GetPort();
    port->read(2,&data);
    // the size of this array represents how many numbers will be used
    // to calculate the average
    iirFilter(&data);
    uint8_t normalized_data = dataNormalization(data);
    return normalized_data;
}

void iirFilter(uint32_t *input)
{
    static float x[] = {0, 0, 0};
    static float y[] = {0, 0, 0};
    x[0]= (float)(*input);
    // Compute the filtered signal
    // (second order Butterworth example)
    float b[] = {1, -2, 1};
    float a[] = {1.992, -0.915};
    float z = 1.093;
    y[0] = (a[0] * y[1] + a[1] * y[2] +
            b[0] * x[0] + b[1] * x[1] + b[2] * x[2]) / z;

    *input = (uint32_t)y[0];
    for (int i = 1; i >= 0; i--) {
        x[i + 1] = x[i]; // almacenar xi
        y[i + 1] = y[i]; // almacenar yi
    }
}

uint8_t dataNormalization(uint32_t input) {
    // Valor mínimo y máximo esperado para los datos de entrada
    uint32_t min_value = 0;  // Valor mínimo
    uint32_t max_value = 2048;  // Valor máximo

    // Valor mínimo y máximo para los datos normalizados
    uint8_t normalized_min = 0;  // Valor mínimo normalizado
    uint8_t normalized_max = 255;  // Valor máximo normalizado

    // Realiza la normalización utilizando una regla de tres y redondeo
    uint8_t normalized_data = (uint8_t)(((input - min_value) * (normalized_max - normalized_min) + (max_value - 1) / 2) / (max_value - min_value));
    return normalized_data;
}
