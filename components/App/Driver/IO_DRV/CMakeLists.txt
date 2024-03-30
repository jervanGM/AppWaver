FILE(GLOB_RECURSE io_get *.c)

idf_component_register(SRCS ${io_get}
                       INCLUDE_DIRS "include"
                                    "../../../../lib/Common"
                        REQUIRES HW_CFG driver)

