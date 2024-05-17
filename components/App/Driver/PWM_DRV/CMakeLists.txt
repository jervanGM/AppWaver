FILE(GLOB_RECURSE hw_get *.c)

idf_component_register(SRCS ${hw_get}
                       INCLUDE_DIRS "include"
                                    "../../../../lib/Common"
                        REQUIRES driver)

