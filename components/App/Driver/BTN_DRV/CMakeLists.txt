FILE(GLOB_RECURSE btn_drv *.c)

idf_component_register(SRCS ${btn_drv}
                       INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
                                    "../../../../lib/Common"
                        REQUIRES esp_common HW_CFG RTOS)


