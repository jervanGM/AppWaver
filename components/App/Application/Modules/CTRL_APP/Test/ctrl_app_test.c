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
      //printf("ANALYSIS INPUT[%d]: %f\n", k, fft_analysis->input[k]);
  }

    // Test accuracy
    fft_execute(fft_analysis);
    for (k = 0 ; k < fft_analysis->size ; k++)
    {
      //printf("ANALYSIS OUTPUT[%d]: %f\n", k, fft_analysis->output[k]);
    }

    // Compute the first 13 coefficients
    for(coeff = 0; coeff < 13; coeff++)
    {
      mfcc_result = GetCoefficient(fft_analysis->output, 8, 48, 128, coeff);
      //printf("%i %f\n", coeff, mfcc_result);
    }

    fft_destroy(fft_analysis);
    TEST_ASSERT(true);
}

void test_controller_app_check_mayor_faults() {
    ECtrlTaskStatus_t fault;
    store_error_in_slot(CONTROL_ERROR_SLOT, -120);
    fault = control_app_check_faults();
    TEST_ASSERT_EQUAL(fault, CTRL_MAYOR_FAULT);
}

void test_controller_app_check_minor_faults() {
    ECtrlTaskStatus_t fault;
    store_error_in_slot(CONTROL_ERROR_SLOT, -10);
    fault = control_app_check_faults();
    TEST_ASSERT_EQUAL(fault, CTRL_MINOR_FAULT);
}

void test_controller_app_check_no_faults() {
    ECtrlTaskStatus_t fault;
    store_error_in_slot(CONTROL_ERROR_SLOT, 10);
    fault = control_app_check_faults();
    TEST_ASSERT_EQUAL(fault, CTRL_TASK_OK);
}

void test_controller_app_check_lower_minor_fault_boundary() {
    ECtrlTaskStatus_t fault;
    store_error_in_slot(CONTROL_ERROR_SLOT, MINOR_FAULT_THRESHOLD);
    fault = control_app_check_faults();
    TEST_ASSERT_EQUAL(fault, CTRL_TASK_OK);
}

void test_controller_app_check_upper_minor_fault_boundary() {
    ECtrlTaskStatus_t fault;
    store_error_in_slot(CONTROL_ERROR_SLOT, MAYOR_FAULT_THESHOLD - 1);
    fault = control_app_check_faults();
    TEST_ASSERT_EQUAL(fault, CTRL_MAYOR_FAULT);
}

void test_controller_app_check_lower_major_fault_boundary() {
    ECtrlTaskStatus_t fault;
    store_error_in_slot(CONTROL_ERROR_SLOT, MAYOR_FAULT_THESHOLD);
    fault = control_app_check_faults();
    TEST_ASSERT_EQUAL(fault, CTRL_TASK_OK);
}

void test_controller_app_check_upper_major_fault_boundary() {
    ECtrlTaskStatus_t fault;
    store_error_in_slot(CONTROL_ERROR_SLOT, INT8_MAX);
    fault = control_app_check_faults();
    TEST_ASSERT_EQUAL(fault, CTRL_TASK_OK);
}

void test_controller_app_process_plant_data_random()
{
	uint32_t plant_data_in[128] = {0};
  uint32_t plant_data_out[128] = {0};

  int num_zeros = sizeof(plant_data_in) / sizeof(plant_data_in[0]);;
  for (int i = 0; i < num_zeros; i++) {
        plant_data_in[i] = rand() % 2000;
  }

  control_app_process_plant_data(plant_data_in,plant_data_out,num_zeros,true);

  TEST_ASSERT_EQUAL_UINT32_ARRAY(plant_data_in,plant_data_out,num_zeros);
}

void test_controller_app_process_plant_data_random_low_level()
{
	uint32_t plant_data_in[128] = {0};
  uint32_t plant_data_out[128] = {0};
  uint32_t plant_data_cmp[128] = {0};

  int num_zeros = sizeof(plant_data_in) / sizeof(plant_data_in[0]);;
  for (int i = 0; i < num_zeros; i++) {
        plant_data_in[i] = rand() % 10;
  }

  control_app_process_plant_data(plant_data_in,plant_data_out,num_zeros,true);

  TEST_ASSERT_EQUAL_UINT32_ARRAY(plant_data_cmp,plant_data_out,num_zeros);
}

