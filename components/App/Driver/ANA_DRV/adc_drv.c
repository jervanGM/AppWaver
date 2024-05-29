#include "adc_drv.h"
#include "SERIES_ID.h"
#include "PERIF_DEFS.h"
#include "CONF_DEFS.h"
#include <stdio.h>
extern adc_continuous_handle_t handle;
extern adc_cali_handle_t adc1_cali_chan0_handle;
extern adc_oneshot_unit_handle_t adc1_handle;
extern bool do_calibration1_chan0;
#ifdef ADVANCED
extern adc_cali_handle_t adc1_cali_chan1_handle;
extern adc_cali_handle_t adc1_cali_chan2_handle;
extern adc_cali_handle_t adc1_cali_chan3_handle;
extern bool do_calibration1_chan1;
extern bool do_calibration1_chan2;
extern bool do_calibration1_chan3;
#endif
#ifdef ADC_DMA
void read_adc(uint8_t channel,uint32_t * data)
{
    esp_err_t ret;
    uint32_t ret_num = 0;
    uint8_t result[READ_LEN] = {0};
    memset(result, 0xcc, READ_LEN);

        /**
         * This is to show you the way to use the ADC continuous mode driver event callback.
         * This `ulTaskNotifyTake` will block when the data processing in the task is fast.
         * However in this example, the data processing (print) is slow, so you barely block here.
         *
         * Without using this event callback (to notify this task), you can still just call
         * `adc_continuous_read()` here in a loop, with/without a certain block timeout.
         */
        //ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        char unit[] = ADC_UNIT_STR(ADC_UNIT);

        ret = adc_continuous_read(handle, result, READ_LEN, &ret_num, 0);
        if (ret == ESP_OK) {
            //ESP_LOGI("TASK", "ret is %x, ret_num is %"PRIu32" bytes", ret, ret_num);
            for (int i = 0; i < ret_num; i += SOC_ADC_DIGI_RESULT_BYTES) {
                adc_digi_output_data_t *p = (void*)&result[i];
                uint32_t chan_num = ADC_GET_CHANNEL(p);
                uint32_t value = ADC_GET_DATA(p);
                /* Check the channel number validation, the data is invalid if the channel num exceed the maximum channel */
                if (chan_num < SOC_ADC_CHANNEL_NUM(ADC_UNIT)) {
                    *data = value;
                } else {
                    ESP_LOGW(TAG, "Invalid data [%s_%"PRIu32"]", unit, chan_num);
                }
            }
        } else if (ret == ESP_ERR_TIMEOUT) {
            //We try to read `EXAMPLE_READ_LEN` until API returns timeout, which means there's no available data
                
        }
        
}
#endif

#ifdef ADC_CONT
int8_t read_adc(uint8_t channel,uint32_t * data)
{
    if(adc_oneshot_read(adc1_handle, (adc_channel_t)channel, &adc_raw[channel][0]) != ESP_OK)
    {
        return -1;
    }
    //ESP_LOGI(TAG, "ADC%d Channel[%d] Raw Data: %d", ADC_UNIT_1 + 1, ADC1_CHAN0, adc_raw[0][0]);
    if (do_calibration1_chan0 && (channel == ADC1_CHAN0)) {
        if(adc_cali_raw_to_voltage(adc1_cali_chan0_handle, adc_raw[channel][0], &voltage[channel][0]) != ESP_OK)
        {
            return -1;
        }
            //ESP_LOGI(TAG, "ADC%d Channel[%d] Cali Voltage: %d mV", ADC_UNIT_1 + 1, ADC1_CHAN0, voltage[0][0]);
            *data = (uint32_t)voltage[channel][0];
    }
#ifdef ADVANCED
    if (do_calibration1_chan1 && (channel == ADC1_CHAN1)) {
        if(adc_cali_raw_to_voltage(adc1_cali_chan1_handle, adc_raw[1][0], &voltage[1][0]) != ESP_OK)
        {
            return -1;
        }
            //ESP_LOGI(TAG, "ADC%d Channel[%d] Cali Voltage: %d mV", ADC_UNIT_1 + 1, ADC1_CHAN0, voltage[0][0]);
            *data = (uint32_t)voltage[1][0];
    }
    if (do_calibration1_chan2 && (channel == ADC1_CHAN2)) {
        if(adc_cali_raw_to_voltage(adc1_cali_chan2_handle, adc_raw[2][0], &voltage[2][0]) != ESP_OK)
        {
            return -1;
        }
            //ESP_LOGI(TAG, "ADC%d Channel[%d] Cali Voltage: %d mV", ADC_UNIT_1 + 1, ADC1_CHAN0, voltage[0][0]);
            *data = (uint32_t)voltage[2][0];
    }
    if (do_calibration1_chan3 && (channel == ADC1_CHAN3)) {
        if(adc_cali_raw_to_voltage(adc1_cali_chan3_handle, adc_raw[3][0], &voltage[3][0]) != ESP_OK)
        {
            return -1;
        }
            //ESP_LOGI(TAG, "ADC%d Channel[%d] Cali Voltage: %d mV", ADC_UNIT_1 + 1, ADC1_CHAN0, voltage[0][0]);
            *data = (uint32_t)voltage[3][0];
    }
#endif
    return 0;
}
#endif
