FILE(GLOB_RECURSE hal_port *.c)
list(FILTER hal_port EXCLUDE REGEX "Test")

idf_component_register(SRCS ${hal_port}
                       INCLUDE_DIRS "include"
                                    "../hal_interfaces"
                        REQUIRES ANA_DRV WLS_DRV IO_DRV MEM_DRV SRL_DRV PWM_DRV BUS_DRV HW_CFG)
