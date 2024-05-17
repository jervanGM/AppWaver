#include "bus_drv.h"
#include "safe_trace.h"
#include "safe_memory.h"
#include "bus_port.h"
#include "rtos.h"

static const IBusPort *bus_port;

/* Initializes the serial module */
void bus_init()
{
    bus_port = hal_bus_get_port();

    
    if (bus_port != NULL)
    {
        if(bus_port->init() != BUS_DRV_OK)
        {
            store_error_in_slot(BUS_ERROR_SLOT, BUS_DRV_INIT_ERROR);
            TRACE_ERROR("A serial task error has been produced during initialization");
            return;   
        } 
    }
    else
    {
        store_error_in_slot(BUS_ERROR_SLOT, HAL_BUS_CONFIG_ERROR);
        TRACE_ERROR("Serial HAL port has not been configured correctly on init");
    }
}

void devices_init()
{
    uint8_t rxbytes[6];
    uint8_t buf[2];
    uint32_t serial;
    uint8_t cmd = SHT4x_READSERIAL;
    bus_port->write_reg(SHT4x_DEFAULT_ADDR,&cmd,1);
    task_delay(15);
    bus_port->read_reg(SHT4x_DEFAULT_ADDR,rxbytes,6);
    serial = ((uint32_t)rxbytes[0] << 24) | ((uint32_t)rxbytes[1] << 16) | ((uint32_t)rxbytes[3] << 8) | rxbytes[4];
    if(serial == NULL || serial == 0)
    {
        store_error_in_slot(BUS_ERROR_SLOT,BUS_DEVICE_NOT_INIT);
        TRACE_ERROR("Temperature/Humidity sensor device was not initialized correctly");
    }

    buf[0] = LIS3DH_CTRL_REG1;
    buf[1] = 0x57;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
    task_delay(10);
    buf[0] = LIS3DH_CTRL_REG2;
    buf[1] = 0x00;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
    task_delay(10);
    buf[0] = LIS3DH_CTRL_REG3;
    buf[1] = 0x40;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
    task_delay(10);
    buf[0] = LIS3DH_CTRL_REG4;
    // buf[1] = 0x80;
    buf[1] = 0x00;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
    task_delay(10);
    buf[0] = LIS3DH_CTRL_REG5;
    buf[1] = 0x08;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
    task_delay(10);
    buf[0] = LIS3DH_CTRL_REG6;
    buf[1] = 0x00;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
    task_delay(10);
    // buf[0] = LIS3DH_REFERENCE;
    // buf[1] = 0x00;
    // bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
    // task_delay(10);
    buf[0] = LIS3DH_TEMP_CFG_REG;
    buf[1] = 0x80;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
    task_delay(10);
    buf[0] = LIS3DH_INT1_THS;
    buf[1] = 0x10;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
    task_delay(10);
    buf[0] = LIS3DH_INT1_DURATION;
    buf[1] = 0x05;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
    task_delay(10);
    buf[0] = LIS3DH_INT1_CFG;
    buf[1] = 0x95;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
    task_delay(10);
    buf[0] = LIS3DH_WHO_AM_I;
    buf[1] = 0x00;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
    task_delay(10);
    uint8_t chip_id;
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&chip_id,1);
    if(chip_id == NULL || chip_id == 0)
    {
         store_error_in_slot(BUS_ERROR_SLOT,BUS_DEVICE_NOT_INIT);
         TRACE_ERROR("Accelerometer sensor device was not initialized correctly");
    }
}

void measure_raw_data(uint8_t *raw_data)
{
    uint8_t rxbytes[6] = {0};
    uint8_t total_data[RAW_DATA_BYTES];
    uint8_t cmd = SHT4x_NOHEAT_LOWPRECISION;
    bus_port->write_reg(SHT4x_DEFAULT_ADDR,&cmd,1);
    task_delay(10);
    bus_port->read_reg(SHT4x_DEFAULT_ADDR,rxbytes,6);
    memcpy(total_data, rxbytes, sizeof(uint8_t) * 6);

    uint8_t reg = LIS3DH_OUT_X_L;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
    task_delay(10);
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&total_data[7],1);

    reg = LIS3DH_OUT_X_H;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
    task_delay(10);
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&total_data[6],1);

    reg = LIS3DH_OUT_Y_L;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
    task_delay(10);
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&total_data[9],1);

    reg = LIS3DH_OUT_Y_H;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
    task_delay(10);
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&total_data[8],1);

    reg = LIS3DH_OUT_Z_L;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
    task_delay(10);
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&total_data[11],1);

    reg = LIS3DH_OUT_Z_H;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
    task_delay(10);
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&total_data[10],1);
    
    reg = LIS3DH_OUT_ADC1_L;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
    task_delay(10);
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&total_data[13],1);
    
    reg = LIS3DH_OUT_ADC1_H;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
    task_delay(10);
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&total_data[12],1);

    reg = LIS3DH_OUT_ADC2_L;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
    task_delay(10);
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&total_data[15],1);
    
    reg = LIS3DH_OUT_ADC2_H;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
    task_delay(10);
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&total_data[14],1);

    reg = LIS3DH_OUT_ADC3_L;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
    task_delay(10);
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&total_data[17],1);
    
    reg = LIS3DH_OUT_ADC3_H;
    bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
    task_delay(10);
    bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&total_data[16],1);

    memcpy(raw_data, total_data, RAW_DATA_BYTES);

        // reg = LIS3DH_INT1_SRC;
        // uint8_t data = 0;
        // bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
        // task_delay(10);
        // bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&data,1);    
        // TRACE_DEBUG("INT DATA:", TO_STRING(data));

}

void write_temp_moist_cmd(ESht4xHeaterCmd_t cmd)
{
    uint8_t reg = SHT4x_NOHEAT_LOWPRECISION;
    switch (cmd)
    {
        case SHT4X_NO_HEATER:
            //Do nothing
            break;
        case SHT4X_HIGH_HEATER_1S:
            reg = SHT4x_HIGHHEAT_1S;
            bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
            break;

        case SHT4X_HIGH_HEATER_100MS:
            reg = SHT4x_HIGHHEAT_100MS;
            bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
            break;

        case SHT4X_MED_HEATER_1S:
            reg = SHT4x_MEDHEAT_1S;
            bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
            break;

        case SHT4X_MED_HEATER_100MS:
            reg = SHT4x_MEDHEAT_100MS;
            bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
            break;

        case SHT4X_LOW_HEATER_1S:
            reg = SHT4x_LOWHEAT_1S;
            bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
            break;

        case SHT4X_LOW_HEATER_100MS:
            reg = SHT4x_LOWHEAT_100MS;
            bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
            break;

        default:
            store_error_in_slot(BUS_ERROR_SLOT,BUS_DRV_HEAT_CMD_INVALID);
            TRACE_ERROR("Moisture sensor temperature heater command is not valid");
            break;
    }

}


void bus_deinit()
{
    if (bus_port != NULL)
    {
        if(bus_port->deinit() != BUS_DRV_OK)
        {
            TRACE_ERROR("A serial task error has been produced during deinitialization");
            return;   
        } 
    }
    else
    {
        TRACE_ERROR("Unexpected error on serial deinit due to port initialization error");
    }
}