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

static int8_t read_register(uint8_t dev_addrs, uint8_t registr, uint8_t *data, uint32_t delay)
{
    uint8_t reg = registr;
    if(bus_port->write_reg(dev_addrs,&reg,1) == BUS_DRV_OK)
    {
        task_delay(delay);
        if(bus_port->read_reg(dev_addrs,data,1) != BUS_DRV_OK)
        {
            return -1;            
        }
    }
    else
    {
        return -1;    
    }
    return 0;
}

void devices_init()
{
    uint8_t rxbytes[6];
    uint8_t buf[2];
    uint32_t serial = 0;
    uint8_t cmd = SHT4x_READSERIAL;
    int8_t err = BUS_DRV_OK;
    if(bus_port != NULL)
    {
        err += bus_port->write_reg(SHT4x_DEFAULT_ADDR,&cmd,1);
        task_delay(15);
        err += bus_port->read_reg(SHT4x_DEFAULT_ADDR,rxbytes,6);
        serial = ((uint32_t)rxbytes[0] << 24) | ((uint32_t)rxbytes[1] << 16) | ((uint32_t)rxbytes[3] << 8) | rxbytes[4];
        if(serial == 0 || err != BUS_DRV_OK)
        {
            store_error_in_slot(BUS_ERROR_SLOT,BUS_DEVICE_NOT_INIT);
            TRACE_ERROR("Temperature/Humidity sensor device was not initialized correctly");
        }

        buf[0] = LIS3DH_CTRL_REG1;
        buf[1] = 0x57;
        err += bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
        task_delay(10);
        buf[0] = LIS3DH_CTRL_REG2;
        buf[1] = 0x00;
        err += bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
        task_delay(10);
        buf[0] = LIS3DH_CTRL_REG3;
        buf[1] = 0x40;
        err += bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
        task_delay(10);
        buf[0] = LIS3DH_CTRL_REG4;
        // buf[1] = 0x80;
        buf[1] = 0x00;
        err += bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
        task_delay(10);
        buf[0] = LIS3DH_CTRL_REG5;
        buf[1] = 0x08;
        err += bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
        task_delay(10);
        buf[0] = LIS3DH_CTRL_REG6;
        buf[1] = 0x00;
        err += bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
        task_delay(10);
        // buf[0] = LIS3DH_REFERENCE;
        // buf[1] = 0x00;
        // bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
        // task_delay(10);
        buf[0] = LIS3DH_TEMP_CFG_REG;
        buf[1] = 0x80;
        err += bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
        task_delay(10);
        buf[0] = LIS3DH_INT1_THS;
        buf[1] = 0x10;
        err += bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
        task_delay(10);
        buf[0] = LIS3DH_INT1_DURATION;
        buf[1] = 0x05;
        err += bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
        task_delay(10);
        buf[0] = LIS3DH_INT1_CFG;
        buf[1] = 0x95;
        err += bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
        task_delay(10);
        buf[0] = LIS3DH_WHO_AM_I;
        buf[1] = 0x00;
        err += bus_port->write_reg(LIS3DH_DEFAULT_ADDR,buf,2);
        task_delay(10);
        uint8_t chip_id = 0;
        err += bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&chip_id,1);
        if(chip_id == 0 || err != BUS_DRV_OK)
        {
            store_error_in_slot(BUS_ERROR_SLOT,BUS_DEVICE_NOT_INIT);
            TRACE_ERROR("Accelerometer sensor device was not initialized correctly");
        }
    }
    else
    {
        store_error_in_slot(BUS_ERROR_SLOT,BUS_DRN_ON_DEVINIT_FATAL_ERROR);
        TRACE_ERROR("Bus port on devices init is not valid");
    }

}