void test_controller_app_process_plant_data_random_sim_real()
{
	uint32_t plant_data_in[128] = {0};
  uint32_t plant_data_out[128] = {0};
  uint32_t plant_data_cmp[128] = {0};

  int plant_size = sizeof(plant_data_in) / sizeof(plant_data_in[0]);;
  // Inicializamos un arreglo para mantener un seguimiento de las posiciones ya asignadas a ceros
  bool assigned_positions[plant_size];
  for (int i = 0; i < plant_size; i++) {
      assigned_positions[i] = false; // Inicialmente, ninguna posición ha sido asignada
  }

  int num_zeros = plant_size * 0.6;
  for (int i = 0; i < num_zeros; i++) {
      int rand_index;
      do {
          rand_index = rand() % plant_size; // Escogemos una posición aleatoria
      } while (assigned_positions[rand_index]); // Si la posición ya ha sido asignada, escogemos otra
      plant_data_in[rand_index] = 0;
      assigned_positions[rand_index] = true; // Marcamos la posición como asignada
  }

  int num_low_values = plant_size * 0.35;
  for (int i = 0; i < num_low_values; i++) {
      int rand_index;
      do {
          rand_index = rand() % plant_size; // Escogemos una posición aleatoria
      } while (assigned_positions[rand_index]); // Si la posición ya ha sido asignada, escogemos otra
      plant_data_in[rand_index] = rand() % 11; // Valor aleatorio entre 0 y 10
      assigned_positions[rand_index] = true; // Marcamos la posición como asignada
  }

  for (int i = 0; i < plant_size; i++) {
      if (!assigned_positions[i]) { // Si la posición no ha sido asignada
          plant_data_in[i] = rand() % 1000; // Valor aleatorio entre 0 y 255
      }
  }

  control_app_process_plant_data(plant_data_in,plant_data_out,plant_size,true);

  TEST_ASSERT_EQUAL_UINT32_ARRAY(plant_data_in,plant_data_out,plant_size);
}

void test_controller_app_process_plant_data_random_sim_low()
{
	uint32_t plant_data_in[128] = {0};
  uint32_t plant_data_out[128] = {0};
  uint32_t plant_data_cmp[128] = {0};

  int plant_size = sizeof(plant_data_in) / sizeof(plant_data_in[0]);;
  // Inicializamos un arreglo para mantener un seguimiento de las posiciones ya asignadas a ceros
  bool assigned_positions[plant_size];
  for (int i = 0; i < plant_size; i++) {
      assigned_positions[i] = false; // Inicialmente, ninguna posición ha sido asignada
  }

  int num_zeros = plant_size * 0.6;
  for (int i = 0; i < num_zeros; i++) {
      int rand_index;
      do {
          rand_index = rand() % plant_size; // Escogemos una posición aleatoria
      } while (assigned_positions[rand_index]); // Si la posición ya ha sido asignada, escogemos otra
      plant_data_in[rand_index] = 0;
      assigned_positions[rand_index] = true; // Marcamos la posición como asignada
  }

  int num_low_values = plant_size * 0.35;
  for (int i = 0; i < num_low_values; i++) {
      int rand_index;
      do {
          rand_index = rand() % plant_size; // Escogemos una posición aleatoria
      } while (assigned_positions[rand_index]); // Si la posición ya ha sido asignada, escogemos otra
      plant_data_in[rand_index] = rand() % 11; // Valor aleatorio entre 0 y 10
      assigned_positions[rand_index] = true; // Marcamos la posición como asignada
  }

  for (int i = 0; i < plant_size; i++) {
      if (!assigned_positions[i]) { // Si la posición no ha sido asignada
          plant_data_in[i] = rand() % 50; // Valor aleatorio entre 0 y 255
      }
  }

  control_app_process_plant_data(plant_data_in,plant_data_out,plant_size,true);

  TEST_ASSERT_EQUAL(memcmp(plant_data_cmp,plant_data_out,128* sizeof(uint32_t)), 0);
}

void ctrl_app_test_suite()
{
    RUN_TEST(fft_test_task);
    RUN_TEST(test_controller_app_check_mayor_faults);
    RUN_TEST(test_controller_app_check_minor_faults);
    RUN_TEST(test_controller_app_check_no_faults);
    RUN_TEST(test_controller_app_check_lower_minor_fault_boundary);
    RUN_TEST(test_controller_app_check_upper_minor_fault_boundary);
    RUN_TEST(test_controller_app_check_lower_major_fault_boundary);
    RUN_TEST(test_controller_app_check_upper_major_fault_boundary);
    RUN_TEST(test_controller_app_process_plant_data_random);
    RUN_TEST(test_controller_app_process_plant_data_random_low_level);
    RUN_TEST(test_controller_app_process_plant_data_random_sim_real);
    RUN_TEST(test_controller_app_process_plant_data_random_sim_low);
}