FILE(GLOB_RECURSE hal_port *.c)
list(FILTER hal_port EXCLUDE REGEX "Test")

idf_component_register(SRCS ${hal_port}
                       INCLUDE_DIRS "include"
                                    "../hal_interfaces"
                        REQUIRES ANA_DRV HW_CFG)
