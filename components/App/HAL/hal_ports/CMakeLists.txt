FILE(GLOB_RECURSE hal_port *.c)

idf_component_register(SRCS ${hal_port}
                       INCLUDE_DIRS "include"
                                    "../hal_interfaces"
                        REQUIRES ANA_DRV HW_CFG)