void measure_raw_data(uint8_t *raw_data)
{
    uint8_t rxbytes[6] = {0};
    uint8_t total_data[RAW_DATA_BYTES];
    uint8_t cmd = SHT4x_NOHEAT_LOWPRECISION;
    if(raw_data != NULL && bus_port != NULL)
    {
        int8_t err = 0;
        err += bus_port->write_reg(SHT4x_DEFAULT_ADDR,&cmd,1);
        task_delay(10);
        err += bus_port->read_reg(SHT4x_DEFAULT_ADDR,rxbytes,6);
        memcpy(total_data, rxbytes, sizeof(uint8_t) * 6);

        err += read_register(LIS3DH_DEFAULT_ADDR, LIS3DH_OUT_X_L, &total_data[7], LIS3DH_READ_DELAY);
        err += read_register(LIS3DH_DEFAULT_ADDR, LIS3DH_OUT_X_H, &total_data[6], LIS3DH_READ_DELAY);
        err += read_register(LIS3DH_DEFAULT_ADDR, LIS3DH_OUT_Y_L, &total_data[9], LIS3DH_READ_DELAY);
        err += read_register(LIS3DH_DEFAULT_ADDR, LIS3DH_OUT_Y_H, &total_data[8], LIS3DH_READ_DELAY);
        err += read_register(LIS3DH_DEFAULT_ADDR, LIS3DH_OUT_Z_L, &total_data[11], LIS3DH_READ_DELAY);
        err += read_register(LIS3DH_DEFAULT_ADDR, LIS3DH_OUT_Z_H, &total_data[10], LIS3DH_READ_DELAY);
        err += read_register(LIS3DH_DEFAULT_ADDR, LIS3DH_OUT_ADC1_L, &total_data[13], LIS3DH_READ_DELAY);
        err += read_register(LIS3DH_DEFAULT_ADDR, LIS3DH_OUT_ADC1_H, &total_data[12], LIS3DH_READ_DELAY);
        err += read_register(LIS3DH_DEFAULT_ADDR, LIS3DH_OUT_ADC2_L, &total_data[15], LIS3DH_READ_DELAY);
        err += read_register(LIS3DH_DEFAULT_ADDR, LIS3DH_OUT_ADC2_H, &total_data[14], LIS3DH_READ_DELAY);
        err += read_register(LIS3DH_DEFAULT_ADDR, LIS3DH_OUT_ADC3_L, &total_data[17], LIS3DH_READ_DELAY);
        err += read_register(LIS3DH_DEFAULT_ADDR, LIS3DH_OUT_ADC3_H, &total_data[16], LIS3DH_READ_DELAY);

        if(err != BUS_DRV_OK)
        {
            store_error_in_slot(BUS_ERROR_SLOT,BUS_DRV_ON_READ_ERROR);
            memset(raw_data, 0, RAW_DATA_BYTES);
        }
        else
        {
            memcpy(raw_data, total_data, RAW_DATA_BYTES);
        }
        // reg = LIS3DH_INT1_SRC;
        // uint8_t data = 0;
        // bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
        // task_delay(10);
        // bus_port->read_reg(LIS3DH_DEFAULT_ADDR,&data,1);    
        // TRACE_DEBUG("INT DATA:", TO_STRING(data));
    }
    else
    {
        store_error_in_slot(BUS_ERROR_SLOT,BUS_DRV_ON_READ_FATAL_ERROR);
        TRACE_ERROR("Digital bus raw data buffer is not valid");
    }

}

void write_temp_moist_cmd(ESht4xHeaterCmd_t cmd)
{
    uint8_t reg = SHT4x_NOHEAT_LOWPRECISION;
    int8_t err = BUS_DRV_OK;
    if(bus_port != NULL)
    {
        switch (cmd)
        {
            case SHT4X_NO_HEATER:
                //Do nothing
                break;
            case SHT4X_HIGH_HEATER_1S:
                reg = SHT4x_HIGHHEAT_1S;
                err = bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
                break;

            case SHT4X_HIGH_HEATER_100MS:
                reg = SHT4x_HIGHHEAT_100MS;
                err = bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
                break;

            case SHT4X_MED_HEATER_1S:
                reg = SHT4x_MEDHEAT_1S;
                err = bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
                break;

            case SHT4X_MED_HEATER_100MS:
                reg = SHT4x_MEDHEAT_100MS;
                err = bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
                break;

            case SHT4X_LOW_HEATER_1S:
                reg = SHT4x_LOWHEAT_1S;
                err = bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
                break;

            case SHT4X_LOW_HEATER_100MS:
                reg = SHT4x_LOWHEAT_100MS;
                err = bus_port->write_reg(LIS3DH_DEFAULT_ADDR,&reg,1);
                break;

            default:
                store_error_in_slot(BUS_ERROR_SLOT,BUS_DRV_HEAT_CMD_INVALID);
                TRACE_ERROR("Moisture sensor temperature heater command is not valid");
                break;
        }
    }
    else
    {
        err = BUS_DRV_FAIL;
    }

    if(err != BUS_DRV_OK)
    {
        store_error_in_slot(BUS_ERROR_SLOT,BUS_DRV_ON_WRITE_ERROR);
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