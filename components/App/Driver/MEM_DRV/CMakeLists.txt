FILE(GLOB_RECURSE mem_drv *.c)

idf_component_register(SRCS ${mem_drv}
                       INCLUDE_DIRS "include"
                                    "../../../../lib/Common"
                        REQUIRES fatfs HW_CFG)

