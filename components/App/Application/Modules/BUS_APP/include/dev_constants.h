#ifndef DEV_CONSTANTS_H_
#define DEV_CONSTANTS_H_

#define SHT4x_DEFAULT_ADDR 0x44 /**< SHT4x I2C Address */

#define SHT4x_NOHEAT_HIGHPRECISION 0xFD /**< High precision measurement, no heater */
#define SHT4x_NOHEAT_MEDPRECISION  0xF6 /**< Medium precision measurement, no heater */
#define SHT4x_NOHEAT_LOWPRECISION  0xE0 /**< Low precision measurement, no heater */

#define SHT4x_HIGHHEAT_1S       0x39 /**< High precision measurement, high heat for 1 sec */
#define SHT4x_HIGHHEAT_100MS    0x32 /**< High precision measurement, high heat for 0.1 sec */
#define SHT4x_MEDHEAT_1S        0x2F /**< High precision measurement, med heat for 1 sec */
#define SHT4x_MEDHEAT_100MS     0x24 /**< High precision measurement, med heat for 0.1 sec */
#define SHT4x_LOWHEAT_1S        0x1E /**< High precision measurement, low heat for 1 sec */
#define SHT4x_LOWHEAT_100MS     0x15 /**< High precision measurement, low heat for 0.1 sec */

#define SHT4x_READSERIAL    0x89 /**< Read Out of Serial Register */
#define SHT4x_SOFTRESET     0x94  /**< Soft Reset */

#define SHT4x_TEMP_ID 0x0400
#define SHT4x_HUM_ID  0x0401

#define GENERAL_RESET 0x06

#define RAW_DATA_BYTES 18

#define LIS3DH_DEFAULT_ADDR 0x18


#define LIS3DH_STATUS_REG_AUX         0x07
#define LIS3DH_OUT_ADC1_L             0x08
#define LIS3DH_OUT_ADC1_H             0x09
#define LIS3DH_OUT_ADC2_L             0x0A
#define LIS3DH_OUT_ADC2_H             0x0B
#define LIS3DH_OUT_ADC3_L             0x0C
#define LIS3DH_OUT_ADC3_H             0x0D
#define LIS3DH_WHO_AM_I               0x0F
#define LIS3DH_CTRL_REG0              0x1E
#define LIS3DH_TEMP_CFG_REG           0x1F
#define LIS3DH_CTRL_REG1              0x20
#define LIS3DH_CTRL_REG2              0x21
#define LIS3DH_CTRL_REG3              0x22
#define LIS3DH_CTRL_REG4              0x23
#define LIS3DH_CTRL_REG5              0x24
#define LIS3DH_CTRL_REG6              0x25
#define LIS3DH_REFERENCE              0x26
#define LIS3DH_STATUS_REG             0x27
#define LIS3DH_OUT_X_L                0x28
#define LIS3DH_OUT_X_H                0x29
#define LIS3DH_OUT_Y_L                0x2A
#define LIS3DH_OUT_Y_H                0x2B
#define LIS3DH_OUT_Z_L                0x2C
#define LIS3DH_OUT_Z_H                0x2D
#define LIS3DH_FIFO_CTRL_REG          0x2E
#define LIS3DH_FIFO_SRC_REG           0x2F
#define LIS3DH_INT1_CFG               0x30
#define LIS3DH_INT1_SRC               0x31
#define LIS3DH_INT1_THS               0x32
#define LIS3DH_INT1_DURATION          0x33
#define LIS3DH_INT2_CFG               0x34
#define LIS3DH_INT2_SRC               0x35
#define LIS3DH_INT2_THS               0x36
#define LIS3DH_INT2_DURATION          0x37
#define LIS3DH_CLICK_CFG              0x38
#define LIS3DH_CLICK_SRC              0x39
#define LIS3DH_CLICK_THS              0x3A
#define LIS3DH_TIME_LIMIT             0x3B
#define LIS3DH_TIME_LATENCY           0x3C
#define LIS3DH_TIME_WINDOW            0x3D
#define LIS3DH_ACT_THS                0x3E
#define LIS3DH_ACT_DUR                0x3F

#define ACC_ADC_CONV_FACTOR (1/64)
#define ACC_AXIS_CONV_FACTOR (0.004/64)

#define TEMP_CONV_FACTOR (56.0 / 65535.0)
#define MOIST_CONV_FACTOR (115.0 / 65535.0)


#endif /* DEV_CONSTANTS_H_ */