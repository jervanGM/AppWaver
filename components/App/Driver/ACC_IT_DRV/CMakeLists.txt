FILE(GLOB_RECURSE acc_it_drv *.c)

idf_component_register(SRCS ${acc_it_drv}
                       INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
                                    "../../../../lib/Common"
                        REQUIRES esp_common HW_CFG RTOS)


