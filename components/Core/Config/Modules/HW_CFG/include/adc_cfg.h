#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/**
 * @file adc_cfg.h
 * @brief Header file for ADC configuration and handling.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_adc/adc_continuous.h"
#include "soc/soc_caps.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "SERIES_ID.h"

/**
 * @brief Define the ADC unit.
 */
#define ADC_UNIT                    ADC_UNIT_1

/**
 * @brief Macro to convert ADC unit to string.
 */
#define _ADC_UNIT_STR(unit)         #unit

/**
 * @brief Macro to get string representation of ADC unit.
 */
#define ADC_UNIT_STR(unit)          _ADC_UNIT_STR(unit)

/**
 * @brief ADC conversion mode.
 */
#define ADC_CONV_MODE               ADC_CONV_SINGLE_UNIT_1

/**
 * @brief ADC attenuation setting.
 */
#define ADC_ATTEN                   ADC_ATTEN_DB_0

/**
 * @brief ADC bit width.
 */
#define ADC_BIT_WIDTH               SOC_ADC_DIGI_MAX_BITWIDTH

/**
 * @brief ADC output type.
 */
#define ADC_OUTPUT_TYPE             ADC_DIGI_OUTPUT_FORMAT_TYPE2

/**
 * @brief Macro to get ADC channel from data.
 */
#define ADC_GET_CHANNEL(p_data)     ((p_data)->type2.channel)

/**
 * @brief Macro to get ADC data from data.
 */
#define ADC_GET_DATA(p_data)        ((p_data)->type2.data)

#ifdef BASIC
/**
 * @brief ADC1 channel 0 definition for basic mode.
 */
#define ADC1_CHAN0          ADC_CHANNEL_2

/**
 * @brief Array of ADC channels for basic mode.
 */
static adc_channel_t channel[1] = {ADC_CHANNEL_2};
#endif

#ifdef ADVANCED
/**
 * @brief ADC1 channel definitions for advanced mode.
 */
#define ADC1_CHAN0          ADC_CHANNEL_0
#define ADC1_CHAN1          ADC_CHANNEL_1
#define ADC1_CHAN2          ADC_CHANNEL_2
#define ADC1_CHAN3          ADC_CHANNEL_3

/**
 * @brief Array of ADC channels for advanced mode.
 */
static adc_channel_t channel[4] = {ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2, ADC_CHANNEL_3};
#endif

/**
 * @brief ADC attenuation setting.
 */
#define ADC_ATTEN           ADC_ATTEN_DB_11

/**
 * @brief Tag for logging ADC operations.
 */
static const char *TAG = "ADC";

/**
 * @brief Length of data to read from ADC.
 */
#define READ_LEN                    256

/**
 * @brief Function to initialize continuous ADC operation.
 *
 * @param channel Array of ADC channels.
 * @param channel_num Number of ADC channels.
 * @param out_handle Pointer to store the ADC continuous handle.
 */
static void continuous_adc_init(adc_channel_t *channel, uint8_t channel_num, adc_continuous_handle_t *out_handle);

/**
 * @brief Function to perform analog calibration for ADC.
 *
 * @param unit ADC unit.
 * @param channel ADC channel.
 * @param atten ADC attenuation.
 * @param out_handle Pointer to store the calibration handle.
 * @return bool Returns true if calibration is successful, false otherwise.
 */
static bool adc_calibration_ana_init(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle);

/**
 * @brief Function to deinitialize ADC calibration.
 *
 * @param handle Calibration handle.
 */
static void adc_calibration_deinit(adc_cali_handle_t handle);

/**
 * @brief Function to initialize ADC configuration.
 *
 * @return int8_t Returns 0 on success, -1 on error.
 */
int8_t adc_config_init();

/**
 * @brief Function to reset ADC configuration.
 *
 * @return int8_t Returns 0 on success, -1 on error.
 */
int8_t adc_config_reset();

#endif /* ADC_CFG_H_ */
