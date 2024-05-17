FILE(GLOB_RECURSE hal_port *.c)
list(FILTER hal_port EXCLUDE REGEX "Test")

idf_component_register(SRCS ${hal_port}
                       INCLUDE_DIRS "include"
                                    "../hal_interfaces"
<<<<<<< HEAD
                        REQUIRES ANA_DRV WLS_DRV IO_DRV MEM_DRV SRL_DRV PWM_DRV BUS_DRV HW_CFG)
=======
                        REQUIRES ANA_DRV WLS_DRV IO_DRV MEM_DRV SRL_DRV HW_CFG)
>>>>>>> 580f3ba01581a2c652de2ce061dcf930e0026a99
