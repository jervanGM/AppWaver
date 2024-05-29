#ifndef TRACE_TEST_H_
#define TRACE_TEST_H_
#include "test_suite.h"

    void test_bus_drv_init_error();

    void test_bus_drv_deinit_error();

    void test_port_dev_init_error();

    void test_port_measure_data_error();

    void test_port_write_temp_moist_cmd_error();

    void test_bus_drv_dev_init();

    void test_bus_drv_dev_init_serial_error();

    void test_bus_drv_dev_init_chip_id_error();

    void test_bus_drv_dev_init_write_error();

    void test_bus_drv_dev_init_read_error();

    void test_bus_measure_raw_data();

    void test_bus_measure_raw_data_null();

    void test_bus_measure_raw_data_write_read_error();

    void test_bus_drv_temp_moist_cmd();

    void test_bus_drv_temp_moist_cmd_write_error();

#endif /* TRACE_TEST_H_ */