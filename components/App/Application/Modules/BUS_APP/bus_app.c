#include "bus_app.h"
#include "safe_memory.h"
#include <string.h>

static SAxisDataBuffer_t data_buffer;
static SBufTime_t data_time;
static STemp_t temp_data;
static SMoist_t moist_data;

const char *bus_cmd_list[] = {
    "heater_1s_on",
    "heater_off"
};

/* Adds a value to the data buffer */
static void add_to_axis_buffer(float x,float y,float z) {

    // Check for buffer overflow
    if (data_buffer.size < DATA_BUFFER_SIZE) {
        
        // Add the value to the buffer
        data_buffer.x[data_buffer.size] = x;
        data_buffer.y[data_buffer.size] = y;
        data_buffer.z[data_buffer.size] = z;
        data_buffer.size++;
        // Update time if the buffer was empty
        if (data_buffer.size == 1) {
            data_time.start_time = get_system_time();
        }
        
        // Check if the buffer is full
        if (data_buffer.size >= DATA_BUFFER_SIZE) {
            data_buffer.ready = true;
            data_time.end_time = get_system_time();
        }
    }
}

/* Clears the data buffer */
static void clear_axis_data_buffer() {
    // Reset buffer properties
    data_buffer.size = 0;
    data_buffer.ready = false;
}

void bus_app_init()
{
    SAxisDataBuffer_t init_axis_data = {0};
    SBufTime_t init_time_data = {0};
    STemp_t init_temp_data = {0};
    SMoist_t init_moist_data = {0};

    /*Initializate buffers to 0*/
    memcpy(&data_buffer, &init_axis_data, sizeof(SAxisDataBuffer_t));
    memcpy(&data_time, &init_time_data, sizeof(SBufTime_t));
    memcpy(&temp_data, &init_temp_data, sizeof(STemp_t));
    memcpy(&moist_data, &init_moist_data, sizeof(SMoist_t));
}

void process_data(uint8_t *raw_data, size_t size)
{
    float temperature;
    float adc1, adc2, adc3;
    float moisture;
    float x, y, z;
    static float sum_temp, sum_moist;
    static bool clean_data = false;

    if (raw_data == NULL || size != RAW_DATA_BYTES) {
        // Log an error if the pointers are null or size is incorrect
        store_error_in_slot(BUS_ERROR_SLOT, BUS_APP_BUFFER_EMPTY);
        TRACE_ERROR("Bus data buffer is empty or not valid");
        return;
    }

    // Process temperature data
    temperature = ((uint16_t)raw_data[0] << 8 | raw_data[1]) * TEMP_CONV_FACTOR;

    // Process moisture data
    moisture = ((uint16_t)raw_data[3] << 8 | raw_data[4]) * MOIST_CONV_FACTOR;

    // Process accelerometer data
    x = ((uint16_t)raw_data[6] << 8 | raw_data[7]) * ACC_AXIS_CONV_FACTOR;
    y = ((uint16_t)raw_data[8] << 8 | raw_data[9]) * ACC_AXIS_CONV_FACTOR;
    z = ((uint16_t)raw_data[10] << 8 | raw_data[11]) * ACC_AXIS_CONV_FACTOR;

    // Process ADC data
    adc1 = ((uint16_t)raw_data[12] << 8 | raw_data[13]) / ACC_ADC_CONV_FACTOR;
    adc2 = ((uint16_t)raw_data[14] << 8 | raw_data[15]) / ACC_ADC_CONV_FACTOR;
    adc3 = ((uint16_t)raw_data[16] << 8 | raw_data[17]) / ACC_ADC_CONV_FACTOR;

    if (data_buffer.ready) {
        // Clear the data buffer if it's ready
        clear_axis_data_buffer();
    }

    data_buffer.instant_x = x;
    data_buffer.instant_y = y;
    data_buffer.instant_z = z;

    data_buffer.instant_time = get_system_time();
    // Add data to the axis buffer
    add_to_axis_buffer(x, y, z);

    // Calculate and store average temperature and moisture
    temp_data.temperature = temperature;
    moist_data.moist = moisture;

    // Uncomment the following line to print sensor data for debugging
    //printf("SENSOR MSG: %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f\n", temperature, moisture, x, y, z, adc1, adc2, adc3);
}

SAxisDataBuffer_t get_axis_data_buffer()
{
    if(data_buffer.ready)
    {
        return data_buffer;
    }
    SAxisDataBuffer_t default_data = {0};
    default_data.instant_time = data_buffer.instant_time;
    default_data.instant_x = data_buffer.instant_x;
    default_data.instant_y = data_buffer.instant_y;
    default_data.instant_z = data_buffer.instant_z;
    return default_data;   
}

SBufTime_t get_axis_buffer_time()
{
    if(data_buffer.ready)
    {
        return data_time;
    }
    SBufTime_t default_time = {0};
    return default_time;
}

STemp_t get_buffer_average_temp()
{
    return temp_data;
}

SMoist_t get_buffer_average_moist()
{
    return moist_data;
}

/* Checks for faults in the serial application */
EBusTaskStatus_t bus_app_check_faults()
{
    int8_t error = 0;

    // Read the error from the specified error slot
    error = read_error_from_slot(BUS_ERROR_SLOT);
    // Determine the task status based on the error value
    if ((error < MINOR_FAULT_THRESHOLD) && (error > MAYOR_FAULT_THESHOLD))
    {
        // Return BUS_MINOR_FAULT if the error falls within the defined range
        return BUS_MINOR_FAULT;
    }
    else if (error < MAYOR_FAULT_THESHOLD)
    {
        // Return BUS_MAYOR_FAULT if the error is less than MAYOR_FAULT_THRESHOLD
        return BUS_MAYOR_FAULT;
    }
    else
    {
        // Return BUS_TASK_OK if no faults are detected
        return BUS_TASK_OK;
    }
}
