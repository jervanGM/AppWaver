#include "ctrl_app_test.h"
#include "safe_memory.h"
#include "control_app.h"
#include "libmfcc.h"
#include "fft.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "safe_trace.h"


void fft_test_task()
{
  int k;
	unsigned int coeff;
	double mfcc_result;
  // Create fft plan and let it allocate arrays
  fft_config_t *fft_analysis = fft_init(128, FFT_FORWARD, NULL, NULL);

// Inicializamos un arreglo para mantener un seguimiento de las posiciones ya asignadas a ceros
bool assigned_positions[fft_analysis->size];
for (int i = 0; i < fft_analysis->size; i++) {
    assigned_positions[i] = false; // Inicialmente, ninguna posición ha sido asignada
}

// Llenamos el 50% del arreglo con ceros en posiciones aleatorias
int num_zeros = fft_analysis->size * 0.6; // 50% de ceros
for (int i = 0; i < num_zeros; i++) {
    int rand_index;
    do {
        rand_index = rand() % fft_analysis->size; // Escogemos una posición aleatoria
    } while (assigned_positions[rand_index]); // Si la posición ya ha sido asignada, escogemos otra
    fft_analysis->input[rand_index] = 0;
    assigned_positions[rand_index] = true; // Marcamos la posición como asignada
}

// Llenamos el 30% del arreglo con valores aleatorios entre 0 y 10 en posiciones no asignadas
int num_low_values = fft_analysis->size * 0.35; // 30% de valores entre 0 y 10
for (int i = 0; i < num_low_values; i++) {
    int rand_index;
    do {
        rand_index = rand() % fft_analysis->size; // Escogemos una posición aleatoria
    } while (assigned_positions[rand_index]); // Si la posición ya ha sido asignada, escogemos otra
    fft_analysis->input[rand_index] = rand() % 11; // Valor aleatorio entre 0 y 10
    assigned_positions[rand_index] = true; // Marcamos la posición como asignada
}

// Llenamos el resto del arreglo con valores aleatorios entre 0 y 255 en posiciones no asignadas
for (int i = 0; i < fft_analysis->size; i++) {
    if (!assigned_positions[i]) { // Si la posición no ha sido asignada
        fft_analysis->input[i] = rand() % 100; // Valor aleatorio entre 0 y 255
    }
}

// Imprimimos los valores para verificar
for (int k = 0; k < fft_analysis->size; k++) {
    printf("ANALYSIS INPUT[%d]: %f\n", k, fft_analysis->input[k]);
}

  // Test accuracy
  fft_execute(fft_analysis);
  for (k = 0 ; k < fft_analysis->size ; k++)
  {
    printf("ANALYSIS OUTPUT[%d]: %f\n", k, fft_analysis->output[k]);
  }

  // Compute the first 13 coefficients
  for(coeff = 0; coeff < 13; coeff++)
  {
    mfcc_result = GetCoefficient(fft_analysis->output, 8, 48, 128, coeff);
    printf("%i %f\n", coeff, mfcc_result);
  }

  fft_destroy(fft_analysis);
  TEST_ASSERT(true);
}

void ctrl_app_test_suite()
{
    RUN_TEST(fft_test_task);
}