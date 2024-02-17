# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE hw_config *.c)

idf_component_register(SRCS ${hw_config}
                       INCLUDE_DIRS "include"
                                    "../../../../../lib/Common"
                        REQUIRES esp_adc)

